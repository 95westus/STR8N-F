# 2512 current PROGRAM: functional pass and exact preservation closeout

October 30, 2026. **65C02 / FT245**, installed MON B g8, services g4, WB2 g5
and PROGRAM/SP1 g1. [Public composite receipt](../monitors/validation/2512-program-positive.json),
[original temporary scope](2512_PROGRAM_POSITIVE_SCOPE.md). Functional checks
passed. The original narrow directory scope was not met because of a host
planning error; the preserving continuation restored every original byte.
The original failed report remains unchanged.

## Functional results

Fresh complete SRAM matched its preserved snapshot before Store. AUTO
previewed 0800 and NO canceled it without writing. Four explicit Stores at
C000/C100/C200/C300 passed: a 16-character name, a short name, a newer same-name
version and a separate record. Occupied-payload refusal and Table passed.
Checked load-only selected the newer UP version and restored its exact 23
bytes. Positive run printed UP and returned through public HOLD to MON B.
A deliberate first-byte change in the temporary C200 payload caused CRC
error 45 before destination copying; all 23 sentinel bytes remained intact.
Repair restored successful checked loading. No retained CLK/CLOCK program
was run. Positive AUTO Store and directory-full checks remain outside this
trial; the 2609 receipt retains its separate current-SP1 evidence for them.

## Host planning error and preserving repair

The planner assumed free directory slots 0/1/2/3. PROGRAM's existing scanner
keeps updating FREE_SLOT and therefore selects the last free slot: the four
Stores actually used 7/4/3/2. Restoring only the initially planned blocks left
91 differing bytes in slots 4 and 7, caught by the complete-array comparison.
The functional binary behaved correctly; this was a host scope-planning
error. The exception also deferred owner-RAM restoration while the board
stayed at WORKBENCH>, with RTC sampling blocked and all original bytes
already escrowed. No reset or flash transaction followed the failure.

The preserving continuation restored exact original 64-byte blocks 0140-017F
and 0200-023F, including slot 7's retired commit byte 00. It reused the same
private restorer instruction bytes; only its data allowlist was restricted
to those two addresses and its image CRC resealed. No assembler or firmware
build. Both blocks were independently read back, followed by complete SRAM
comparison. The union of trial/restoration addresses was 1408 bytes, including
128 bytes outside the original 1280-byte plan. This is explicitly recorded
as a scope error, not described as compliance with the original plan.

## Final preservation

All 131072 SRAM bytes now match the original:
`580a60e314e7c91703a319f03516bd803f36a8202f773e4206b6d4aa69d227aa`.
Primary header, CLK/CLOCK payloads, original directory bytes, WORKSPACE and
tail are exact. Four-bank double comparisons also match: frozen F, images,
boot/wear history and saved B/g8 are unchanged. The journal remains 20 rows,
C300/seq1033; C=53/D=33/E=28/F=24. Zero flash/journal/WORKSPACE writes,
clock/trim/PF changes, power cuts, resets or firmware builds.

Fresh pre-helper native owner RAM0200-66FF/ZP00-DF escrow was restored and
independently compared through native Dump. Original MON B/B3> returned,
COM4 released, and the unchanged native TIME RTC/NTP profile can resume.
The source planner/driver now check the allocator's actual slot order before
any future Store. 2609's AP/02 work waited until this preservation closeout.
2205 and 2604 were outside the trial. Published Foundation/preview archives,
tags and F remain unchanged; ASM/DBG remain deferred and nonblocking.

Private original failed captures and the separate repair receipt remain in
the parent project's `output/qualification/2512-PROGRAM-*` directories.
