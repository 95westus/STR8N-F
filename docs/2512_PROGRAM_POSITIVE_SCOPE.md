# 2512 current PROGRAM Store/Restore/run: scope

**Historical plan: its narrow directory scope was not met.** The provider
allocated slots 7/4/3/2, while this plan assumed 0/1/2/3. Full verification
caught 91 remaining byte differences; a restoration-only continuation restored
exact original slots 4/7 and every SRAM/owner-RAM byte. The original failed
report and plan remain intact. See [composite acceptance](2512_PROGRAM_POSITIVE_ACCEPTANCE.md).
The union of trial/restoration addresses was 1408 bytes, not 1280. Future
planners must admit the allocator's actual last-free slot order before Store.

October 30, 2026. Owner requested this positive 65C02 trial before considering
soak. Use installed MON B g8, services g4, WB2 g5 and PROGRAM/SP1 g1, with
golden N-F v0.3.0 g1 / BASE1 / PR05. No firmware build or replacement.

## Temporary storage and restoration

Use only SS1 directory slots 0-3 at SRAM00040-0013F and payload pages
0C000-0C3FF: **1280 distinct bytes**, all restored exactly. Preserve the
retained CLK/CLOCK records in slots5/6, free slots4/7, the primary header,
other PROGRAM bytes, WORKSPACE10000-1FFDF and tail. No format, record
retirement, mode-register change or message allocation.

Before any write, take fresh native owner RAM0200-66FF/ZP00-DF double escrow,
compare all four flash banks twice, mount the actual PROGRAM format, read the
complete 131072-byte SRAM and require its latest preserved hash:
`580a60e314e7c91703a319f03516bd803f36a8202f773e4206b6d4aa69d227aa`.
Require free slots0-3 and free pagesC0-C3; any changed preimage stops writes.
No allocation is admitted merely because a byte looks erased.

AUTO currently chooses0800. Test AUTO preview followed by NO; actual Stores
use explicit C000/C100/C200/C300 so the already qualified 767-byte PB fixture
can restore every permitted block. Its unchanged allowlist covers exactly
four64-byte directory blocks and sixteen64-byte payload blocks. No new build.

Store the existing public-console/HOLD 23-byte OK fixture under a16-character
name atC000, a short name atC100, a newer same-name UP version atC200 and a
separate explicit record atC300. Check occupied-payload refusal, Table,
latest-version checked load-only, exact destination bytes and positive run/
public HOLD back to MON B. Change the test C200 payload's first byte, require
CRC refusal before copying destination RAM, repair it and verify load again.
The remaining free slots are preserved; directory-full testing is outside
this trial rather than falsely inferred from the four temporary records.

Restore all20 permitted64-byte blocks with CRC-framed writes and independent
readback, then compare the complete SRAM. Compare all four flash banks twice,
restore/read back fresh owner RAM/ZP, finish at original MON B/B3>, release
COM4 and retain the native TIME RTC/NTP profile/schedule. Golden F, all images,
boot policy and wear history stay byte-identical:20 rows, C300/seq1033,
saved B/g8, C=53/D=33/E=28/F=24. Zero flash/journal/WORKSPACE writes,
clock/trim/PF changes, resets or power cuts. 2609's AP/02 flash target has a
separate review; 2205 and2604 are excluded.

Sealed private plan in the parent project:
`output/qualification/2512-PROGRAM-positive-scope-20261030-r1/plan.json`,
SHA256 `b5ef1a5a542e6a69af2aa5891d99256ae59993011c79366422a0f8912f337bd9`.
The existing PB fixture remains
`5dadab107c2663f6b75b8b2267b0ca480c3dcda854219b1635063cad68ff68a1`.
