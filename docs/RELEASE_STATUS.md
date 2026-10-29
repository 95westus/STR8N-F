# STR8N-F BASE1 / PR05 closeout and release status

Closeout: **October 28, 2026**. The reviewed **2512 / 65C02 / FT245 / Windows**
source/hardware cases are closed. **0.3.0-rc1** is an unpublished candidate
for the next migration test using only its extracted ZIP. That packaged
migration test is **NOT RUN**; public release is **NOT PUBLISHED**.

> Give me 4KB, I can give you 4 boards.

With ~32KB RAM shared by four selectable bank environments.
F stays **0.3.0 g00000001 / BASE1 / PR05**, exactly 4096 bytes. Toolkit and
console versions do not alter F generation.

## Closed 2512 cases

| Case | Result and evidence |
| --- | --- |
| Known-b15 existing-journal F upgrade | [Passed](2512_BASE1_ACCEPTANCE.md): reservation before F, prior history/settings/images retained |
| BASE1 identity, reset, recovery and RAM tools | [Passed](2512_BASE1_ACCEPTANCE.md): physical resets, MAP, READBACK, Ctrl-C and normal BIN loading |
| Python terminal operator acceptance | [Passed](2512_BASE1_ACCEPTANCE.md): native F1-F12, dialogs and real-port disconnect deferral; original RAM restored |
| CONFIG and opaque install/boot | [Passed](2512_B0_POWERCUT_ACCEPTANCE.md): persistence, RAM/flash writes and boot, original images/policy/RAM restored |
| WDC RAM migration | [Passed](2512_WDC_MIGRATION_ACCEPTANCE.md): real vendor debugger/archive, public F/D/C conversion, recovery and preservation |
| Programmer-installed-F C/D entry | [Passed](2512_PROGRAMMER_F_CD_ACCEPTANCE.md): public no-op and declared non-SNBT first journal, four C/D erases, F golden |
| Interrupted C/D journal cases | [Passed](2512_CD_RECOVERY_ACCEPTANCE.md): six named chip-idle cuts, original rows/settings/images/RAM restored, current counts retained |
| Interrupted-F runtime gate | [Closed by scope](GOLDEN_F_RECOVERY_SCOPE.md): F assumed golden; no interrupted-F pass claimed |

All passes are limited to their receipts. The WDC and programmer-F conversions
explicitly archived replaced raw history on the host while importing latest
tracked counts. The last board checkpoint is REC>, COM4 released, latest
sequence 1000, three records, C=52/D=32/F=24; original owner images, settings
and RAM/ZP verified. 2205 was not accessed.

## What remains

| Item | Status |
| --- | --- |
| Fresh operator/source ZIP, terminal and migration dependencies | Candidate packaging; integrity/extraction results belong in PACKAGE_RECEIPT.json and its extraction receipt |
| Migration and terminal acceptance from that exact extracted ZIP | **NOT RUN**; next reviewed test, bind archive SHA-256 in the result |
| Public release/tag/upload | **NOT PUBLISHED** |
| Other CPUs/adapters/hosts and occupied layouts | Unqualified; no four-board hardware pass inferred |
| Electrical mid-pulse failures, arbitrary corrupted history and interrupted provisioning | Outside this candidate's accepted happy paths |
| Interrupted F installation/explicit F upgrade | Unqualified maintenance boundary; normal runtime keeps F golden |

Use the [release workflow](RELEASE_WORKFLOW.md) for package contents and the
pending ZIP test. The terminal is included, not a future download requirement
apart from Python/Tk and pinned pyserial. Migration remains a separate CLI;
F-keys load RAM tools and do not start migration.

No further firmware optimization or routine rebuild/simulation is needed
for packaging. F defects require a reviewed new generation. This docs/package
step performs no board actions, power cuts or publication. Future test scope
must identify its board and writes; keep 2205 excluded and use no deliberate
power-off-during-programming tests.
