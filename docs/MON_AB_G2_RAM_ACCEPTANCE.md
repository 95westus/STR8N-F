# Mona g2 RTCC RAM acceptance: 2512

**Passed, 2026-10-29**, under the [RAM-only scope](MON_AB_G2_RAM_SCOPE.md).
The owner approved: "Run RAM-only trial; 2512 idle, COM4 free."
The [receipt](../monitors/validation/2512-mona-g00000002-RAM-rtcc.json) pins
the candidate, source and captured evidence hashes. This qualifies
`MONA-0.1.0-dev-g00000002-RAM.bin` on **2512 / 65C02 / FT245**, not g2 A/B ROM
startup or another CPU/console configuration.

## Observed behavior

Sixteen checks covered startup/initial RTC state, rejection of T arguments,
help, V before sampling, explicit T, sampled raw/normalized state, V retaining
the sample, a second T, bank inspection, Ctrl-C/ESC and Q directly to REC>.
The initial RTC adapter state was zero and remained zero after `T garbage`.
No automatic startup sample was observed.

| Read | Device-reported time, zone unspecified | Raw registers 00-06 | Displayed flags |
| --- | --- | --- | --- |
| First T | 2026-10-29 17:25:11 | `91 25 17 2C 29 10 26` | `$28` |
| Second T | 2026-10-29 17:25:14 | `94 25 17 2C 29 10 26` | `$28` |

Displayed dates/times matched independent host decoding of the dumped raw
registers and the adapter's normalized fields. V retained the first sample;
the next explicit T refreshed it. PWRFAIL and VBATEN bits remained unchanged
between reads. This is not a clock-accuracy, UTC-offset or battery-health test.
See the [adapter description](MON_AB_RTCC_ADAPTER.md) for flag meanings and
the VIA input-latch limitation.

## Preservation and final state

There were **zero flash, F or journal writes**, no boot-policy change and no
power cuts. All four banks were captured independently twice before the trial
and once afterward. Every final flash byte matched, including all images,
boot settings, wear records and frozen F. No other board was accessed.

Original owner RAM `$0200-$66FF` and ZP `$00-$DF` were restored and independently
read back. Pre-helper escrow came from the preceding verified g1 closeout and
owner-confirmed idle continuity; live ZP and RAM beyond the helper matched it.
The helper-overwritten prefix remained the original escrow, not a purported
fresh capture. **Final state: REC>, COM4 released, original images installed.**
No Mona ROM image was installed. The g2 RAM code was removed by restoring owner
RAM. Published N-F downloads and F remain unchanged.

## Remaining limits

Only normal 24-hour device reads were observed. No forced 12-hour mode, invalid
calendar, missing device, busy/stuck bus or clock fault was injected. VIA
restoration follows the reviewed source path; there was no independent
post-read register instrumentation. Input-pin output-latch contents are not
readable and are not claimed preserved byte-for-byte.

The g2 A/B binaries remain built candidates with ROM startup/handoff untested.
The earlier g1 A/B acceptance remains valid for its own hashes. Both variants
retain identical behavior at the owner's request. EDU mode, SSRAM allocation,
battery age policy and automatic startup collection remain planned adapters.
