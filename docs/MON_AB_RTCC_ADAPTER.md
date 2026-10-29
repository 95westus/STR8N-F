# Mona generation 2: explicit RTCC reader

**RAM reader passed on 2512; A/B ROM qualification pending.** Mona remains
**0.1.0-dev**, now generation **00000002**. A and B have identical commands,
as requested. The [candidate manifest](../monitors/candidates/g00000002/manifest.json)
pins A/B/RAM bytes; [build/review evidence](../monitors/review/g00000002-rtcc-candidate.json)
records the creation-time source hashes and stopped build attempts. The subsequent
[RAM acceptance](MON_AB_G2_RAM_ACCEPTANCE.md) qualifies only the exact g2 RAM
artifact. Generation 1's
[2512 acceptance](MON_AB_2512_ACCEPTANCE.md) still applies only to its own hashes.

## Commands and display

`T` explicitly samples the MCP79411 through **WDC EDU Rev D wiring: VIA1 PA0
SCL, PA7 SDA**. It requires exclusive use of those pins as idle, high inputs,
with VIA port-A input latching disabled. `T` with arguments is rejected before
any adapter call. Startup, `V` and `?` do not probe hardware. `V` displays the
last successful sample until monitor reentry; it does not refresh the clock.
A failed `T` invalidates the previous sample.

Illustrative output after a successful read, not a captured hardware result:

```text
Mona 0.1.0-dev g00000002 / MON A
N-F 0.3.0 g00000001 / BASE1 / PR05
...
EDU: --   SSRAM: --
RTCC: 2026-10-29 22:41:05 flags $28* (sample; zone --)
Battery: --*
Wear: B2:8 tracked max $000250*
-- no reported data; T explicitly reads EDU Rev D RTCC.
* Battery condition/prior flash wear unverified; counts are tracked attempts.
```

The displayed year is limited to 2000-2099. Raw 12-hour readings are normalized
to 24-hour output; BCD, month length, leap day and field ranges are checked.
The weekday field is range-checked but is not independently recomputed from the
date. The chip stores no time zone; no local/UTC label or offset is inferred.

`flags` preserves the observed RTCWKDAY bits: `$20` OSCRUN, `$10` PWRFAIL,
`$08` VBATEN. These are device status/configuration/history, not battery-health
measurements. A power-fail flag remains set until separately acknowledged by
another tool; this reader does not clear it. See Microchip's
[MCP79410/11/12 data sheet, DS20002266K](https://ww1.microchip.com/downloads/aemDocuments/documents/MPD/ProductDocuments/DataSheets/MCP79410-MCP79411-MCP79412-Battery-Backed-I2C-RTCC-DS20002266.pdf),
registers 00-06 and sections 6.1.4-6.1.5.

| Error printed by T, hexadecimal | Meaning |
| --- | --- |
| 01 | Port-A input latching enabled, a bus pin configured as output, or initial bus not high; no VIA writes |
| 02 | Device did not acknowledge |
| 03 | SCL did not rise within the bounded wait, including a failed STOP |
| 04 | Clock stopped or invalid BCD/calendar/range |
| 07 | Seconds changed during all three snapshot attempts |

## Access and ownership

The reader writes the I2C register pointer, performs a repeated START and reads
registers 00-06, then rereads seconds. It makes at most three attempts for a
coherent snapshot, with at most 255 polls per SCL wait. It never sends an RTC
data byte, SET, power-fail acknowledgment, EEPROM write, SRAM write or flash
command. The shared device address pointer advances as part of reading; its
previous value is not restored.

The adapter uses only Mona state at `$6A90-$6AB6`, system stack and existing
console calls. It does not install the old service at `$6500-$66FF`, use its
RAM flags, call a legacy E/B2 provider, format SRAM or change saved EDU policy.
I/O writes are confined to VIA1 DDRA `$7FC3` and non-handshaking ORA `$7FCF`.
ACR `$7FCB` is read for admission; PCR, IFR and IER are untouched.

After bus admission, the original DDRA and sampled ORA are saved. Both bus
pins are released before the sampled ORA is restored, including on timeout.
DDRA is restored; other configured output bits retain their sampled values.
The VIA cannot expose the prior output-latch values of pins configured as
inputs. Those input-pin latch values are therefore not claimed to be preserved
byte-for-byte; the pins remain inputs. This is an explicit hardware-adapter
limit, not a claim that I/O reads have no side effects.

## Legacy reuse decisions

The old rich display reads `$7D27` EDU mode and optional service RAM, calls the
legacy RTC/banner providers, and reads SSRAM allocation through the old SM
gateway. Those values are not populated by BASE1. The new reader borrows the
bounded I2C read approach of the retained RAM collector, with new state ownership,
an idle-input/latching guard, no history/EEPROM access and no private provider
calls. Reference-file hashes are in the review evidence.

EDU mode, SSRAM PROGRAM/WORKSPACE allocation and battery age policy remain
unported. A successful RTC response does not imply EDU ON or validate an SSRAM
layout. They remain `--`. Planned follow-ons are separate adapters with explicit
admission, current measurements and no reliance on stale legacy RAM.

## Build and next qualification

```text
python tools/build_mona.py --generation 2 --out build/NEW-DIRECTORY
```

Do not rebuild merely to reproduce these candidates. The successful build has
3704 linked bytes in each 4096-byte slot, leaving 264 bytes after the linked
payload; RAM is 3695 bytes. Two earlier attempts stopped: one at assembly on
generated labels containing a hyphen, the next after linking A on a descriptor
adjacency assertion. The label sanitizer and include order were corrected;
the complete A/B/RAM build then passed. No CPU model or board was used.

F and the qualified g1 artifacts remain unchanged. G2 is stored separately in
`monitors/candidates/g00000002/`; it is not part of the published N-F downloads.
The [reviewed RAM-only scope](MON_AB_G2_RAM_SCOPE.md) passed with 16 recorded
checks and two coherent device samples; all flash bytes and owner RAM/ZP were
preserved. The build manifest/review retain their pre-trial labels; the separate
acceptance receipt records the later RAM result. No new monitor-sector install
occurred or is authorized by that RAM trial.

Only 264 bytes remain after the ROM payload. Further status adapters need a
size review and may belong in an optional provider image; no additional owner
sector is reserved or assumed free by this work.
