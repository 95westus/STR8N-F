# 2512 existing-journal F upgrade and BASE1 acceptance plan

Status: prepared for review, not authorized for execution. No board or port
was accessed to prepare this plan. No flashing, firmware assembly, release-kit
update or 2205 access is included. Work order: journal-preserving upgrade,
BASE1 acceptance, then a separate WDC migrator trial.

## Board, artifacts and scope

| Item | Required value |
| --- | --- |
| Board / CPU | 2512 / W65C02SXB, 65C02 |
| Last port / exact USB serial | COM4 / A10MQFLCA; verify again before opening |
| Last installed F | Project b15; SHA-256 1a1db354d49d8a9a555be1100b74f3e4b0ed14d3156f3a333086853a845717b8 |
| Frozen target | STR8N-F 0.3.0 g00000001 / BASE1 / PR05, exactly 4096 bytes |
| Target SHA-256 | 8f4d35ac66730daa773515980983fcf442be3b1bdf1e523d3752ec3615657cc1 |
| NFU1 RAM template | 8192 bytes; SHA-256 137a73923af1661a6af03d8dc9351e1b1f650f4c6e3381669ae3cf020f8c6b62 |
| RAM escrow | Original 0200-66FF, 25856 bytes; original ZP 00-DF, 224 bytes |
| Final safe prompt | REC>; intercept S at every chooser |

Use the complete source checkout at `release/str8nf-v0.2.0`, not the published
or existing candidate kit. Keep frozen F, F_FREEZE.json, all matching BASE1
tool hashes and the upgrade template pinned. No rebuild is planned. Never
open COM3/2205 or any other board port.

The current b15 MON B and B0:8 FLASH image remain owner images. Preserve them,
but do not boot them after the F upgrade to prove BASE1 compatibility. They
may depend on old private addresses. In particular, preserving default B does
not make a timeout into MON B safe. The host must select S before timeout.
Do not change the saved default to S merely to simplify the test.

## Archived reference prepared now

The last preserving console trial finished 2026-10-28 23:33:40 UTC. Its actual
independent flash reads and pre-helper RAM reads were used to prepare a private
reference capture and rendered expected postimage:

```text
C:\SRC\STR8-N\output\qualification\2512-upgrade-base1-plan-20261028-r1\
  REVIEW_ONLY.json
  archived-reference-capture\
  archived-reference-plan\
```

These are historical inputs, not a fresh device admission. The capture is
marked `reference_only: true`; both the upgrade CLI and execution API refuse
it before device access. Do not remove that flag, rename old files into a fresh
capture, or copy a single read twice to satisfy repeated-read admission.

Expected delta for those archived bytes:

| Field / region | Before | Expected after |
| --- | --- | --- |
| Existing committed records | 19, newest at D200 | All 19 retained byte-for-byte; one additional record |
| Sequence | 951 / 000003B7 | 952 / 000003B8 |
| Reservation page / commit | D300 erased, D3FF=FF | One cloned SNBT record, D3FF=00 last |
| Default / enabled / entries | B / 0F / 8000 in all four banks | Identical |
| F reservation count | 21 / 000015 | 22 / 000016 |
| C/D erase counters | C=47, D=27 | Identical; zero C/D erases |
| Other wear counters / unknown mask | Original / FFFFFFFF | Identical |
| B0-B2, B3:8/9/A/B/E | Owner images | Byte-for-byte identical |
| B0:8 / B0:9 | FLASH installed / intentionally erased | Identical, including the erased sector |
| F | Old b15 | Exact frozen BASE1 bytes |

Only D300-D3FF and F000-FFFF may differ for this reference transaction. The
private REVIEW_ONLY.json contains all source/expected bank hashes and the
reservation-record hash. Expected reference B3 SHA-256 is
`c26fc14619902baa502cfbffe8ce104e8a3cc8ae1e135b1ec30ea21e2ad74424`.
Do not force these addresses/counts if a fresh capture differs.

## A. Fresh admission before any future write

This phase also needs authorization to access 2512; it has not run now.

1. Confirm 2512 remains powered, owner applications/RTC collectors are stopped,
   COM4 is free and device markers have no pending restore/reset/worker. Resolve
   only the exact USB serial A10MQFLCA. Leave all other terminals/ports alone.
2. At the existing known b15 monitor, collect original owner RAM and ZP twice
   before the first helper upload. Collect all four flash banks twice through
   read-only monitor commands; save separate files and immutable hashes. The
   existing inventory helper reads all banks once and repeats B0 only, so one
   such run alone is insufficient. Use two independent read-only passes, checking
   RAM/ZP before and after and matching every bank. No RAM shim/helper first.
3. Require the known b15 F hash, clean SNBT history, available erased append
   page, non-exhausted sequence/F counter and unchanged original RAM reads.
   Preserve every original record, including older ones; never initialize C/D.
4. Normalize the independent originals into the private capture schema described
   in [the upgrade procedure](JOURNAL_F_UPGRADE.md). Include original-escrow
   provenance and exact USB serial. A fresh capture must not be marked as an
   archived reference. Keep RAM/vendor/owner image files out of Git/public kits.
5. Prepare and inspect a new private plan, without opening a device:

```text
python migration-host/nf_upgrade.py prepare --capture FRESH-2512-CAPTURE --cpu 65c02 --out FRESH-2512-UPGRADE-PLAN
python migration-host/nf_upgrade.py inspect --plan FRESH-2512-UPGRADE-PLAN
```

6. Review the actual append address, record delta, preserved settings, counters,
   target F and full-bank expected hashes. If source bytes differ from the
   archived reference, stop for review of the new delta. Do not substitute old
   postimages. Keep the board idle after capture; engine source guards must
   still match all four banks before mutation.

Gate A: original escrow durable and repeated; exact fresh transaction reviewed.
No live execute command is authorized by this document or by preparing a plan.
The current no-flashing instruction remains in force.

## B. Single future authorized upgrade transaction

Use a fresh private run directory and only the freshly reviewed NFU1 plan.
Execution requires separate authorization plus the tool's explicit `--execute`
and `--allow-unqualified` flags. Do not run factory provisioning or CONFIG I.

| Checkpoint | Required observation / acceptance | Stop condition |
| --- | --- | --- |
| B1 Old-F entry | Physical RESET, observe chooser, select S, REC>, temporary C1; saved settings unchanged | Wrong board/prompt or missed chooser; do not guess a command |
| B2 RAM preflight | Full NFU1 self/plan check, four current bank guards and BF/B5 chip check before Y | Missing/failed guard; no authorization or payload |
| B3 Authorization | Original capture and plan durable; phase receipt written before Y | Any durability/plan mismatch |
| B4 Journal append | Selected page is erased; record programmed with FF commit, compared; D3FF/reference equivalent committed to 00; complete reserved-B3 hash verified | Missing reservation proof: send no F bytes |
| B5 F transfer | Only after reservation proof and B3:F ready marker: exactly 4096 frozen bytes, paced; no terminator | Short write/timeout/refusal; no automatic retry |
| B6 Device verification | F staged/erase/program/full comparison and all four final bank guards pass | Any mismatch; inspect, do not reset/replay blindly |
| B7 New-F reset | Physical RESET; exact BASE1 identity/profile; select S promptly | No exact identity/REC>; keep logs and use inspected recovery |
| B8 Independent verification | Matching BASE1 READBACK; full B0-B3 SHA-256 equals fresh planned postimages | Any mismatch: do not declare success or blindly restore/replay |
| B9 Owner restoration | Restore original RAM 0200-66FF and ZP 00-DF, independently read/compare both, Q to REC> | CRC/byte/return mismatch: restoration pending |

Gate B: upgrade and original-RAM restoration proven. All retained journal bytes
must match the source; only the approved new record and frozen F may differ.
The F count is a conservative reserved attempt and is never decremented after
failure or an unused reservation. Do not restore an old whole B3 image or old
C/D sectors as a rollback: that would destroy the new wear history.

## C. Preserving BASE1 acceptance after Gate B

Retain the same immutable original escrow. Every new RAM-tool load borrows
owner RAM again; mark restoration pending and never replace original escrow
with a dump of working tool RAM. Use only matching BASE1 payloads/manifests.

| Test | Procedure / acceptance |
| --- | --- |
| Startup identity | Capture physical-reset output: STR8N-F 0.3.0 g00000001, then BASE1 / PR05. Observe recovery separately from OS identity; intercept S on every reset |
| SEND BIN cancellation | At REC>, L then F12/Ctrl-C before payload. Require a single 03, zero BIN payload and return to REC>. Compare flash with Gate B and verify final original-RAM restoration. A later helper upload cannot prove the overwritten prefix stayed unchanged during cancellation |
| Normal RAM BIN | Load matching DEMO with F3 at SEND BIN and F4 from REC>; require 1234+0001=1235, key K reported as 4B, then intercept S. Host-sent count alone is insufficient. Use the non-overwriting resident-service method below for the surviving immutable bytes; do not claim a full-code readback from a freshly uploaded helper |
| MAP | F5 / matching MAP, M1/M2/M3. Compare roles/erased sectors and wear to actual bytes. WDC recognition is only a resident fingerprint; do not assume any preserved image boots |
| CONFIG inspection | F6; B, C and W without arguments read back the original default B, mask 0F, entries and planned counts. Do not issue I or setting-changing forms. Q then select S |
| OPAQUE menu | F7; reach matching prompt and Q back to recovery. Do not issue I or send an install frame. This checks loading/return, not flash programming |
| Console operator checks | Real physical F1-F12/buttons, native file/help dialogs, log on/off, explicit connect/disconnect and local clear. Verify exact byte routing; keep private logs out of public evidence |
| Disconnect deferral | During a known matching DEMO BIN, request disconnect; complete payload/drain/idle before close. Reconnect and verify the expected running prompt before sending another command |
| Second physical reset | Saved boot record/default remains unchanged; intercept S rather than allowing an unqualified old MON/image to autostart |
| Final preservation | Reload matching READBACK; all four banks still equal the Gate B expected hashes. Restore/read back original full RAM/ZP again; finish REC>, release COM4 |

Gate C is preserving boot/recovery/RAM-tool acceptance for this 65C02 board.
Record hardware/key/adapter observations accurately. Prior b15/Tk-generated-key
results are reference evidence, not passes for these BASE1/native-key tests.
Keep borrowed stack 0100-01FF and system ZP E0-FF distinct from owner ranges;
do not claim that all system scratch RAM is restored.

Independent inspection must not silently destroy the bytes being inspected.
The READBACK service loaded for Gate B resides at 6800, outside owner RAM.
If its residency and the intervening tools' memory footprints have been
reviewed, a three-byte raw RAM trampoline `4C 00 68` at 0200 can reenter that
service without uploading the 3078-byte loader over the DEMO. This deliberately
overwrites 0200-0202: record that overlay, compare the surviving immutable DEMO
bytes from 0203 onward (exclude its documented mutable variables), and report
the first three original code bytes as unavailable for independent readback.
Restore those bytes from original escrow with all other owner RAM at the end.
If service residency is uncertain, do not jump to it; mark that inspection
NOT RUN and use the normal matching READBACK load for final preservation only.
A complete immutable-image readback requires a separately reviewed harness
that does not overwrite the image prefix. Never use the old b15 MON to obtain
that readback under a different F/private contract.

## D. Separate tests still requiring their own reviewed scope

The following are not silently included in the single-F-write plan:

- CONFIG save/default persistence and actual opaque install/boot/return need
  controlled additional flash writes and journal records. Prepare a separate
  expected wear/record delta and an owner-approved scratch target first. An
  erased sector is not permission to use it; B0:9 must remain erased here.
  Restore original settings/images through admitted operations, retaining all
  new erase reservations/history rather than restoring old journal sectors.
- NFU1 preflight Ctrl-C can be trialed before Y, but the RAM engine then halts.
  A matched b15 reset/readback/owner-restore procedure must be ready and reviewed
  before that separate trial. The upgrade CLI otherwise proceeds to Y after
  preflight; do not call it a preflight-only test.
- Power-cut/torn-append/partial-F tests require a separately admitted repair
  procedure and independent programmer recovery. Do not improvise them on the
  preserved board or assume retry is safe.
- 65C816 mode coverage, ACIA/electrical/EDU/SPI/RTC tests, old MON/FLASH image
  compatibility, factory C/D provisioning and the full WDC migrator remain
  separate. No 2205 access or firmware/image changes are authorized.

Passing B/C does not close these release gates. In particular, unchanged boot
settings prove preservation, not a new successful CONFIG save; reaching OPAQUE
and Q does not prove sector programming or booting an installed opaque image.

## Required final record and failure handling

Retain privately: fresh dual captures and provenance, source/F/NFU1/tool hashes,
reviewed plan, durable phases and exact serial trace, reservation proof, actual
post-bank dumps, original and restored RAM/ZP readbacks, physical-reset banners,
operator-key observations, any failures and final REC>/port-release evidence.
Each case is PASS/FAIL/NOT RUN with its actual scope. Sanitized results may be
committed later; current candidate/source ZIPs remain untouched.

On failure: stop writes and automatic retries/resets; retain power and escrow,
record whether journal commit/F transfer may have begun, and keep owner-RAM
restoration pending until independently verified. Inspect actual flash before
proposing repair. If F may be torn, do not assume ROM recovery is callable.
No generic rollback or power-cycle command is part of this plan.
