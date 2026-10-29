# Mona g4 install on 2512: reviewed scope

Completed [acceptance](MON_AB_G4_2512_ACCEPTANCE.md) is separate from this
original install scope. Its initial physical-default expectation exposed the
old saved generation pin; the owner separately approved the
[one-record binding update](MON_AB_G4_DEFAULT_BINDING_SCOPE.md).

The owner requested "flash 2512", selected "Build Dump/Modify first, then
install", and added forced Modify with "Keep F and C/D protected; force other
regions". This scope makes that installation concrete. A/B remain identical;
leave both g4 images installed, keep the existing B default, and finish ready
at MonaB>. No other board is included.

## Images and write budget

Mona **0.1.0-dev g00000004**, exact 4096-byte MI/01 A/B images, PR05. G3 was
built once for Dump/Modify but not installed; the added force request required
one g4 build. There is no reproduction build or CPU simulation. G4 retains
TIME, normal M and hex/ASCII D; L, maps and DEBUG are still planned.

| Image | Destination | SHA-256 |
| --- | --- | --- |
| A | B3:A000-AFFF | `eb0eebc1b57997a407bfefc5a7113c7ebc42d42d5568df1131e0c9226ca4e3ee` |
| B | B3:B000-BFFF | `a3c2768455a2cd2f5684441909c99779afcefccaeaae9ead5730bedf661ce71f` |
| RAM, 3891 bytes | 0200-1132, temporary | `309936eed0896f9b3e3f7c5d40daa5e96228a0c9346a87daac9f7bc3bfa6d661` |

Exactly **two monitor-sector erases**, A then B, with two append-only erase
reservations and **zero C/D erases or F writes**. Frozen F must match
`8f4d35ac66730daa773515980983fcf442be3b1bdf1e523d3752ec3615657cc1`.
Latest checkpoint forecast, subject to fresh device admission:

| Step | Append | Sequence | A/B tracked counts |
| --- | --- | --- | --- |
| Before | seven retained records | 1004 | 37 / 44 |
| Install A | C600 | 1005 | 38 / 44 |
| Install B | C700 | 1006 | 38 / 45 |

C/D/F stay 52/32/24; all other counts, old record bytes, default B, enable mask
15, entries 8/8/8/8 and prior-wear uncertainty stay unchanged. No CONFIG/default
save, journal rotation/reset, power cut or unrelated opaque-image write occurs.
An admission mismatch or insufficient append space stops before programming.

## Real byte-program check within the two replacement sectors

Each final Mona image has install-check byte **FE at offset 18 hex** (24 decimal).
This byte is outside F's CRC and admission fields; it is not a public ABI flag.
The remaining bytes are the exact assembled g4 image. Header packaging added
this byte without invoking the assembler again, with before/after hashes in
the candidate manifest.

The OPAQUE install first writes a staging image with that one byte left FF.
OPAQUE skips programming FF, so this cell remains fresh after the reviewed
sector erase. Once the staged monitor boots, issue its native `!M A018 FE` or
`!M B018 FE`. This exercises real 1-to-0 programming of a fresh byte, no erase,
and produces the exact final candidate SHA. It uses no extra owner sector and
adds no erase reservation. All stages and the final byte are read back.

SST programming requirements still apply: a logical 1-to-0 test alone is not
manufacturer approval to reprogram previously programmed bytes. Qualification
uses only the fresh install-check cells. See the Microchip
[SST39SF010A/020A/040 data sheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MPD/ProductDocuments/DataSheets/SST39SF010A-SST39SF020A-SST39SF040-Data-Sheet-DS20005022.pdf).

## Preservation and execution order

1. Verify COM4's 2512 USB identity, acquire the shared lease, admit REC>, capture
   all banks independently twice and back up both original monitor sectors.
   Establish owner RAM/ZP escrow from the latest verified g2 closeout and idle
   continuity; check live ZP and the RAM suffix beyond the readback helper.
   Stop on a mismatch. Do not call a post-helper prefix an original capture.
2. Run exact g4 RAM first. Exercise D/ASCII and a range longer than 256 bytes,
   normal M/readback and complete-command refusals, RAM-image self-protection,
   TIME naming, cancel/Q, and safe force cases. Temporary ordinary edits use
   $2000-$2007 and owner ZP $00DF, then restore their originals.
3. Force cases may use an inactive stack byte $0120, dormant service RAM $6800
   and the force writer's scratch area, with test bytes restored. An I/O test
   may write the unchanged observed VIA DDRA value; do not reconfigure pins.
   Test flash no-op, forbidden 0-to-1 and C/D/F refusal without programming any
   original owner image. Do not deliberately overwrite active stack frames,
   vectors, worker code, bank-control I/O or the running monitor.
4. Independently verify unchanged flash and restore/read back owner RAM/ZP
   before installing A. Bind each OPAQUE request to fresh target preimages and
   its sealed expected journal snapshot. No automatic flash retry or third erase.
5. Boot A through F's validator; exercise core editing/readback, TIME, Q and
   its one-byte install check. Verify complete B3 against the sealed A result.
   Install B similarly; request one physical RESET with its receiver ready to
   observe the saved B default and g4 startup. Complete B's install check and
   exercise A/B handoff. Preserve boot policy throughout.
6. Independently compare final banks twice. Require only A/B and the two planned
   append pages to differ from the original capture. Restore/read back original
   owner RAM $0200-$66FF and ZP $00-$DF, then enter Mona B and release COM4.
   Keep original A/B and all evidence on the host.

Normal M stays limited to owner ZP/RAM. !M deliberately permits dangerous
system/stack/I/O edits outside golden F and C/D; its raw stores have no automatic
readback, since reading I/O can itself act on the device. Such edits may stop
the monitor or change the selected hardware bank. A flash program failure halts
in RAM; do not fetch ROM while the chip's state is unverified. These dangerous
cases are not part of the live test scope.
