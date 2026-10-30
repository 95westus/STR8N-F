# MON feature release: finish the usable increment

Owner direction, October 30, 2026: finish and release more features. Retain
2604's working rc1 as the reference while preparing2609. No whole-board clone,
new F generation, historical-branch deletion or public-download replacement.

## Next feature increment

Use hash-pinned MON/g8, services/g4, WB2/g5 and PROGRAM/SP1 artifacts.
The new storage/APPS increment passed2512 RAM acceptance; its flash installation
is still pending. Existing manifest build-only labels remain immutable; later
hardware receipts state which exact variants passed.

Current checkpoint: [2609 installed acceptance](2609_MON_FEATURE_ACCEPTANCE.md)
passed. The original five replacements plus the separately approved D/E
dispatcher repair are closed. Only the narrow dispatcher repair was rebuilt,
once. RTC collection was re-admitted with its unchanged instrument and retained
history. The optional preview packages these exact bytes and the unchanged
Python terminal. Preview 1 is now published. Positive PROGRAM Store/Restore/run
on 2609 [now passed](2609_PROGRAM_POSITIVE_ACCEPTANCE.md), with exact full-SRAM,
owner RAM/ZP and flash preservation. Services g4 now also
[passed RAM qualification on 2512/65C02](2512_SERVICES_G4_RAM_ACCEPTANCE.md);
matching board-flash reload follows its separately approved installation scope.
SOURCE/ASM/DEBUG is follow-on implementation work. See the
[Foundation release path](FOUNDATION_RELEASE_PATH.md) for the remaining package
and CPU/backend qualification boundaries.

Latest owner update, October 30: **resident ASM and DBG are follow-on work
and do not block the current monitor/tools release**. Retain the
[port/qualification plan](MON_ASM_DBG_RELEASE_GATE.md). Finish the current
qualified tool scope and package/verify a new candidate when authorized;
published Foundation and preview downloads stay unchanged.

Deliver one optional monitor/tools preview, separate from frozen N-Fv0.3.0:
Dump/Modify/force guards, map/wear, TIME/CLOCK, flash and PROGRAM Table/Restore,
Store/AUTO, compatible APPS, bounded BATCH, Python terminal and command manual.
Mark the remaining ASM/DEBUG, advanced CLOCK, full FLASH editor and CONFIG
integration as unfinished. Do not advertise complete b35/rc1 replacement yet.

## First concrete gate:2609 RAM readiness

No new firmware build is needed. Use COM8/A10MPQXCA,65C816 emulation, existing
frozen F and the established original-owner escrow. Before borrowing RAM,
admit the latest completed2609 preservation receipt; the first3078bytes retain
that pre-helper escrow authority. Freshly double-read the remaining RAM/ZP and
all banks through the qualified READBACK tool. Stop on changed authority.

Test the g8/services-g3 RAM composite: CPU identity, Dump/Modify and restored
test bytes, protected F/C/D refusals, bank inspection, TIME, maps/wear, APPS
inventory and missing-app refusal. It is not an owner-application launch test.

Then load the existing full WB2/SP1 RAM packet. Its shell Q uses public HOLD,
which normally reenters an active ROM monitor;2609 has no admitted MON slot.
For this trial only, save the actual RAM HOLD jump operand at7E68-7E69 and
temporarily point it to the exact frozen F recovery entryF2AF. Never patch F.
Q can then reach REC>. Reload the RAM monitor, restore and verify the original
HOLD operand before the final READBACK/restoration. No reset is required.

Workbench checks are read-only or cancel-only: help, EDU volatile selection,
SRAM/WORK queries, PROGRAM Table, BATCH returning-command/precheck paths,
missing-name Restore and Store/AUTO preview followed by NO. Never transmit
YES, execute a Store commit, run a retained program, format, delete or reclaim.
Record busy/unavailable refusals honestly; they do not qualify positive SRAM
operation. The positive write/run receipts remain2512-only.

The first completed2609 scope trial preserved everything but found$01 on SRAM
transfer: disabled VIA CB edge flags. A follow-up may use explicit `SRAM PREP`
only through its existing guard, whose non-handshaking reads require CB
interrupts disabled, compatible PCR/ACR and free DDRB pins. PREP acknowledges those disabled VIA flags, with no
SPI clocks or RTC/PF acknowledgement; it never overrides an enabled owner.
Repeat the query and cancel-only preview afterward; do not call refusal a
positive PROGRAM pass.

Independently compare all banks afterward, including C/D/F. Restore/read back
owner0200-66FF/ZP00-DF, restore the public HOLD operand, return to REC>, release
COM8 and retain its existing qualified hourly RTC profile. The serial lease
prevents simultaneous RTC access; defer to a pending collector. No clock set,
trim, PF acknowledgement, EEPROM, flash, SRAM-data or boot-setting writes.

## Installation and release gates

1. Finish the RAM readiness gate above and name every remaining limitation.
2. From its fresh capture, prepare the exact2609 sector/journal scope. Count
   native journal rotation as a real erase and explicitly review any replaced
   raw history. Preserve counts, boot policy, images outside admitted targets,
   owner RAM and external storage. This plan authorizes no flash transaction.
3. After the exact write scope is approved, install/admit the monitor and tools,
   check physical boot/return and the complete preview workflow, then qualify
   the RTC transport for the installed profile without adjusting the clock.
4. Package the verified optional binaries, source references, terminal, manual,
   manifests and precise acceptance limits. Published N-F0.3.0 remains unchanged.
5. Continue source/ASM/DEBUG against2604's intact rc1 reference; retire that
   hardware role only after the replacement workflows pass.

Historic branches/tags and original owner/vendor images remain preserved.
