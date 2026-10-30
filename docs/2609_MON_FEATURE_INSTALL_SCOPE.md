# 2609 MON/tools: preserving installation scope

**REVIEW ONLY: no flash transaction is authorized or executed by this file.**

Status: the owner approved this exact scope and it completed. See
[acceptance](2609_MON_FEATURE_ACCEPTANCE.md), including the separately approved
dispatcher repair. Original review limits below are retained as history.
Prepared October 30, 2026 after the completed RAM readiness trial. The first
installation replaces MON B and its tools, keeping every old raw journal row.
2604 remains intact as the integrated rc1 reference.

| Sector replaced | Component | Wear append | Counter before -> after |
| --- | --- | --- | --- |
| B2:8 | Tool bundle / WB2 g5 | CA00 / seq1025 | 602 -> 603 |
| B2:9 | WB2 / PROGRAM bundle | CB00 / seq1026 | 261 -> 262 |
| B2:A | PROGRAM/SP1 bundle | CC00 / seq1027 | 13 -> 14 |
| B3:E | Services g3 | CD00 / seq1028 | 43 -> 44 |
| B3:B | MON B g8 | CE00 / seq1029 | 54 -> 55 |

**Five 4KB replacements, five append-only records, zero C/D erases, zero F
writes, no power cuts.** The five blank ordinary pages exactly fit this scope.
CF00 is the reserved rotation-intent page, not a sixth ordinary slot.

Original sectors and complete-bank postimages are prepared privately at
`C:/SRC/STR8-N/output/qualification/2609-mon-feature-install-scope-20261030/`.
Its `plan.json` binds originals, targets, counts, sequences and expected hashes.
Execution must freshly recapture and admit those originals before writes.

The current 11 raw C/D records remain at their original addresses. Final state:
16 records, newest CE00/seq1029; C=78, D=47 and F=31 unchanged. Default S,
mask00, entries8000 and all other boot-policy bytes remain unchanged. Select
MON B manually at the chooser. Saving a new default is outside this scope and
would require a separately reviewed journal rotation afterward.

B0/WDC, B1, B2:B-F, B3:8/9/A and F stay byte-identical. A remains retained b15
firmware whose execution under BASE1 is unqualified; do not choose it. New A/B
candidate implementations remain identical; only B is installed in this scope.

Installing both slots instead needs six component erases/reservations and one
native D rotation: **seven erases total**. D000/seq1014 would need a verified
host archive before replacement. All C records and latest settings/counts would
survive, but this changes the raw-history preservation contract. It is an
alternative, not part of the recommended five-erase transaction.

After approval: verify all bank postimages, physically reset/select B, check
board-loaded tools, PROGRAM Table, AUTO/NO, BATCH, native TIME and Q to recovery.
Restore/read back owner RAM0200-66FF and ZP00-DF; verify unchanged old history,
settings and F; release COM8. No positive Store, owner-app launch, SRAM-data,
RTC/trim/PF/EEPROM write or power cut is included. Positive write/run receipts
remain 2512-specific.

Update RTC profile admission against the completed installation receipt before
scheduled access resumes on 2609. Keep clock, trim, PF state and historical
measurements, recording the firmware/profile boundary. The hourly schedule and
other boards remain unchanged; a serial lease excludes concurrent access.

Published N-F v0.3.0 and downloads remain unchanged. Optional feature candidate
installation/boot acceptance is pending.
