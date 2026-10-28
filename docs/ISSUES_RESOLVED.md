# BASE1 integration and remaining release issues

Resolved in this checkpoint:

- STR8N-F / BASE1 / PR05 naming, F startup version/generation and a bounded,
  CRC-protected identity descriptor.
- Append-only F change preserving existing PR05 addresses, worker/vector
  bytes and hardware vectors. No saved setting is rewritten.
- Separate F generation, SNBT monitor generation, journal sequence and OS
  identity. No board-service status work added to F.
- Synchronized BASE1 OPAQUE/READBACK prompts, binary sizes and host SHA pins;
  refreshed RAM MAP's exact-F CRC guard and immutable-image seal.
- WDC resident recognition in RAM, with no whole-bank, EDU/SPI or bootability
  inference. Only fingerprints/labels are included, never vendor code.
- Corrected map roles: no assumed B0 backup, A/B monitor reservation or E
  provider ownership. Only C/D/F are reserved in BASE1.
- Fixed detailed-map sector output that used an ASCII parser instead of a
  numeric nibble printer.
- Restored compact M1/M2/M3 syntax alongside spaced M 1/2/3, retaining range
  and trailing-input validation. Only MAP needed this follow-up rebuild.
- Removed alternate F-building paths. The canonical builder reuses frozen F
  and supports rebuilding only a selected RAM component.
- Reused independent NFM1/NFA1 helpers without rebuilding. Older exact-F-bound
  optional payloads remain reference-only, not matching BASE1 binaries.

Serial Console 0.1.0 now supplies file selection, prompt-gated RAM loading,
MAP/CONFIG/OPAQUE/DEMO presets, explicit connection and optional host logging.
One I/O owner keeps terminal input out of a BIN. Ctrl-C is limited to before
payload, and disconnect waits for serial drain/idle. The console, requirements
and operator guide are included by the candidate packager. Host/Tk checks do
not qualify physical function keys or USB serial behavior.

Remaining before a complete public migration release:

1. Hardware acceptance on supported CPUs/USB: physical reset, banner, recovery,
   first-byte Ctrl-C/normal BIN loading, journals, opaque operations and boot,
   and independent preservation/restoration evidence.
2. Existing-SNBT F upgrade with a durable onboard append reservation. The
   current factory path refuses this unsupported upgrade and preserves history.
3. Generic live provisioning after programmer-installed F. Per-run plan/engine
   and recovery wrapper exist; the live WDC command is not this route.
4. Qualified vendor-startup/peripheral behavior across the WDC reset boundary
   and an explicitly admitted interrupted-migration recovery procedure.

No board was accessed for this checkpoint. 2205 remains read-only. Host tests
and source freeze do not mark these remaining items complete.
