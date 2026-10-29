# Mona g4 installed on 2512

**Passed, 2026-10-29.** Mona **0.1.0-dev g00000004** is installed in both
B3:A/B on **2512 / 65C02 / FT245**. Both have identical commands. Physical
RESET with no chooser key boots saved default B and reaches **MonaB>**.
COM4 is released. See the [command manual](MONA_COMMANDS.md) and
[final receipt](../monitors/validation/2512-mona-g00000004-final.json).

## Delivered and tested

- D now displays aligned hex/ASCII and accepts non-I/O ranges beyond 256 bytes.
  A 257-byte range and cancellation of a long dump passed; paging/continuation
  remain planned.
- M edits 1-8 bytes of owner ZP/RAM after complete parse/range validation,
  verifies writes and displays independently read bytes. Invalid trailing data,
  excess/wide byte tokens, ZP/RAM boundary crossings and protected regions
  refused without changing a valid-looking prefix. The RAM candidate protected
  its own code pages. Temporary owner RAM/ZP edits were restored.
- !M forced writes passed in an inactive stack area, dormant service RAM and
  its own primary writer area, using the alternate writer. An I/O test wrote
  the same observed VIA DDRA value; subsequent TIME observed the same value.
- Flash no-op and whole-unit 0-to-1 refusal passed without changing an original
  owner image. B3:C/D/F and crossing-boundary refusals passed. Native !M then
  programmed fresh **A018 and B018, FF to FE**, within the two replacement
  sectors, and final images matched their canonical hashes exactly.
- TIME replaces g2's temporary T clock alias. Normal RTC reads, status, help,
  bank selection, Ctrl-C/ESC, Q to REC>, F-admitted A/B entry and B-to-A-to-B
  handoff passed. No old debugger/provider shim was installed.

This is explicit force: ordinary M retains its restrictions. !M has no erase
path and no automatic raw I/O readback. Dangerous writes to active stack frames,
live vectors/worker/bank-control registers or executing code were not injected.
Fresh-cell flash programming was tested; manufacturer-supported repeated
programming of already programmed bytes is not claimed.

## Writes, history and backups

| Action | Journal page / sequence | Erases |
| --- | --- | --- |
| Replace A, then native install-check byte | C600 / 1005 | One B3:A |
| Replace B, then native install-check byte | C700 / 1006 | One B3:B |
| Approved CONFIG C B generation binding | C800 / 1007 | None |

Final tracked counts, decimal: **A=38, B=45, C=52, D=32, F=24**. Only A and B
increased, once each. All seven original records remain exact; the two erase
reservations and one separately approved default-binding record bring the
total to ten. No C/D erase, F write, power cut or other-board access occurred.
The boot default remains B, enabled mask 15 and entries 8/8/8/8. Only the
approved saved monitor-generation binding changed, **8000000F to 00000004**.

Independent paired full-bank captures verified preservation. Apart from A/B
and those three append pages, every flash byte matches the original. Original
A/B and paired complete-board backups remain in the private qualification
case; original owner/vendor images are not published with the source.

Original owner RAM **$0200-$66FF** and ZP **$00-$DF** were restored and checked
by the readback service. After the final physical default boot, Mona D read
every owner RAM/ZP byte again in bounded blocks, matching the originals exactly.
Escrow came from the latest verified g2 closeout and idle continuity; live ZP
and the suffix beyond the helper were checked before further uploads. No
post-helper prefix was mislabelled as an original capture.

Frozen F remains SHA-256
`8f4d35ac66730daa773515980983fcf442be3b1bdf1e523d3752ec3615657cc1`.
Published N-F downloads, tags and F sources were unchanged. 2205, 2604 and 2609
were not accessed.

## Issues resolved during closeout

The first physical default check returned to REC>. This was F's intended
generation guard: preserved default B still pinned the old **8000000F** image.
The install harness had overlooked that binding. Both new images were verified
through explicit F admission, and owner RAM was restored before the additional
[binding scope](MON_AB_G4_DEFAULT_BINDING_SCOPE.md) was approved. Exactly one
stock CONFIG `C B` appended C800, retaining B and all counts/entries/history.
The next physical reset booted g4 B successfully.

A single full-RAM text dump exceeded the host's 35-second deadline while still
emitting valid rows. No board write failed. A read-only continuation cancelled/
drained the old dump and verified all RAM in 2KiB blocks plus owner ZP. No
CONFIG command, monitor erase or install-check program was repeated.

G3 was built once for Dump/Modify, but was not installed because the owner then
requested force. G4 was built once with conservative file-local branch sizing;
the WDC assembler/linker accepted all A/B/RAM outputs. This sizes assembly
branches, not CPU simulation. Each ROM payload is **3900 bytes**, leaving
**68 bytes** in its slot. A packaging-only header revision set the final
install-check byte FE without another assembler run. The staging FF-to-FE
operation exercised the requested native flash path after a fresh erase,
using no extra sector. The candidate manifest records both package hashes.

## Qualification boundary

65C02/FT245 only. A/B were independently admitted through frozen F; B also
passed physical saved-default startup. No physical A-default change was made.
No 65C816, alternate console, application debug session, forced bus failure,
electrical interruption or worn-sector fault was tested. L, maps, named-record
tools, interactive Modify, debugger and full profile-driven startup remain
planned. G4's build manifest retains creation-time unqualified labels; the
separate hardware receipts qualify its exact final hashes within this scope.
