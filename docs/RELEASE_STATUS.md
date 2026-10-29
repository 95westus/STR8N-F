# STR8N-F BASE1 / PR05 release status

Current scope decision: [F is the golden runtime recovery anchor](GOLDEN_F_RECOVERY_SCOPE.md).
Normal recovery remains at REC> and leaves F intact. Deliberate interrupted-F
testing is NOT RUN and outside the installed-BASE1 runtime contract; that
runtime gate is closed by the owner's stated assumption. Interrupted initial
F installation/explicit upgrade remains an unqualified maintenance case.
This decision made no board, firmware or release-kit changes.

Prepared next: [2512 interrupted C/D B3 scope](2512_CD_RECOVERY_SCOPE_REVIEW.md).
The source-bound RAM lab and exact packets are ready for review: one C erase,
one D erase and six chip-idle USB power cycles, with F untouched and original
records/images/policy/RAM restored. Hardware is NOT RUN; no board command was
sent during preparation. The general damaged-journal classifier remains strict.

Later hardware checkpoint: [2512 B0 write/boot and real power loss](2512_B0_POWERCUT_ACCEPTANCE.md)
passed. CONFIG saved entry/default, an opaque image booted directly and after
physical reset, and recovery survived power loss with an incomplete B0 image
at a chip-idle checkpoint. Originals were restored, all older records retained,
and F/kit assets unchanged. Restoring the incompatible original MON default
required a guarded test-only escrow helper; normal CONFIG correctly refused it.
The separately approved [2512 WDC migration](2512_WDC_MIGRATION_ACCEPTANCE.md)
also passed: real vendor resets/archive, public NFM1 F/D/C provisioning,
physical BASE1 recovery, source-bound wear import and final original policy,
images and RAM restoration. Six erases were recorded; original raw history is
archived on the host. Flash-pulse and torn-journal coverage remain open;
interrupted-F scope is distinguished above.

Checkpoint: October 28, 2026. Unpublished candidate, F 0.3.0 g00000001,
Serial Console 0.1.0. The 4096-byte F is frozen. Packaging this checkpoint
copies existing firmware; no assembly, simulation or board access is required.

## Completed

- Frozen name/version/generation and identity descriptor, with OS status kept
  in the running image. Exact F and source bindings are recorded in F_FREEZE.json.
- Matching BASE1 CONFIG, OPAQUE, DEMO, MAP and READBACK files. RAM MAP recognizes
  known WDC resident fingerprints. Only B3:C/D/F are reserved in BASE1.
- Verbose WDC migration planning/executor and independent archiver/engine
  artifacts, with admission checks and explicit unqualified live gate.
- Python serial console, operator guide, dependency pin and 19 host checks.
- Real serial trial on 2512 with its existing b15 F: F1-F12 bindings, Ctrl-C at
  SEND BIN, normal F3/F4 BIN execution and independent code readback, b15 preset
  loading, logging, connection and local clear. All flash bytes, boot/wear journal
  and images matched; RAM 0200-66FF and ZP 00-DF matched after restoration.
  The board returned to MON B and COM4 was released. No flashing; 2205 untouched.

The kit includes the sanitized [2512 receipt](../validation/console-2512-hardware.json).
It binds the exact tested console source hashes. Keys were generated through
Tk; native dialogs used deterministic substitutes. The test used matched b15
tools, including MAINT under the MAP preset filename. It did not install or run
BASE1 firmware. Raw serial logs, RAM and vendor/owner images remain private.

## Open gates

Update: the authorized [2512 BASE1 acceptance](2512_BASE1_ACCEPTANCE.md) has now
passed the existing-journal upgrade, repeated reset, preserving RAM-tool and
native-console checks. F stayed frozen. Source receipts have been added; the
existing kit and its release manifests remain their prior package snapshot.

| Gate | What remains | Release impact |
| --- | --- | --- |
| Interrupted C/D recovery | Source-bound lab, byte-exact phase plan and B3 review prepared. Six chip-idle interruption cases await explicit scope approval and hardware execution | Open; no fault-test pass claimed by preparation |
| Frozen BASE1 hardware acceptance | 2512 reset/identity/recovery/BIN/MAP/CONFIG save/opaque programming/boot/READBACK and preservation passed, including chip-idle incomplete-image power loss. Other supported modes/adapters and flash-pulse/torn-journal cases remain | Golden F assumed intact; tested 65C02/FT245 cases closed; broader runtime qualification remains |
| WDC RAM migration acceptance | 2512 real WDC archive/reset/public NFM1 F/D/C migration and independent flash/RAM/ZP preservation passed. Other occupied layouts/platforms, peripheral effects and exercised interrupted-migration repair remain | 65C02/FT245 happy path closed; general acceptance and future kit integration remain |
| Generic provisioning after programmer-installed F | Source implementation now complete in nf_provision_live.py; original-escrow procedure and focused host checks added. Hardware acceptance and future kit integration remain pending | F alone does not provision occupied vendor C/D; existing kit intentionally unchanged |
| Existing-SNBT F upgrade | Known-b15 to BASE1 on 2512 passed: D300 committed before F, old records/settings/images retained, original RAM restored. Failure/interruption and 816 coverage remain unqualified | Explicit maintenance outside normal golden-F runtime; full/damaged journals still refused. Future kit integration pending |
| Console operator acceptance | Native F1-F12/help/file/log dialogs, exact normal loading/cancellation and real-port disconnect deferral passed on 2512/BASE1 | Individual button aliases and other supported host/adapter coverage remain |

The existing-SNBT upgrade is implemented separately in source; see
[its transaction](JOURNAL_F_UPGRADE.md). Live C/D provisioning is also implemented
in source; see [its procedure](LIVE_CD_PROVISIONING.md).
The user separately authorized the completed 2512 reservation/F upgrade,
B0 CONFIG/opaque tests, B0 power loss, and the reviewed six-erase current-chip
WDC trial. Those approvals do not authorize other boards or additional F/C/D
fault tests. Board 2205 remains excluded. Existing release kit assets stay at
their earlier package snapshot until the user authorizes a kit update.

An earlier programmer-only release could explicitly omit WDC migration and
existing-SNBT upgrade support, but it would still need frozen-BASE1 hardware
acceptance. The requested combined 4K image plus verbose WDC RAM migrator must
close both acceptance gates. Any unsupported provisioning/upgrade route must
be plainly excluded, not presented as completed.

No further F optimization is required by this checklist. A real F defect would
require a reviewed new generation; the console result does not justify changing
the frozen bytes. The legacy b15 test is not a substitute for BASE1 acceptance.
