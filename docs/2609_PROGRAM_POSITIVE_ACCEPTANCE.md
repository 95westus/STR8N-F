# 2609 PROGRAM Store/Restore/run: passed

October 30, 2026. **65C816 emulation / FT245, installed MON B g8, services g4,
WB2 g5 and PROGRAM/SP1 g1.** [Public receipt](../monitors/validation/2609-program-positive.json),
[reviewed scope](2609_PROGRAM_POSITIVE_SCOPE.md).

## Results

The fresh complete SRAM read matched the two-pass approved capture before
any Store. AUTO preview/NO left all test blocks unchanged. Four temporary
records passed: a 16-character name, a short name, a newer same-name version
and explicit C300 placement. AUTO used C000, C100 and C200. A fifth Store was
refused with the directory full, without committing another record.

PROGRAM and combined Table listed the test records. Load-only selected the
latest same-name version and restored its exact 23 bytes. Running that version
printed `UP` and returned through the public HOLD entry to MON B, CPU $16.
A deliberate first-byte change in the test C200 payload caused CRC error $45
before copying any destination RAM; its sentinel bytes remained unchanged.
Repairing that test block restored a successful checked load.

This qualifies the positive SS1 PROGRAM path on 2609. It adds no flash AP/02
owner-app launch, positive SS2-write, native-mode or new 65C02 services-g4 pass.
Those boundaries remain explicit in the [Foundation release path](FOUNDATION_RELEASE_PATH.md).

## Preservation and closeout

All 20 original 64-byte directory/payload blocks were restored and device-
verified. The complete 131072-byte SRAM then matched the original snapshot:
`56cd2490028e7c6b4ee07fb26c87ea75d9d665f10c6406263c0c0f4000116a9e`.
All four retained CLK versions, the primary header, WORKSPACE and tail are
byte-identical. No test record is left installed and no duplicate was retired.

All four flash banks match their admitted original hashes, including F and
every C/D byte. Default S, all boot settings and 17 journal records remain
unchanged, latest D000/seq1031. Tracked counts remain C=78/D=48/E=45/F=31
(decimal). There were zero flash writes/erases, journal appends, WORKSPACE or
mode-register writes, RTC SET/trim/PF acknowledgements, resets or power cuts.
2205, 2512 and 2604 were outside this trial.

Owner RAM0200-66FF and ZP00-DF were restored and independently read back.
Final REC>, COM8 released; the existing qualified RTC/NTP profile and schedule
remain applicable because firmware, owner RAM and clock settings are unchanged.

## Host failures retained as evidence

Two host-only errors required preserving continuation. The first helper sent
CR after the bench's immediate Q; the extra blank MON prompt was mistaken for
the next command's reply. That attempt stopped before Store, and independent
recovery verified unchanged flash/SRAM and restored owner RAM/ZP without reset.
The corrected Q sends one byte, without a line terminator.

The functional retry passed every positive Store/Restore/run/CRC check. During
restoration its parser incorrectly recognized `EF9` inside successful reply
`O2EF9` as a separate error. The exact positive CRC acknowledgement now decides
success. The preserving continuation restored all 20 allowed blocks, compared
the full array, verified flash and restored owner RAM/ZP. Original failed
reports remain intact; the composite receipt links both functional and
restoration evidence. Neither correction expanded the write scope or changed
board firmware. The same 767-byte restorer was reused; no extra build occurred.

Private captures and host-source checkpoints remain in the parent project's
`output/qualification/2609-PROGRAM-positive-*` directories. Public receipts
include hashes and results, with no captured owner bytes.

## Release boundary

**PROGRAM gate closed.** Resident [ASM and DBG](MON_ASM_DBG_RELEASE_GATE.md)
are now deferred follow-on work and do not block the current MON/tools
release. Their future inclusion still requires a BASE1 port and live
qualification. Existing Foundation v0.3.0 and preview 1 archives stay unchanged.
