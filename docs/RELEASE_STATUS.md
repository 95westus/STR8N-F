# STR8N-F BASE1 / PR05 release status

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

| Gate | What remains | Release impact |
| --- | --- | --- |
| Frozen BASE1 hardware acceptance | Physical reset/startup identity, supported CPU modes and adapters, recovery cancellation/normal load, matched MAP/CONFIG/OPAQUE/READBACK, boot-default persistence, opaque boot/return, journal/wear behavior and independent preservation checks | Blocks qualifying the BASE1 firmware/toolkit, including the programmer-only 4K distribution |
| WDC RAM migration acceptance | Real end-to-end verbose migration, physical reset boundaries, vendor startup/peripheral effects, final independent flash/RAM/ZP verification, and a documented/admitted interrupted-migration repair procedure | Blocks the promised public WDC-to-STR8N RAM migrator |
| Generic provisioning after programmer-installed F | Source implementation now complete in nf_provision_live.py; original-escrow procedure and focused host checks added. Hardware acceptance and future kit integration remain pending | F alone does not provision occupied vendor C/D; existing kit intentionally unchanged |
| Existing-SNBT F upgrade | Separate NFU1 source implementation now appends/commits an F attempt reservation before F erase; qualify it on hardware | Known b15 source only; full/damaged journals refused. Factory path still refuses upgrades. Future kit integration pending |
| Console operator acceptance | Native physical F-key/button/file/help-dialog checks, disconnect deferral and supported host/adapter timing with matching BASE1 tools | Still pending; the b15 serial trial closes only its stated subset |

The existing-SNBT upgrade is implemented separately in source; see
[its transaction](JOURNAL_F_UPGRADE.md). Live C/D provisioning is also implemented
in source; see [its procedure](LIVE_CD_PROVISIONING.md).
The other gates require authorized hardware work. The current no-flashing
instruction leaves those hardware gates open. Board 2205 remains outside all
release work.

An earlier programmer-only release could explicitly omit WDC migration and
existing-SNBT upgrade support, but it would still need frozen-BASE1 hardware
acceptance. The requested combined 4K image plus verbose WDC RAM migrator must
close both acceptance gates. Any unsupported provisioning/upgrade route must
be plainly excluded, not presented as completed.

No further F optimization is required by this checklist. A real F defect would
require a reviewed new generation; the console result does not justify changing
the frozen bytes. The legacy b15 test is not a substitute for BASE1 acceptance.
