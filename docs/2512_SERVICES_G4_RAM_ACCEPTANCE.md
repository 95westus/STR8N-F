# 2512 services g4 / WB5 RAM qualification: passed

October 30, 2026. **65C02 / FT245**, installed MON B g8 and frozen N-F
v0.3.0 g1 / BASE1 / PR05. [Hash-only receipt](../monitors/validation/2512-services-g4-RAM.json),
[RAM scope](2512_SERVICES_G4_RAM_SCOPE.md).

The exact unmodified g4 RAM dispatcher passed M1/M2/M3/W, APPS inventory
and missing-app refusal. A separate ordinary-RAM bridge called its public
command entry; the dispatcher and its loader were not patched. Cached
MAINT/FLASH opened WB2 g5; CLOCK read the RTC, refreshed and returned through
public HOLD to the installed MON B. WB5/SP1 passed guarded EDU/SRAM/WORK
queries, SS1 PROGRAM Table, bounded `BATCH T;T`, malformed separators,
missing-name Restore and AUTO Store preview followed by NO.

`MAINT LOAD` and spaced syntax consumed LOAD, selected the forced loader and
correctly refused 2512's older WF/02 flash bundle before calling the workbench.
An extra argument was refused before loading. This qualifies g4's RAM path
and the actual old-bundle refusal. Successful reload from a matching new
board-flash bundle remains the next [installation gate](2512_SERVICES_G4_INSTALL_SCOPE.md).
This trial adds no positive PROGRAM Store/run, AP/02 launch or ASM/DBG pass.

All four flash banks were read twice before and twice afterward: exact
equality, including F and all C/D bytes. The journal remains at DE00/seq1028,
31 valid rows, saved B/g8; boot policy and wear counts are unchanged.
The complete 131072-byte SRAM matches before/after:
`580a60e314e7c91703a319f03516bd803f36a8202f773e4206b6d4aa69d227aa`.
PROGRAM, retained CLOCK/CLK images, WORKSPACE and the primary header remain
intact. There were zero flash/journal/SRAM-data/WORKSPACE writes, clock
settings, trim/PF acknowledgements, resets, power cuts, firmware builds or
CPU simulations. Other boards were excluded.

Owner RAM0200-66FF and ZP00-DF were freshly double-captured through native
Dump before any helper upload, restored through READBACK and independently
compared again through native Dump. Original MON B/B3> returned; COM4 was
released. The existing RTC/NTP sampler, schedule, baselines and samples remain
unchanged. The first attempt only encountered the collector's busy lease;
it opened no port. The successful retry waited until the collector finished.

Private raw captures remain under the parent project's
`output/qualification/2512-services-g4-RAM-20261030-r2`; the public receipt
contains hashes and results only. The paired install plan has a separate
owner approval; this RAM acceptance grants no additional erase allowance.
