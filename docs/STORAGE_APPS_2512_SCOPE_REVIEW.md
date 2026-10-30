# Storage/APPS checkpoint: 2512 scope review

Prepared 2026-10-29. F remains exact STR8N-F v0.3.0 BASE1/PR05 generation1.
Use only2512/COM4. No power cuts, other-board access, published ZIP or download
changes. This document prepares the expanded installation; it does not itself
authorize a C/D erase or the additional B2:A replacement.

RAM PROGRAM, exact duplicate cleanup, on-demand/periodic host sampling and
the APPS/ambiguity gate have now passed on2512. The original B0 fixture is
restored, all31 current raw journal records are retained, boot settings and
owner RAM/ZP are verified, and COM4 is released. Current latest DE00/seq1028;
B0:9=12, C=52, D=33 and F=24. No C/D erase or F write was used by these gates.

The conditional postimage plan is private:
`C:\SRC\STR8-N\output\qualification\2512-storage-apps-20261029-r1\conditional-install-plan\plan.json`.
Plan SHA256: `fa049d137cca582a450c0014a05785351cf16b965488806936dd2246c6b0b89d`.
This is prepared scope, not installation authorization or an acceptance claim.

## RAM/SRAM qualification and exact duplicate cleanup

Two complete131072-byte SRAM captures match SHA256
`8dbe691d4e7e2552d2cf363d21ec5f734b023aa1bbdf339da45fd9ba70952b6c`.
The primary layout is SS1, with PROGRAM0800-0FFFF and WORKSPACE10000-1FFDF;
the remaining tail is preserved too. No format or mode-register write.

| Backend/location | Name | Payload bytes | Disposition |
| --- | --- | ---: | --- |
| PROGRAM00800, slot7/seq1 | CLK |11224 | Exact duplicate of03400, superseded by CLK/seq3; specifically approved retirement |
| PROGRAM03400, slot6/seq2 | CLOCK |11224 | Retain |
| PROGRAM06000, slot5/seq3 | CLK |12231 | Different build; retain |
| Flash B1:B000 record | CLOCK |12258 | Different build; retain |

The two identical payloads have SHA256
`a91ca254bba098c289b61bc2049a02e619af083daa3b67ef120e244c2e64d7f7`.
Their records have sequence numbers, not creation timestamps. A name match or
a shared function is insufficient evidence of duplicate bytes or safe removal.

The owner explicitly approved RAM PROGRAM tests in the five initially free
directory slots0-4, payload pages9000-93FF andA000-A03F, exact restoration of
every temporary test byte, and then only slot7's commit byte0023F A5-to00.
The cleanup frees44 pages (11264 bytes) and one directory slot. It neither
zeroes nor moves the old payload. Current CLK/seq3 and CLOCK/seq2 remain valid.
Owner RAM0200-66FF and ZP00-DF must be restored/read back before releasing COM4.

Qualification covers Store/AUTO preview/cancel, commit-last writes, explicit
A000 placement, short names after long names, successive same-name versions,
full-directory refusal, combined/explicit Table, latest Restore/run, payload
CRC failure before copying owner RAM, CRC repair and public return to MON.
All temporary SRAM changes must be independently restored and the full array
compared against the expected image. The intentional duplicate retirement is
reported as a one-byte exception, not described as complete SRAM equality.

The initial RAM HELP printer exposed an8-bit pointer wrap and was repaired;
the second read-only source review found the moved directory cache still used
its old high address. Recovery verified unchanged flash and restored owner
RAM/ZP. The corrected provider uses the DIR symbol. These are development
failures, not qualified installed behavior. No flash or SRAM write preceded
the preserving recovery checkpoints.

## APPS RAM gate and B0 fixture restoration

Use the existing permission for B0 on2512. B0:9 must still match its captured
all-FF sector before programming. Install a short public-ABI AP/02 APPDEMO
fixture at9000, with its two header-CRC bytes and two payload-CRC bytes left
unprogrammed initially. Program each remaining checksum cell once fromFF to
exercise invalid-header, invalid-payload, valid-list and deliberate named
launch. Q must return through the public HOLD entry to MON B/g8.

A small SR01 CLOCK record at9E00 exercises explicit flash selection and an
ambiguous bare name also present in PROGRAM. It shares the same temporary
sector. No retained CLOCK image is overwritten.

Restore original B0:9 with one journaled erase. The last ordinary reservation
is DE00/seq1028; B0:9 increases11-to12. There is no C/D erase in this RAM gate,
and every original raw journal row is retained. Read-only APPS must not change
owner RAM/ZP. Restore/read back original owner RAM/ZP and release COM4.

## Conditional installation requiring explicit scope approval

After both RAM gates and B0 restoration pass, the intended replacements are:

| Target | Replacement | Target erases |
| --- | --- | ---: |
| B2:8/9/A | WF/03 tool bundle: copy loader, WB2/g5, PROGRAM provider |3 |
| B3:E | Services/g3: APPS and APP, explicit MAINT LOAD, existing map/wear entry points |1 |
| B3:C | Native journal peer rotation; latest policy and counts carried forward |1 |
| B3:A/B/D/F and all owner images | No replacement |0 |

The reviewed bundle takes three sectors instead of two; B2:A's original
legacy utility must be included in the host archive. WB2 remains4800-63FF,
state6400-66FF, provider6B00-77FF and non-owner scratch6700-69FF. Application
RAM stays0200-47FF. The512-byte copy loader temporarily uses6900-6AFF and
preserves monitor6A state. No public F ABI expansion or monitor rewrite.

Following the B0 restoration, native reservations are expected to be:

| Request | Journal result |
| --- | --- |
| B2:8 | DF00/seq1029 intent reserves C erase; erase C; C000/seq1030 snapshot |
| B2:9 | C100/seq1031 |
| B2:A | C200/seq1032 |
| B3:E | C300/seq1033 |

Thus the conditional installation has five total erases (four component
targets plus C), five new journal rows including the intent, and zero D/F
erases. Archive all16 old C rows byte-for-byte before rotation: those raw rows
will survive on the host, not on chip. All old D rows remain on chip. Latest
boot policy, generation8 binding, enabled banks, entries, delay, wear counts
and uncertainty flags carry forward. Counts after the complete checkpoint:
B0:9=12; B2:8=596; B2:9=265; B2:A=13; C=53; E=28. A=41, B=48, D=33 and F=24
stay unchanged. Recompute from the actual accepted RAM-gate capture before
asking for approval; no automatic write retries or extra erases are included.

Final checks must include installed MAINT LOAD despite a valid old cache,
provider admission, PROGRAM discovery, combined Table, AUTO preview/cancel,
APPS, M1/W, exact F and untouched-image checks, boot/wear carry-forward and
owner RAM/ZP restoration. Stop after APPS; source/ASM and DEBUG remain next.

## Timestamp collection boundary

TIME and CLOCK R/TIME perform explicit bounded RTC reads. The owner clarified
that timestamp collection means current-time samples, on demand or periodically,
and asked that it take priority over further cleanup. `tools/time_samples.py`
therefore adds a foreground host collector using the existing TIME command;
see TIME_SAMPLES.md for its separate live acceptance. It appends host log rows
and neither changes existing record formats nor schedules a board interrupt.
Retain distinct legacy CLOCK builds until their functions and provider
dependencies are accounted for. Immediate or periodic timestamp collection
on the board can be a later application/service using a defined log area; it must not
silently take PROGRAM pages or expand frozen F. No persistent scheduler is enabled here.
