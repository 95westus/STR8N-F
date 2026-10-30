# Development artifacts

Use the exact manifests pinned by [base1-dependency.json](../base1-dependency.json)
and the linked live receipts. Generation alone does not identify a candidate;
revision suffixes and SHA-256 values matter. These are development components,
separate from the published N-F 0.3.0 foundation downloads.

G8 current: `g00000008-r2`, `services-g00000002-wb4`, `wb2-g00000004`.
The service bundle includes the matching WB2 payload. Do not mix arbitrary
monitor/service/module layouts. See [2512 acceptance](../../docs/MON_AB_G8_2512_ACCEPTANCE.md).

Earlier g8, services g1/g2 and WB2 g2 directories retain build evidence:

- `g00000008` had the MAINT/Modify ambiguity; r2 corrected it before installation.
- `services-g00000001` had an overbroad map tag; r2 corrected it, and r3 paired
  the unchanged services with the corrected RAM monitor for qualification.
- Installed services g1 intercepted WORK as W. `services-g00000002` was an
  unqualified routing attempt; r2 corrected the branch. R3 reuses that dispatcher
  and repacks the WB2 g3 payload without rebuilding unchanged support code.
- WB2 g2 cancellation exposed frozen F's Ctrl-C-only cancel facade during a
  positive ESC test. WB2 g3 adds queued-ESC handling and clears cancellation
  before output. F is unchanged.

Build manifests retain their build-time status. Live qualification belongs in
the separate validation receipts; a built BIN alone is not an installation
recommendation. Owner flash/RAM backups and raw serial logs remain private.
