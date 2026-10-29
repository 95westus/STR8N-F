# g7 / WB2 g1: 2512 RAM-only trial scope

**Prepared scope, not an armed receiver or test result.** Target only
2512/COM4/FT245 USB serial A10MQFLCA, idle with the port available. Leave
2205, 2604, 2609 and all other ports alone. No flash programming/erase, journal
append, boot-policy change, SRAM write/format, RTC access or power cut.
F remains golden; A/B ROM candidates are excluded.

Use the exact RAM artifacts and hashes from the [g7/WB2 manifests](MON_AB_G7_WB2.md).
Installed g6 is the preservation/reentry path; no old flash budget is reused.

1. Acquire the board-specific serial lease and verify USB identity. Before any
   helper/BIN, capture fresh owner RAM 0200-66FF and ZP00-DF using native D in
   bounded blocks. Archive boot policy and both full-bank read passes; require
   equality and exact golden F/current g6. Do not substitute an old RAM backup.
2. Load g7 RAM through REC>. Check its new name, prompt, help, explicit TIME
   availability without invoking it, missing WB2 refusal and RAM L/G refusal.
   Q returns to REC>.
3. Load WB2 RAM. Check identity, B0..B3, help and `BATCH B1;T;B3`. Compare Table
   with the fresh flash inventory; no record fixtures or erases are permitted.
4. Check empty, leading/trailing/repeated separators, >34-byte text, malformed
   arguments and unsupported/nested commands. A command outside the allowlist
   must be rejected before any earlier bank/EDU change. Bad arguments stop when
   their command is reached. No later command may execute after a failure.
5. Use `EDU OFF`, then `BATCH SRAM;B0`: result02 must stop before B0. Use
   `BATCH EDU ON;EDU OFF;B3` for successful returning commands. Check Ctrl-C/ESC
   during Table and between commands; result03 must stop the queue. Store, R,
   PREP, G/L/Q and application handoff inside BATCH must all be refused.
6. EDU ON allows only the already documented guarded Rev D read profile.
   Retain guard-register readings; busy is a valid refusal, not permission to
   force/reconfigure the VIA. No SRAM PREP is included in this trial. If reads
   succeed, check SRAM/WORK and compare mounted layout/capacity with the archived
   read-only facts. Do not claim positive paths when the guard refuses.
7. Return via installed g6 to REC>, then load g7 RAM while WB2 remains at 4000.
   Check bridged BATCH/T/HELP, status 02/03/01 results at 655F and resulting data
   bank. The g7 RAM image ends at 1153; its Restore floor is 1200. Do not load legacy
   CLOCK whose end exceeds the new 4000 boundary and do not run legacy apps.
8. Ordinary M must refuse module/state targets and the 3FFF/4000 boundary before
   any write. Reversible RAM admission/corruption tests may use module padding
   byte 63FD only, with its original byte retained and restored; no forced I/O,
   flash, stack or owner ZP edits. Show bad CRC refusal then restored admission.
9. Independently recapture all flash banks and require byte-for-byte equality,
   including every C/D row, F, installed g6 and boot/wear settings. Restore and
   read back all original owner RAM/ZP, evicting WB2 deliberately. Finish in
   installed g6 or REC>, release COM4 and the serial lease, and record exact
   evidence/limitations. Any mismatch stops the trial before optional steps.

These candidates have no positive hardware result yet. Successful RAM testing
would qualify only this subset/CPU/console; it would not close AUTO T/S/R,
SSRAM PROGRAM writes, APPS, complete BATCH or full 2.0b35 parity. A later A/B
installation requires a fresh journal-capacity preflight and bounded review.
