# 2609 AP/02 named flash launch: passed

October 30, 2026. **65C816 emulation / FT245**, installed MON B g8 and
services g4, golden N-F v0.3.0 g1 / BASE1 / PR05.
[Public receipt](../monitors/validation/2609-ap02-positive.json),
[approved retained-WDC target review](2609_AP02_SCOPE_REVIEW.md).

## Execution and CRC admission

The existing 88-byte public-console/HOLD example ran directly from B0:9020.
Its AP/02 header's CPU tag changed 02 to 16 with a recalculated header CRC;
the executable body was unchanged and no assembler/firmware build occurred.
The first unsealed-header image was omitted from APPS and named launch was
refused. Sealing only the header CRC still refused the unsealed payload.
Sealing the payload CRC then listed APPDEMO B0:9000 and admitted
`APP APPDEMO`. Help redisplayed; bare Q returned through public HOLD to
MON B/g8/CPU16. Native Dump afterward confirmed all original owner
RAM0200-66FF and ZP00-DF unchanged by the app/return path.

## Exact restoration and history

The occupied B0:9 target was used only under its explicit two-erase approval.
The first erase installed the fixture; four checksum cells at 901C-901F were
programmed 1-to-0 without another erase. The second erase restored its exact
original 4096 bytes. Complete original WDC B0 is restored:
`1398d9551f7072ff36203307f55b7e41204f2579ce667515920a2703845eef94`.
APPDEMO is a temporary fixture and is no longer installed at closeout.

Each component and journal postimage matched the sealed plan. Final banks
were independently read twice. All 17 old journal records remain intact;
new D100/seq1032 and D200/seq1033 reserve the two B0:9 erases. Final 19 valid
rows, B0:9 count 4; C=78/D=48/E=45/F=31 unchanged (decimal). Saved default S,
mask 00, entries 8000, delay, generation fields and prior-wear flags carry
forward. No C/D erase, F/MON A/B/E replacement, other image write, reset or
power cut. No SPI SRAM/WORKSPACE service or data write was part of this
trial; a new full-SRAM comparison is not claimed. The app uses console/HOLD.

Fresh native owner RAM/ZP double escrow matched the prior qualified authority.
After flash restoration those bytes were restored and independently compared
again. Original REC> returned; COM8 released. 2205, 2512 and 2604 were outside
this trial. No vendor-monitor execution or native 816 mode is qualified.

## RTC continuity and release boundary

RTC source admission now validates the new preserving receipt and journal
rows. The profile and exact sampler bytes remain unchanged. A live read-only
RTC/NTP qualification passed with all-bank comparison and owner restoration;
its audit passed. Clock settings, trim, PF flags, baselines, prior samples and
the existing hourly schedule are preserved. This was an admission update,
not a CPU reset or a new firmware image. The prior adapter source is archived.

This closes current-g4 positive AP/02 flash-app launch on 816 emulation.
The 2512 PROGRAM acceptance separately records its repaired host directory
scope error. ASM/DBG stay deferred and nonblocking; complete b35 parity,
SS2 writes and native-mode tools remain separate work. Published Foundation
and preview archives, tags and frozen F are unchanged. Private WDC backups,
captures, plan, driver and RTC receipts remain under the parent project's
`output/qualification/2609-AP02-*` directories; public evidence contains
hashes and results without owner/vendor firmware bytes.
