# 2512 current MON tools: installed and accepted

October 30, 2026. **65C02 / FT245**, MON B g8, services g4, WB2 g5 and
PROGRAM/SP1 g1. [Public receipt](../monitors/validation/2512-services-g4-install.json),
[approved five-erase scope](2512_SERVICES_G4_INSTALL_SCOPE.md),
[preceding RAM acceptance](2512_SERVICES_G4_RAM_ACCEPTANCE.md).

## Installed workflow

Native M1/M2/M3/W, APPS inventory and TIME passed. Actual `MAINT LOAD` from
the new WF/03 board bundle passed over a valid older WB3 RAM cache, with
leading/trailing spaces, and with an empty cache. Extra arguments were
refused before loading. Cached MAINT/FLASH opened WB5; CLOCK read/refreshed
and returned. Explicit EDU/SRAM/WORK queries, SS1 PROGRAM Table,
`BATCH T;T`, malformed separators, missing-name Restore and AUTO preview/NO
passed. No PROGRAM record was stored or retained program executed.

The physical RESET then selected saved B/g8 without a chooser key. It left
owner RAM/ZP intact before any helper upload. Native map/wear/APPS/TIME and
all flash postimages passed again. Final owner RAM0200-66FF and ZP00-DF were
restored and independently read back, original MON B/B3> returned, COM4
released. Both MON slots retain their original g8 bytes; this new installed
workflow was exercised through B.

At B3>, use **MAINT LOAD** to deliberately load the new board-stored tools.
Exact owner-RAM restoration also restores its valid older WB3 cache; bare
MAINT can reuse that cache. Q returns from tools to B3>; Q at B3> returns
to recovery. The saved default remains B bound to generation 8.

## Writes and preservation

Exactly five sector erases: B2:8/9/A, B3:E and native B3:C journal rotation.
Five new journal rows: DF00 intent/seq1029, C000 root/seq1030, then
C100/C200/C300 through seq1033. Every component and journal result matched
its sealed postimage before the next request. No retry or extra erase.

The 16 original C records are durably archived on the host; they are no
longer on chip. All 15 original D records remain byte-identical on chip.
Latest boot policy, generation bindings, wear counts and prior-wear flags
carry forward. Final journal: 20 valid rows, C300/seq1033. Counts (decimal):
B2:8=596, B2:9=265, B2:A=13, C=53, D=33, E=28, F=24; MON A=41/B=48.
Other images, golden F, saved B/g8, mask 0F, four 8000 entries and delay remain
unchanged. Original component sectors and complete banks are archived.

Complete 131072-byte SRAM equality:
`580a60e314e7c91703a319f03516bd803f36a8202f773e4206b6d4aa69d227aa`.
PROGRAM, CLOCK/CLK records, header, WORKSPACE and tail are intact. Zero F,
MON A/B or SRAM-data writes; no clock settings, trim/PF acknowledgements,
power cuts, firmware builds or CPU simulations. Other boards were excluded.
The existing native TIME RTC/NTP sampler, schedule, baselines and samples
remain unchanged; its unchanged MON/F identities and B3> context remain
admitted after verified restoration. The shared serial lease is released.

## Release boundary

This closes the current 65C02 RAM and matching board-flash reload gate.
Positive PROGRAM Store/Restore/run on 2609 retains its separate 65C816
emulation receipt; this trial adds no new 65C02 positive write/run or AP/02
flash-app launch. ASM/DBG remain deferred and nonblocking. Full b35 parity,
advanced CLOCK, the sector editor and CONFIG integration remain separate
increments. Foundation v0.3.0, its F image and published downloads are
unchanged. Private raw captures remain in the parent project's
`output/qualification/2512-services-g4-*` directories.
