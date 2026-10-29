# 2512 g8/services: preservation and installation scope

Prepared 2026-10-29 from the owner's instructions to update CLOCK/MAINT on
2512 and continue conserving flash/RAM, flashing as needed. 2205, 2604, 2609,
their ports and published N-F downloads remain excluded. F stays frozen.

## RAM gate first

Use only COM4 / FT245 A10MQFLCA. Before loading any helper, capture fresh owner
RAM 0200-66FF and ZP00-DF through installed g6's native D. Read all four banks
twice with the matching readback helper and compare the complete images,
journal and exact F. An earlier native inventory was interrupted by an
owner-confirmed RESET; its complete first pass is retained, not called a
completed paired capture. The new capture supersedes it for write planning.

Load the exact WB2 g2 RAM candidate and g8+RAM-services composite. Test bounded
BATCH completion/failure/cancellation; M1/M2/M3/W; known WDC resident/sector tags
against the captured bytes; all 32 tracked erase counters against the newest
valid raw journal row; module/provider CRC refusal and repaired admission;
ordinary M reservation boundaries; CLOCK read/refresh/return; and MAINT return.
M1/W must leave free application RAM and the loaded module unchanged. No
Store, flash byte test, SPI SRAM write, format, RTC SET/ACK or power cut is
included. Existing guarded SRAM reads may refuse busy pins without forcing them.

g8 RAM plus services occupies 0200-2FFF; its Restore/ordinary Modify floor is 3000.
WB2 g2 occupies 4800-63FF with state 6400-66FF. CLOCK reuses the qualified bounded
read-only RTC adapter. Its advanced administration remains planned. The FLASH
alias opens the workbench; the proposed full 4KB editor/erase/copy workflow is
not claimed implemented. Full b35 parity remains open.

The RAM gate finishes by requiring all flash bytes to match the baseline,
restoring/verifying owner RAM/ZP, returning to installed g6 and releasing COM4.
Failed RAM admission/functionality prevents installation of those artifacts.

## Conditional flash scope after the RAM gate passes

Recheck the current images/settings and use `native_journal_room.py` against
the fresh B3 capture before the first write. Required zero-C/D-erase capacity:
**six native operations**. PageF is reserved rotation intent, never normal room.

| Target | Authorized component replacement | Maximum erases |
| --- | --- | ---: |
| B2:8 and B2:9 | Two-sector flash workbench bundle, including CLOCK page and RAM loader | 1 each |
| B3:E | Optional read-only service dispatcher and explicit module loader | 1 |
| B3:A and B3:B | Identical g8 monitor front ends | 1 each |
| C/D | Five append-only erase reservations plus one existing-B default generation binding | **0** |
| F | Frozen BASE1 / PR05 | **0** |

Maximum: **five sector erases and six journal appends**, no write retry or
additional erase assumed. Original contents of every replaced sector and all
raw journal rows are archived before replacement. B0/B1, other B2/B3 sectors,
original CLOCK/source/ASM/debug assets and board metadata stay byte-for-byte
unchanged. The legacy utility/extension bytes being replaced remain available
in the complete host backup; their incompatible entry points are not executed.

Default stays B; enable mask, entries, delay, uncertainty flags and all unrelated
settings stay unchanged. Its existing generation binding moves from 6 to 8 so
the updated B can actually boot. Existing wear counts are carried forward with
one additional tracked erase attempt for each replaced sector. No C/D rotation,
old-row replacement, counter reset or F write is permitted.

Order: B2 bundle, E dispatcher, A, then B. Independently read/verify the exact
postimage and accounting after each operation. Test both slots and the B2
loader from RAM/bank-safe code. Bind the existing B default once, then verify
physical default startup with an explicitly requested RESET. No unsolicited
reset, DTR/RTS pulse or power interruption is part of the driver.

Finally compare every flash bank with its exact expected postimage; require all
original raw C/D rows to remain. Restore/read back original owner RAM/ZP after
startup and release COM4. Restoring owner RAM deliberately evicts WB2; MAINT or
CLOCK can explicitly reload it from flash, without a host BIN. M1/W need no
workbench load and borrow only scratch beyond owner RAM. Record incomplete or
refused paths honestly; these updates do not close the full b35 workbench gate.

## Recorded coverage limits

The reviewed write budget and preservation checks passed. Positive BATCH ESC
cancellation and provider-only CRC fault injection were not captured in this
increment and remain qualification work. Bad module CRC followed by a checked
flash reload passed in both ROM slots. See the acceptance receipt for the exact
checks; no full b35 or exhaustive fault-coverage claim is made. The later
[WORK/cancellation repair](MON_AB_G8_WORK_REPAIR_SCOPE.md) closed these two
focused coverage gaps; its additional writes and final counts are recorded in
the [acceptance](MON_AB_G8_2512_ACCEPTANCE.md).
