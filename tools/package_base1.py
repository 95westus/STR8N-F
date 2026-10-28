"""Package the existing BASE1 candidate files; no builds, models or devices."""
import argparse
import hashlib
import json
import shutil
import zipfile
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1]
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()


def package(out):
    out=Path(out).resolve()
    if out.exists():raise ValueError('Use a fresh output directory')
    fw=json.loads((ROOT/'firmware/minimal-manifest.json').read_text())
    engine=ROOT/'migrator/payload'
    archive=engine
    em=json.loads((engine/'engine-manifest.json').read_text())
    am=json.loads((archive/'archive-manifest.json').read_text())
    assert fw['passed'] and not fw['execution_qualified']
    from verify_base1 import verify
    verify(ROOT)
    assert em['template_sha256']==sha(engine/'template.bin')
    assert am['archive_sha256']==sha(archive/'archive.bin')
    assert em['source_sha256']==sha(ROOT/'migrator/nf-migrate.asm')
    assert am['source_sha256']==sha(ROOT/'migrator/nf-archive.asm')
    for name,info in fw['artifacts'].items():
        assert sha(ROOT/'firmware/payload'/name)==info['sha256']
        assert (ROOT/'firmware/payload'/name).stat().st_size==info['bytes']
    f=ROOT/'firmware/payload/STR8N-F-BOOT-4096.bin'
    assert f.stat().st_size==4096 and sha(f)==fw['F_sha256']
    trial_path='validation/console-2512-hardware.json'
    trial=json.loads((ROOT/trial_path).read_text(encoding='utf-8'))
    assert trial['passed'] and trial['no_flashing'] and not trial['BASE1_firmware_qualified']
    for rel,digest in trial['tested_files'].items():
        assert sha(ROOT/rel)==digest,'2512 evidence no longer matches '+rel
    out.mkdir(parents=True)
    kit=out/'STR8N-F-BASE1-candidate'
    kit.mkdir()
    for name in fw['artifacts']:
        dest=kit/'firmware/payload'/name
        dest.parent.mkdir(parents=True,exist_ok=True)
        shutil.copyfile(ROOT/'firmware/payload'/name,dest)
    shutil.copyfile(ROOT/'docs/START_BASE1.md',kit/'README.md')
    for rel in ('LICENSE','layout.json','release.json','checkpoint.json','identity.json','F_FREEZE.json',
                'docs/MINIMAL_RELEASE.md','docs/OPAQUE_HOST.md','docs/RECOVERY_BASE1.md',
                'docs/F_IDENTITY.md','docs/ISSUES_RESOLVED.md','docs/RELEASE_STATUS.md','docs/RAM_MAP.md',
                'docs/SERIAL_CONSOLE.md','requirements-console.txt',
                'tools/nf_console.py','tools/console_core.py','validation/console-host-checks.json',
                trial_path,
                'firmware/minimal-manifest.json','migration-host/README.md',
                'migration-host/nf_migrate.py','migration-host/nf_migrate_live.py',
                'tools/nf_opaque.py','tools/nf_recovery.py','tools/oip.py','tools/boot_identity.py',
                'tools/map_catalog.py','tools/verify_base1.py','migrator/PROTOCOL.md'):
        dest=kit/rel;dest.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(ROOT/rel,dest)
        if rel=='migration-host/README.md':
            text=dest.read_text(encoding='utf-8').replace('../migrator/payload/','../migrator/')
            dest.write_text(text,encoding='utf-8',newline='\n')
    for folder,name,dest in ((engine,'template.bin','migrator/template.bin'),
                             (engine,'engine-manifest.json','migrator/engine-manifest.json'),
                             (archive,'archive.bin','migrator/archive.bin'),
                             (archive,'archive-manifest.json','migrator/archive-manifest.json')):
        target=kit/dest;target.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(folder/name,target)
    files={p.relative_to(kit).as_posix():dict(bytes=p.stat().st_size,sha256=sha(p))
           for p in sorted(kit.rglob('*')) if p.is_file()}
    manifest=dict(project='STR8N-F',profile='BASE1',status='unpublished-candidate',
                  execution_qualified=False,hardware_qualified=False,F_bytes=4096,
                  F_sha256=sha(f),host_console_version='0.1.0',
                  console_serial_trial=dict(board='2512',existing_firmware='b15',passed=True,
                      evidence=trial_path,physical_keypresses_verified=False,
                      BASE1_firmware_qualified=False),files=files)
    (kit/'MANIFEST.json').write_text(json.dumps(manifest,indent=2)+'\n',encoding='utf-8')
    zip_path=out/'STR8N-F-BASE1-candidate.zip'
    with zipfile.ZipFile(zip_path,'x',zipfile.ZIP_DEFLATED,compresslevel=9) as z:
        for path in sorted(kit.rglob('*')):
            if path.is_file():z.write(path,path.relative_to(out).as_posix())
    # Also provide the exact 4K programmer image directly, outside the ZIP.
    direct=out/f.name;shutil.copyfile(f,direct)
    for path in (zip_path,direct):
        path.with_suffix(path.suffix+'.sha256').write_text(sha(path)+'  '+path.name+'\n',encoding='ascii')
    print('Saved BASE1 candidate kit and exact 4096-byte F; unpublished, hardware acceptance pending')
    return manifest


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--out',type=Path,required=True)
    args=parser.parse_args()
    package(args.out)
