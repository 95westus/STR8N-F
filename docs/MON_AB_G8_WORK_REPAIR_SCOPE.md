# 2512 WORK routing and BATCH cancellation repair

2026-10-29. The owner authorized continued development and flashing as needed.
The first g8 update completed its five reviewed erases/six appends and owner
restoration. Before closing the source checkpoint, review found WORK would be
intercepted by the dispatcher's single-letter W path. The RAM qualification
also exposed a cancellation gap: frozen F recognizes Ctrl-C, while ESC remains
queued. WB2 now checks queued ESC and clears cancellation before reporting it.
The monitor and F stay unchanged; B2:8/9 and optional E need replacement.

First qualify corrected services in RAM on 2512/COM4, with fresh owner RAM/ZP
escrow, matching readback helper and unchanged flash checks. Verify W versus
WORK, EDU/SRAM forwarding, M1, ordinary Modify protection, provider/module CRC
refusal/repaired admission and positive BATCH ESC/Ctrl-C stop with no following
command. Reuse the exact existing monitor and loader code; replace the WB2
payload and E dispatcher. No SPI
write, format, RTC SET/ACK, power cut or other-board access is included.

After that RAM gate passes, the repair adds **three erases: B2:8, B2:9, B3:E,
and three normal append-only erase reservations**, using admitted blank D pages. Current
room is seven normal operations; C/D erases remain excluded. Expected totals
for this update session become eight sector erases/nine appends, with counts
B2:8 593->594, B2:9 262->263, E 26->27, sequence 1021->1024, and 27 valid rows.
A/B generation 8/default B and all
other counters/settings/old raw journal rows stay unchanged. F remains golden.

Archive the three current sectors and complete flash before any request. Require
the exact postimages and counter changes, then test WORK, BATCH cancellation
and the read-only service entry points from installed MON B. No A/B, F or C/D erase is needed,
and no additional monitor/default binding is made. Restore/read back fresh
owner RAM/ZP and release COM4. The previously tested physical default boot
remains valid for unchanged F/A/B; no further physical RESET is required.
