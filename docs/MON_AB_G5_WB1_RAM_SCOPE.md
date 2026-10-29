# Proposed g5 / WB1 RAM trial: 2512

**Review only: not authorization, an armed receiver or a test result.**
2512/COM4/FT245 USB serial A10MQFLCA only, after idle/port-free confirmation.
Leave 2205,2604,2609 and other ports alone. Preserve installed g4, golden F,
images, boot settings, all boot/wear history and original owner RAM/ZP.
Zero flash writes/erases, journal appends, SRAM writes, formatting, power cuts
or RTC access. No old install budget is reused.

Use exact g5 RAM and WB1 RAM hashes in [the manual](MONA_WORKBENCH_WB1.md).
A/B candidates are excluded. Native L from g5 ROM remains a later check; the
RAM variant deliberately refuses L/G.

1. Acquire the shared serial lease and verify USB identity. From installed
   ROM g4, capture fresh owner RAM 0200-66FF and ZP 00-DF with native D in bounded
   2KiB blocks **before any helper or RAM BIN**. Capture all four flash banks
   twice and live boot settings. Verify golden F, g4 and repeated readback
   equality; stop on mismatch. Old receipt RAM does not replace fresh escrow.
2. Load g5 RAM via REC>. Check identity/help/V/D, absent-module refusal, L/G
   refusal and Q to REC>. No automatic SPI/RTC read should occur.
3. Load WB1 RAM. Check identity, bounded input, data-bank selection, T1 and
   scan cancellation. Compare listings with fresh bank files. Test EDU OFF
   status and SRAM/WORK refusal without bus access.
4. Test load-only R by name/address, then independently compare destination
   with archived payload. Test malformed/range refusals; claim duplicate/pending
   cases only if present in actual inventory. Do not create flash fixtures.
5. Optionally run B1:8000 HELLO0200 only if fresh bytes exactly match this
   reviewed 23-byte public PUTC/HOLD program:
   `A94F206D7EA94B206D7EA90D206D7EA90A206D7E4C677E`.
   Require OK then return to installed g4. CLOCK and other legacy apps stay
   load-only; header validity is not private-ABI qualification.
6. Select EDU ON for the explicit RevD profile. Retain guard-register values;
   a busy guard is a valid refusal, not permission to reconfigure the VIA.
   Only separately acknowledged SRAM PREP may clear disabled CB flags. If
   reads pass, repeat SRAM and WORK and compare raw SS2 layout/CRC/boundary
   against reported capacities. Label fallback/absent/invalid paths honestly.
   No PROGRAM/WORKSPACE write or allocation is included. Record the sampled
   ORB/hidden-input-latch limitation; foreground bus ownership is required.
7. Return via installed g4 to REC> and load g5 RAM while WB1 remains at5000.
   Test bridged T/R/EDU/SRAM/WORK. R1 HELLO0200 L must refuse the RAM-monitor
   overlap. If fresh CLOCK remains at B1:B000/load2000/length2FE2, load-only
   R1 B000 L may exercise2000-4FE1; dump/compare all bytes and never run it.
8. Confirm normal M refuses module/state targets and a 4FFF/5000 crossing
   before any write. Optionally !M only borrowed padding63FD, verify corrupted
   module admission refuses, restore its exact original byte and recheck.
   Forced I/O/system/flash edits are excluded.
9. Independently recapture all four flash banks and require baseline equality,
   including every C/D page and F; verify boot policy/counts. Restore original
   owner RAM 0200-66FF and ZP 00-DF using a reviewed RAM-only restore path, then
   read/compare every byte from installed ROM g4. This evicts WB1 deliberately.
   Leave g4 prompt or REC> as recorded, release COM4 and save a private receipt.

Missing hardware, guard refusals and unobserved paths remain explicit limits.
Capacity is not free space; EDU ON is not presence proof. No battery/endurance,
816, fault-injection, persistent message-writer or g5 installation claim follows
from this RAM trial. Release kit/downloads stay unchanged.
