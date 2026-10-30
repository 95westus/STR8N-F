# Current-time samples

Development host tool: `tools/time_samples.py`. It uses the existing native
MON `TIME` command, one sample per request, with optional periodic requests
while the collector remains running. F, monitor binaries and the published
terminal/downloads are unchanged. This is not an unattended boot service.

Disconnect the selected board's terminal first and leave it idle at its
native `Bx>` prompt. Select its exact COM port; the tool never discovers a
board by sending commands to other ports. It leaves DTR/RTS reset controls
disabled. `--idle-monitor` confirms that the board is already idle; Ctrl-C
only cancels an idle partial command so the tool can observe the prompt.
Recovery or a BIN prompt is refused. Prompt loss stops collection without
automatically resending a command. Ctrl-C on the host stops periodic sampling.

One current-time sample, appended to an existing or new host log:

```powershell
python tools/time_samples.py --port COM4 --idle-monitor --output private/time-samples.jsonl
```

Ten samples at60-second intervals, starting immediately:

```powershell
python tools/time_samples.py --port COM4 --idle-monitor --interval 60 --count 10 --output private/time-samples.jsonl
```

Omit `--count` with a positive interval to continue until Ctrl-C. For a known
USB adapter, optional `--expect-serial A10MQFLCA` pins2512's adapter. The port
must have one owner; do not run this alongside the connected Python terminal.
Intervals use the host's monotonic clock. Slow reads skip missed deadlines
instead of issuing a burst of catch-up requests. This scheduler exists only
for the lifetime of the foreground host process; it does not set RTC alarms,
install a recurring desktop task or survive closing the collector.

Each JSONL row contains the raw reply, parsed board time, board flags if
reported, status, and host UTC times before/after the read. The board time is
kept unzoned: a host collection timestamp does not prove the RTC's accuracy,
battery condition or timezone. Unavailable samples retain the reply with an
`unavailable` status. Logs append and flush after each sample. Keep private
logs out of Git.

The underlying explicit reader uses the selected EDU Rev D MCP79411 profile,
reads current-time registers and moves the read pointer. It leaves RTC data,
latched power-fail timestamps/flags, alarms, flash, boot/wear records and all
SRAM unchanged. On-board persistent WORKSPACE logging remains a separate
storage design and allocation; no PROGRAM or WORKSPACE pages are taken here.

Live2512/COM4 qualification passed on2026-10-29: one on-demand CLI sample and
three periodic CLI samples at a requested1-second interval, all four parsed.
Observed host request intervals were1.012 and0.993 seconds. Native readback
confirmed owner RAM0200-66FF and ZP00-DF unchanged, and COM4 was released.
No RAM BIN or board-storage write was used by the collector. This qualifies
collection behavior, not RTC calibration or timezone. See the hash-only
[receipt](../validation/2512-program-cleanup-time-samples.json); raw logs remain
private. Published console/ZIP files were not changed.
