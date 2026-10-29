"""Build the WB1 RAM-only checkpoint once; never rebuild F or access hardware."""
import argparse
import binascii
import json
from pathlib import Path
import re
import shutil
import subprocess

from build_mona import ROOT, cells, equs, sha
from mona_branches import conservative_branches


def build(out, generation=1):
    if not 1 <= generation <= 0xffffffff:
        raise ValueError('Generation must be 1..FFFFFFFF')
    generation_text=f'{generation:08X}'
    out = Path(out).resolve()
    if out.exists():
        raise ValueError('Use a fresh output directory; preserve earlier build results')
    assembler, linker = shutil.which('wdc02as'), shutil.which('wdcln')
    if not assembler or not linker:
        raise ValueError('WDC assembler/linker required')
    freeze = json.loads((ROOT/'F_FREEZE.json').read_text(encoding='utf-8'))
    f = (ROOT/'firmware/payload/STR8N-F-BOOT-4096.bin').read_bytes()
    assert len(f) == 4096 and sha(f) == freeze['sha256']
    for filename, digest in freeze['sources'].items():
        assert sha((ROOT/filename).read_bytes()) == digest, filename
    bs = equs(ROOT/'src/core/boot-symbols.inc')
    ws = equs(ROOT/'src/core/worker-public-symbols.inc')
    crc = binascii.crc_hqx(f, 0xffff)
    private = dict(WB_F_READ=ws['V2W_READ'], WB_F_EXECUTE=ws['V2W_EXECUTE'],
                   WB_F_RECOVERY=bs['BOOT_RECOVERY'],
                   WB_F_CRC_LO=crc & 255, WB_F_CRC_HI=crc >> 8)
    out.mkdir(parents=True)
    source_hashes = {}
    branch_layout = {}
    for filename in ('workbench.asm', 'workbench-loader.asm',
                     'workbench-layout.inc', 'workbench-sram.inc'):
        path = ROOT/'monitors/src'/filename
        body = path.read_text(encoding='utf-8')
        body = body.replace('WB_GENERATION_TEXT',generation_text)
        source_hashes[path.relative_to(ROOT).as_posix()] = sha(path.read_bytes())
        if filename != 'workbench-layout.inc':
            body, info = conservative_branches(body, 'WB_LONG_'+re.sub(r'\W', '_', filename)+'_')
            branch_layout[filename] = info
        (out/filename).write_text(body, encoding='utf-8', newline='\n')
    shutil.copyfile(ROOT/'src/include/str8n-v2-public.inc', out/'str8n-v2-public.inc')
    (out/'workbench-foundation.inc').write_text(
        ''.join(f'{name} EQU ${value:04X}\n' for name, value in private.items()),
        encoding='ascii', newline='\n')
    logs = []
    objects = {}
    for stem, origin, end_symbol in (('workbench', 0x5000, 'W_CODE_END'),
                                    ('workbench-loader', 0x0200, 'WL_END')):
        for command in ([assembler, '-G', '-L', '-S', '-W', stem+'.asm'],
                        [linker, '-g', '-s', '-t', f'-c{origin:04X}', '-hm19', '-j',
                         '-o', stem+'.s19', stem+'.obj']):
            done = subprocess.run(command, cwd=out, capture_output=True,
                                  text=True, encoding='utf-8')
            logs.append(dict(command=command, returncode=done.returncode,
                             stdout=done.stdout, stderr=done.stderr))
            (out/'build-log.json').write_text(json.dumps(logs, indent=2)+'\n',
                                              encoding='utf-8', newline='\n')
            if done.returncode:
                raise RuntimeError('WDC build failed; inspect '+str(out/'build-log.json'))
        symbols = {name: int(value, 16) for value, name in re.findall(
            r'^\s*([0-9A-Fa-f]{8})\s+(\w+)\s*$',
            (out/(stem+'.map')).read_text(encoding='utf-8'), re.M)}
        memory = cells(out/(stem+'.s19'))
        assert set(memory) == set(range(origin, symbols[end_symbol]))
        objects[stem] = (bytes(memory[a] for a in range(origin, symbols[end_symbol])), symbols)
    body, symbols = objects['workbench']
    loader, _ = objects['workbench-loader']
    assert len(loader) <= 256, 'Loader overlaps source module at 0300'
    assert len(body) <= 5118, 'Module overlaps its CRC trailer at 63FE'
    assert body[:8] == b'MW\x01\x14PR05'
    for offset, target in ((8, 'W_DISPATCH'), (11, 'W_SHELL')):
        assert body[offset:offset+3] == b'\x4c'+symbols[target].to_bytes(2, 'little')
    module = body+b'\xff'*(5118-len(body))
    module += binascii.crc_hqx(module, 0xffff).to_bytes(2, 'big')
    assert len(module) == 5120 and binascii.crc_hqx(module, 0xffff) == 0
    image = loader+b'\xff'*(256-len(loader))+module
    assert len(image) == 5376 and 0x0200+len(image) == 0x1700
    filename = 'MONA-WORKBENCH-WB1-g'+generation_text+'-RAM.bin'
    (out/filename).write_bytes(image)
    (out/'WB1-module-5000.bin').write_bytes(module)
    report = dict(schema=1, component='Mona RAM workbench', interface='WB1',
                  generation=generation_text, status='BUILD_ONLY_NOT_EXECUTION_QUALIFIED',
                  artifact=dict(filename=filename, bytes=len(image), sha256=sha(image)),
                  module=dict(origin='5000', bytes=5120, linked_bytes=len(body),
                              linked_end=f'{symbols["W_CODE_END"]:04X}',
                              sha256=sha(module), crc='CCITT FFFF; big-endian trailer; residue zero',
                              header='MW 01 14 PR05', command_entry='5008', shell_entry='500B'),
                  bridge_client_RAM_floor='6550: lowest destination page; Mona RAM declares code end rounded up',
                  foundation_sha256=sha(f), private_adapter=private,
                  loader_bytes=len(loader), sources=source_hashes,
                  RAM_borrowed=['0200-16FF transfer staging', '5000-63FF module', '6400-66FF state'],
                  application_RAM_while_loaded='0200-4FFF', system_ZP=['E0-E1', 'E2-E3', 'E6-E7', 'EA'],
                  entry='REC> L raw RAM BIN; existing Mona g4 has no L/module dispatch',
                  return_path='Q -> public RAM HOLD -> active monitor, or recovery if unavailable',
                  monitor_A_B_changed=False, F_rebuilt=False, hardware_access=False,
                  flash_writes=False, journal_writes=False, SRAM_writes=False,
                  EDU='Explicit session OFF/ON; ON is a wiring selection, not presence proof',
                  SPI=dict(profile='EDU Rev D PB0 SCK/PB1 MOSI/PB2 SRAM CS/PB5 MISO; PB3 CS kept high',
                           opcodes=['05 RDMR', '03 READ'], automatic_probe=False,
                           layout='SS/01/08 primary fixed 64KiB zero-generation; SS/02/08 nonzero generation and labelled fallback; CRC/commit/reserved fields required',
                           PREP='Explicit disabled-CB flag acknowledgment; not automatic',
                           prior_input_pin_output_latch='Unreadable: sampled ORB restoration only'),
                  records=dict(format='SR/01; no payload checksum', scan='bytewise 8000-DFFF, selected bank',
                               table=True, restore=True, restore_names='unique within selected bank',
                               store=False, run='Explicit R without L; old program ABI not thereby qualified'),
                  planned=['Mona core dispatch and native L', 'Store', 'APPS and maintenance/config/opaque routing',
                           'Source/ASM/DEBUG', 'WORKSPACE allocation review and separate append-only messages'],
                  build_passes=1, assembler_linker_invocations=len(logs),
                  branch_layout=branch_layout, CPU_simulations=0)
    (out/'manifest.json').write_text(json.dumps(report, indent=2)+'\n', encoding='utf-8', newline='\n')
    print(json.dumps(dict(filename=filename, bytes=len(image), linked_bytes=len(body),
                          free_module_bytes=5118-len(body), sha256=sha(image),
                          status=report['status']), indent=2))
    return report


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--generation', type=lambda value:int(value,0), default=1)
    args=parser.parse_args()
    build(args.out,args.generation)
