# 2512 acceptance: Mona g5 and WB1 g2

**Passed 2026-10-29; g5 left installed in A and B, saved default B.**
65C02 / FT245 / COM4 only. [Machine-readable receipt](../monitors/validation/2512-mona-g00000005-wb1-final.json).
The physical RESET booted directly to Mona B generation 00000005. Fresh owner
RAM 0200-66FF and ZP 00-DF were restored and independently read back after that
reset. COM4 is released. Golden N-F 0.3.0 BASE1/PR05 F and published downloads
remain unchanged; no other board was accessed.

## Qualified behavior

- The g5 RAM candidate passed missing-module refusal, core inspection/help,
  RAM-only L/G refusal, and Q back to recovery.
- WB1 g2 passed Table/Restore in its shell and through the g5 bridge. T found
  HELLO0200 at B1:8000, UCHESS at B1:802F and CLOCK at B1:B000, demonstrating a
  bytewise scan rather than sector-start-only recognition.
- HELLO0200 loaded by name/address and ran through public PUTC/HOLD back to
  the active monitor. CLOCK was loaded only, with every RAM byte compared to
  its flash payload; its old private-ABI execution remains unqualified.
- Restore refused the RAM monitor's own code range. Normal M refused the
  module/state and a 4FFF/5000 crossing without a partial write. Deliberate
  corruption of borrowed module padding caused admission refusal; restoring
  the byte restored admission.
- Both ROM slots passed native L first-byte Ctrl-C cancellation to REC>,
  normal WB1 loading, shell Q/HOLD, bridged Table, public HELLO return and
  explicit EDU/SRAM status.
- Read-only SRAM access recognized the existing **primary SS1** layout and
  reported PROGRAM payload 63488 bytes and WORKSPACE capacity 65504 bytes.
  It checked layout CRC/commit/reserved fields without upgrading or formatting.
  No SRAM WRITE/WRMR command was issued. Capacity is not an allocation/free-space
  report. Existing WORKSPACE allocations were not adopted.

## Flash and preservation

| Item | Before | After |
| --- | --- | --- |
| B3:A tracked erase attempts | 38 | 39 |
| B3:B tracked erase attempts | 45 | 46 |
| B3:C / D / F counts | 52 / 32 / 24 | 52 / 32 / 24 |
| Journal sequence / valid records | 1007 /10 | 1010 /13 |
| Default | B, generation4 | B, generation5 |

Two monitor erases total. The only appends were C900/1008 (A wear), CA00/1009
(B wear) and CB00/1010 (same B default bound to the new generation). All ten
old raw records remain exact. Enable mask 15, entries 8/8/8/8, delay, uncertainty
flags and owner images outside A/B are unchanged. Original g4 A/B images have
fresh host backups. All four banks were independently read twice after the
upgrade and matched the sealed postimages. Zero F writes/C/D erases/power cuts.

Owner RAM SHA-256:
`1e1e8f62ac65a68206d8936ce9ce65c871e0428b5114193c65b3ba0c2838dda4`.
Owner ZP SHA-256:
`30b1c0333c3e83a73c1abce7bd3e1fb200edf07207f485910d45cae46f816978`.

## Use the installed checkpoint

Restoring owner RAM deliberately **evicted WB1**. G5 core D/M/!M/G/L/Q remains
available. To use T/R/EDU/SRAM/WORK again:

1. In the existing Python terminal, F2 selects
   `monitors/candidates/wb1-g00000002/MONA-WORKBENCH-WB1-g00000002-RAM.bin`.
2. At `MonaB>`, type `L` and Enter. At `SEND BIN`, press F3.
3. In `WORKBENCH>`, use `EDU ON`, then `SRAM` or `WORK`. T1 lists bank1 records.
4. Q returns to MonaB>; the loaded module is then also available through Mona's
   bridge. Mona's own Q returns REC>.

Loading WB1 intentionally borrows RAM 0200-16FF and 5000-66FF; preserve any live
application data first. Its runtime reserves 5000-66FF, and Restore destinations
are limited to 0200-4FFF. No flash space is silently claimed for persistence.
F4 in the terminal remains recovery-only; manual L followed by F3 works at Mona.

## Evidence limits and next work

Early host runs stopped on an EDU-session expectation and an unanchored prompt
match inside dump ASCII. Owner RAM/ZP was restored after each. The corrected
run passed without rebuilding g5. WB1 alone needed a g2 build to support the
observed legacy SS1 format. No CPU simulator/offline regression group ran.

SS2/fallback layouts, modes 40/80 and other CPU/console profiles were not observed
on hardware. The first explicit guarded PREP acknowledged disabled CB flags;
prior input-pin output-latch values are unreadable, so only sampled ORB
restoration is claimed. There is no full-SRAM before/after hash claim, physical
wear/endurance or battery-health certification. G5's unchanged force flash-byte
path inherits g4 evidence; no new flash-byte test was added.

Store, apps/maintenance/config/opaque command routing, source/ASM/DEBUG and a
separate persistent append-only WORKSPACE message journal remain open. Source
and messages must not overwrite formatted PROGRAM or boot/wear C/D. Inspect
existing WORKSPACE allocation ownership before enabling any such writer.
