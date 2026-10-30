# 2609 PROGRAM Store/Restore/run: scope review

Prepared October 30, 2026. **Approved, completed and passed** within the
temporary SRAM scope below. See [acceptance](2609_PROGRAM_POSITIVE_ACCEPTANCE.md).
This gate is
65C816 emulation / FT245 on 2609 only, using the installed MON B g8,
services g4, WB2 g5 and PROGRAM/SP1 g1 from published preview 1. F stays
STR8N-F v0.3.0 g00000001 BASE1 / PR05. No firmware replacement is proposed.

## Exact temporary storage scope

| Region | Permitted trial use |
| --- | --- |
| PROGRAM directory slots 0–3, SRAM 00040–0013F | Four temporary records; restore all 256 original bytes |
| PROGRAM payload SRAM 0C000–0C3FF | AUTO/explicit payloads, one deliberate temporary CRC fault and repair; restore all 1024 original bytes |
| Retained slots 4–7 and their CLK payloads | Read only; preserve all four versions |
| Primary header 00000–0003F, other PROGRAM bytes | Read only |
| WORKSPACE 10000–1FFDF and tail 1FFE0–1FFFF | Read only; no message allocation |
| All flash banks, including C/D/F | Read only; zero erases, byte programming or journal appends |
| Owner CPU RAM 0200–66FF and ZP 00–DF | Temporarily borrowed; restore and independently read back |

The temporary SRAM scope is **1280 distinct bytes**, restored exactly. Stores
and repairs may write those bytes more than once; this is SRAM, not an erase
budget. No record retirement, deletion, formatting, layout change, mode-register
write, RTC SET/trim/PF acknowledgement, EEPROM write, reset or power cut.
2205, 2512 and 2604 are outside this trial.

Both fresh complete 131072-byte captures match each other and the historical
SRAM archive; the [read-only preflight passed](../monitors/validation/2609-program-readonly-preflight.json):
`56cd2490028e7c6b4ee07fb26c87ea75d9d665f10c6406263c0c0f4000116a9e`.
Its four retained payload CRCs are valid, slots 0–3 are free in SS1, and the
PROGRAM boundary is 10000. All-bank double comparisons before/after and owner
RAM/ZP restoration/readback passed; final REC>, COM8 released.
The approved snapshot must match a new complete read before any trial write;
changed contents invalidate the plan.

## Trial sequence and acceptance

1. Obtain the shared serial lease, admit 2609's exact installed hashes and
   existing owner escrow, check REC>, verify all banks, and recheck the full
   SRAM snapshot. Guarded `SRAM PREP` may acknowledge disabled VIA CB flags;
   it performs no SPI clocks or RTC/PF acknowledgement and cannot override an
   enabled pin/interrupt owner.
2. Check AUTO preview/NO with no directory/payload change. Then make these four
   temporary Stores, confirming each exact PROGRAM target before YES:

   | Name | CPU source | PROGRAM destination |
   | --- | --- | --- |
   | NF30PROGRAM_LONG | 3000–3016, public OK fixture | AUTO C000 |
   | NF30P | 3000–3016, public OK fixture | AUTO C100 |
   | NF30P | 3020–3036, public UP fixture | AUTO C200 |
   | NF30EX | 3000–3016, public OK fixture | Explicit C300 |

3. Check short-after-long names, Table/discovery, new same-name version
   selection, full-directory refusal before another Store, exact load-only,
   and positive PROGRAM run through public HOLD back to MON B.
4. Change only the test payload's first byte at C200 through the allowed
   restorer; verify payload-CRC refusal before copying any destination RAM.
   Restore that test block, recheck a successful load, then restore all 20
   backed-up 64-byte directory/payload blocks.
5. Read and compare all 131072 SRAM bytes against the approved original.
   Independently compare all flash banks, restore/read back owner RAM/ZP,
   return to REC> and release COM8. Keep the existing RTC/NTP admission and
   schedule; no new time/trim setting or baseline is required.

Expected flash/journal state remains 17 records, latest D000/seq1031,
default S, C=78/D=48/E=45/F=31. Exact full-bank equality checks all other
boot-policy and wear fields too. No other-board access is part of this trial.

The narrowly allowed RAM restorer uses the existing qualification reader/
writer source and published provider, with one necessary build for this
board's exact block allowlist. F, MON, services, WB2 and PROGRAM are reused.
Host approval binds the plan SHA-256, executable driver and restorer binary.
No CPU simulator or second firmware build is required.

The sealed private plan is
`C:\SRC\STR8-N\output\qualification\2609-PROGRAM-positive-scope-20261030-r1\plan.json`,
SHA-256 `bffc613383033c2679d74ca38692045c99153ac93aa6bdac8323d251a3d54897`.
Its 767-byte RAM restorer was built once, has the distinct `PB>` prompt and
SHA-256 `5dadab107c2663f6b75b8b2267b0ca480c3dcda854219b1635063cad68ff68a1`.
It was run in the approved trial. Captures, original SRAM blocks, the restorer and host
driver remain private; no owner bytes are included in public receipts.

The two host-only handshake/acknowledgement corrections and preserving
continuations are recorded in acceptance. The Q-only amendment has plan hash
`0c2cfeb4bb5c71b41732bbbf188e1664ece1e01aca7aad976e97a72121db6d48`;
the 1280-byte scope and restorer binary were unchanged. This completed trial
grants no further storage-write or flashing permission.

## Boundary after passing

This adds positive SS1 PROGRAM evidence on 2609/816 emulation. It does not
qualify SS2 writes, native 816 mode, flash AP/02 named app launch, new 65C02
services-g4 behavior, source/ASM/DEBUG, or packaged WDC/programmer-F migration.
Those remain separate gates in the [Foundation release path](FOUNDATION_RELEASE_PATH.md).
The public Foundation and preview downloads remain unchanged.
