# MON A/B: monitor and workbench on BASE1

The Mona name is retired. New runtime banners use **STR8-N / MON A or MON B**,
with their own monitor version and generation. Historical filenames, branch
spelling, g1-g6 binaries and receipts stay intact. The installed g6 still has
the old banner; the source rename takes effect at the next functional build
and install. No monitor binary is included in the published N-F 0.3.0 kit.

STR8N-F stays the frozen 4096-byte bootstrap/recovery foundation. MON A/B
supplies the practical monitor, richer status, applications and workbench.
**A and B remain identical.** Full [2.0b35 capability](MON_B35_PARITY.md) is the
completion target, including BATCH, AUTO T/S/R on flash and SSRAM PROGRAM,
APPS, source/ASM/DEBUG, maintenance/config/opaque access and EDU/SRAM/WORK.

[G6 / WB1 g3 acceptance](MON_AB_G6_2512_ACCEPTANCE.md) records the current 2512
state; see the [command manual](MONA_COMMANDS.md) for implemented commands.
Full parity remains unfinished. Retained legacy images are not automatically
BASE1-compatible; the [compatibility review](MON_AB_COMPATIBILITY_REVIEW.md)
records the entry/private-call conflicts.

The A/B boot path requires the monitor image header, CRC and PR05 contract.
Ordinary opaque images use a configured bank entry. Hardware/service status
and subsystem menus belong in these images, independent of frozen F. Missing
optional hardware returns an explicit error. Persistent messages/metadata use
an admitted append-only WORKSPACE allocation, separate from PROGRAM and the
C/D boot/wear journal. LED/buzzer and other service extensions remain proposed;
they do not expand F's 0.3.0 ABI.
