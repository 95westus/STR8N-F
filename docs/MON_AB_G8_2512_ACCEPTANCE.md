# 2512 g8: direct M1/W and board-stored CLOCK/MAINT

This records the g8 / WB2 g2-g3 service checkpoint. The later
[WB2 g4 AUTO acceptance](MON_STORE_AUTO_2512_ACCEPTANCE.md) records current
flash Store, final counts, RAM-cache behavior and the 63-byte module remainder.

**Installed and passed on 2026-10-29: 65C02 / FT245 / 2512 only.**
[Current receipt](../monitors/validation/2512-mon-g8-services-repair.json),
[initial receipt](../monitors/validation/2512-mon-g8-services.json),
[RAM gate](../monitors/validation/2512-mon-g8-ram.json),
[scope](MON_AB_G8_2512_SCOPE.md).

Both A/B slots contain STR8-N 0.1.0-dev g00000008 with identical commands.
The saved B default is bound to generation 8; physical RESET/countdown booted B
and reached B3>. M1/W worked afterward without loading the workbench. Every
owner RAM byte 0200-66FF and ZP byte 00-DF then matched the fresh original escrow.
COM4 is released. F remains the exact N-F 0.3.0 g00000001 / BASE1 / PR05 image.
2205, 2604, 2609 and published downloads were untouched.

## What works

- M/M1: two-character sector grid, including known WDC resident recognition.
  M2 gives layout/reservation notes; M3 and W give all 32 tracked erase counts.
  These read-only E services use scratch 6700-69FF and preserve owner RAM/ZP.
- CLOCK: explicitly loaded from the B2 flash bundle, bounded RTC read/refresh
  and Q back to its caller. Real coherent RTC samples were observed. No RTC
  SET/ACK, EEPROM write or clock-policy import was performed; zone is labelled
  unconfigured and health/prior wear retain the shared symbol/caveat.
- MAINT and FLASH: enter the board-stored WB2 workbench, with Q back to the
  active monitor. This is the current storage/hardware front door; the proposed
  full 4KB sector editor/erase/copy and merged CONFIG page remain planned.
- BATCH: the 34-byte returning-command subset, complete separator/allowlist
  precheck, failure stop, data-bank preservation after failure, and ordinary
  module dispatch. It is not full b35 core/app batch parity.
- Existing D/M/!M/G/L/Q implementation retained. The g8 RAM gate additionally
  checked the MAINT-versus-M ambiguity, numeric A-prefixed addresses, actual
  RAM Modify/readback/restore and reserved-region refusal.

The B2 bundle boot entry was exercised via the original g6 monitor's explicit
B2/G8000 before replacing either monitor. Both new ROM slots then passed direct
map/wear, CLOCK loading from flash after deliberate RAM-module invalidation,
CLOCK refresh/return, BATCH, MAINT and FLASH-alias return. The larger module is
loaded only for an explicit tool command; no host BIN is required for those
installed tools. Startup and M1/W do not probe EDU/SPI or load the module.

## Preservation and accounting

The initial installation used exactly five sector replacements: B2:8/9 bundle, B3:E dispatcher, B3:A/B monitors.
Exactly six append-only journal operations: five erase reservations, then the
existing B default's generation 6->8 binding. Original 18 raw rows remain at
their original locations; final 24 valid rows, newest sequence 1021 at D700.
There were no F writes, C/D erases, write retries or power cuts.

| Tracked counter | Before | After |
| --- | ---: | ---: |
| B2:8 | 592 | 593 |
| B2:9 | 261 | 262 |
| B3:E | 25 | 26 |
| B3:A | 40 | 41 |
| B3:B | 47 | 48 |
| B3:C / D / F | 52 / 33 / 24 | 52 / 33 / 24 |

Default B, enable mask 0F, entries 8/8/8/8, delay, uncertainty mask and all other
settings were retained; only its required generation binding changed. B0/B1,
other B2/B3 sectors and all old C/D bytes outside the six admitted blank pages
matched the exact expected images. Sector originals, complete banks and fresh
owner RAM/ZP remain in the private qualification case named by the receipt.

The earlier native inventory was interrupted by an owner-confirmed RESET and
superseded by fresh paired captures. A RAM trial caught MAINT being parsed as
Modify; flash was unchanged and owner RAM restored before the corrected monitor
was rebuilt/requalified. Only affected components were rebuilt. Unchanged
workbench/service/loader bytes were reused by hash. No CPU model, offline test
group or reproduction build was run.

## WORK routing and cancellation repair

The initial acceptance missed two cases. Source review found WORK intercepted
by the single-letter W service. A positive BATCH test then showed ESC remained
queued because frozen F's cancel facade latches Ctrl-C only. Neither failure
required changing F or the monitors. E g2 corrects dispatch; WB2 g3 inspects
queued ESC without consuming other typeahead, and resets cancellation before
printing the result. The unchanged loader and service support code were reused.

The [reviewed repair](MON_AB_G8_WORK_REPAIR_SCOPE.md) passed in RAM first:
ESC and Ctrl-C each stopped Table inside BATCH with result $03 and the following
B1 command unexecuted. Provider-only and module-only CRC faults were refused;
restoring their padding restored admission. WORK and SRAM reached the hardware
status adapter. Its busy-pin guard refused probing in this session; no new
positive SSRAM capacity or PROGRAM/WORKSPACE write claim is made.

Three additional replacements followed: B2:8/9 and B3:E, with three append-only
reservations and no write retry. Installed MON B passed WORK versus W, M1/M2/W,
APPS, checked CLOCK reload/refresh/return, MAINT return and both cancellation
keys. Complete readback matched every expected bank; all previous 24 journal
rows remain at their original offsets. Owner RAM/ZP were restored and verified
again. COM4 is released at B3> / MON B g8.

Total for this update: **eight erases and nine appends**, including the initial
five/six above. Final journal: **27 valid rows, sequence 1024 at DA00**.
Final tracked counts: **B2:8=594, B2:9=263, E=27, A=41, B=48, C=52, D=33, F=24**.
Default B/g8, mask0F, entries8/8/8/8 and the remaining boot policy are unchanged
by this repair. F, A/B and boot policy are the same as the physical default-boot
check, so no additional RESET was requested. There were zero F writes, C/D
erases, SPI writes, RTC data writes or power cuts. B0/B1 and all other images
remain intact. The current receipt records final hashes and both live gates.

## Space and ownership

| Component | Region bytes | Linked bytes | Reserved bytes | Free bytes |
| --- | ---: | ---: | ---: | ---: |
| Frozen F | 4096 | 3697 | 32 vectors/tail | **367** |
| MON A/B, each | 4096 | 3901 | 128 header/reservation | **67** |
| E dispatcher g2 | 4096 | 3113 | 2 CRC | **981** |
| WB2 g3 code block | 7168 | 6893 | 2 CRC | **273** |

The B2 bundle occupies 8192 bytes and includes a one-page RAM loader and 512-byte
trailing pad. WB2 explicitly borrows 4800-66FF; application RAM while loaded is
0200-47FF. Against the initial 9KB prototype, this saves 2KB RAM and one allocated
flash sector. The loader at 7000 uses 237 bytes and never overlaps the frozen
7800-7BE7 worker. These free tails are inside existing images, not declarations
that owner sectors or SRAM allocations are available.

Owner restoration deliberately evicts WB2. MAINT/CLOCK reload it from flash;
M1/W remain usable without that RAM borrowing. The RAM-only composite used for
qualification occupies 0200-2FFF and protects that region from ordinary M/R.

## Remaining work

Full [b35 parity](MON_B35_PARITY.md) remains open: FLASH's sector buffer/editor
and journaled erase/copy, merged MAINT/CONFIG navigation, advanced CLOCK,
AUTO flash/SSRAM T/S/R, compatible app discovery, source/ASM/DEBUG, rich board
startup and separate WORKSPACE messages. Existing legacy source/program/RTC
assets were retained; their private calls are not declared BASE1-compatible.
PROGRAM writes, WORKSPACE allocation/formatting and additional CPU/console modes
were not newly qualified in this increment.
