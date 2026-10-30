# 2512: g6 bank prompts and WB1 g3 Store

**Functionality passed; the original scope was exceeded and history recovered.**
2026-10-29, 65C02/FT245 only. [Receipt](../monitors/validation/2512-mona-g00000006-store-final.json).

G6 remains installed in A and B. Physical RESET selected the saved B default
and displayed `B3>`. Bank selection shows `B0>` through `B3>`; active MON A/B
stays in the banner. All fresh owner RAM 0200-66FF and ZP 00-DF was restored and
read back after reset. COM4 is released. F, other boards and published downloads
remain unchanged.

## Store and prompt tests

WB1 g3's shared RAM module passed these checks through g6 RAM:

- HELP, explicit AREA ownership window and bare-AREA clear.
- Unarmed, protected-bank, out-of-window and malformed-input refusals.
- NO, Ctrl-C and YES-with-extra-text cancellation before programming; CRLF
  command/confirmation handling stayed with the requesting console.
- Three exact SR01 records in B0:9, including non-sector-start addresses,
  duplicate names, an unnamed record, NULL/FF bytes and prompt text in data.
- Occupied-target refusal, Table, duplicate-name Restore refusal, address
  Restore, full payload readback and public HELLO/HOLD return.
- Full bank readback matched the expected temporary records exactly; all
  other flash banks and boot/wear rows were unchanged by Store itself.

Both ROM slots passed the selected-bank prompts, native L Ctrl-C and normal
WB1 load, Q/HOLD, Table/HELP and guarded read-only SS1 SRAM status. Store's
byte-programming test used the RAM monitor; no additional ROM Store write was
performed after cleanup. Its shared module and pinned RAM worker are the same.

B0:9 was restored exactly after testing, using one accounted erase. None of
the three test records remains installed. Store does not erase, allocate space
automatically or append C/D; its source/program records are distinct from the
planned SRAM WORKSPACE message journal. See [Store use](MONA_STORE.md).

## Unplanned D rotation and remediation

The plan counted CF00 as an ordinary fourth append slot. Native CONFIG reserves
that page for a peer-erase intent. CONFIG C B therefore committed CF00/1014,
erased occupied D once, then committed D000/1015. **That D erase was outside
the reviewed zero-C/D-erase scope.** No mutation was blindly retried.

Read-only inspection confirmed valid policy/counters and unchanged images/F.
The old D000/sequence998 raw record had been backed up before any mutation.
A fixed-target RAM helper, guarded by exact A000-DFFF preimage and frozen F,
restored those 256 bytes at blank D100, commit last, without another erase.
Paired full-bank captures verified the result. All thirteen original raw
records are again present, with the old D record relocated to D100. The newest
sequence remains 1015 and default B remains bound to g6. D's real extra erase
is retained as count 33; it was not rolled back or hidden.

| Item | Before | Final |
| --- | --- | --- |
| B0:9 count | 9 | 10 |
| A / B counts | 39 /46 | 40 /47 |
| C / D / F counts | 52 /32 /24 | 52 /33 /24 |
| Journal sequence / valid records | 1010 /13 | 1015 /18 |
| Saved default / generation | B /5 | B /6 |

Actual erases: B0:9, A, B and D once each; three were planned, D was not.
Enable mask 15, entries 8/8/8/8, delay, uncertainty flags and retained metadata
remain the same. The original g5 A/B images are backed up. Full B0/B1/B2 and
B3:8/9/E/F contents remain exact. No SRAM write, power cut or CPU simulation.
See [incident and repair scope](G6_D_ROTATION_REMEDIATION.md).

`tools/native_journal_room.py` now reports ordinary capacity separately from
the reserved intent page. It reports three zero-erase operations on the original
CB00 image, which would reject the four-operation plan, and thirteen on the
recovered current image. Future no-C/D-erase plans must check this before writes.

## Using the installed checkpoint

Owner-RAM restoration evicted WB1. F2 selects
`monitors/candidates/wb1-g00000003/MONA-WORKBENCH-WB1-g00000003-RAM.bin` in the
Python terminal. Type L at `B3>`, then F3 at SEND BIN. Q from WORKBENCH returns
to the active monitor; HELP there exposes AREA/S/T/R and EDU/SRAM/WORK.
Loading intentionally borrows RAM 0200-16FF and 5000-66FF.

Apps/maintenance/config/opaque routing, source/ASM/DEBUG and persistent SRAM
messages remain open. SS1 has live positive status evidence; SS2/fallback,
other SPI modes, arbitrary NMI/DMA concurrency, faults and other CPUs remain
unqualified. AREA supplies an ownership bound, not a record allocator/overlap
map. SR01 has no payload CRC. F remains the frozen foundation.
