# 2512 current MON tools: installation review

**Owner approved the five-erase/history scope on October 30, 2026.** The paired
[RAM qualification passed](2512_SERVICES_G4_RAM_ACCEPTANCE.md), restoring and
independently verifying owner RAM/ZP. The sealed plan below matches that fresh
capture. Execute only against identical admitted preimages, without retries
or additional erases. No power cuts; other boards excluded.
F remains exact STR8N-F v0.3.0 g00000001 / BASE1 / PR05.

Private plan: `output/qualification/2512-services-g4-install-scope-20261030-r1/plan.json`
in the parent project. SHA256:
`531d9981d535cd090d83fc12ad9f2a35bae59ee4fffcd05d739321154f67f9df`.
Its immutable preparation status is paired with `owner-approval.json`, which
binds the owner's later “Aproved” to this exact scope and plan hash.
Source RAM report SHA256:
`71fd00adaebf6bb34dc6b43fc0f715c659935a6297cbd1fd807595e699b2c909`.

## Intended replacements

| Target | New image | Erases |
| --- | --- | ---: |
| B2:8/9/A | Existing WF/03 bundle: WB2 g5 plus PROGRAM/SP1 g1 | 3 |
| B3:E | Existing services g4, including MAINT LOAD argument handling | 1 |
| B3:C | Required native boot/wear journal rotation | 1 |
| B3:A/B/D/F, B0/B1 and other B2 images | No replacement | 0 |

Total **five erases**: four component sectors and one C-sector rotation.
No new firmware build. Original component images and full banks are archived
before replacement. New tools remain installed at closeout; an additional
rollback erase is outside this budget. All images outside the four admitted
component targets and journal changes must match their originals.

The fresh preflight shows DE00/seq1028, 31 valid records, no ordinary append
space, occupied peer C and reserved intent page DF00. A zero-C/D-erase install
cannot fit. Native reservations are expected to be:

| Component request | Journal action |
| --- | --- |
| B2:8 | DF00/seq1029 intent reserves C's erase; erase C; C000/seq1030 root reserves the target erase |
| B2:9 | C100/seq1031 reservation |
| B2:A | C200/seq1032 reservation |
| B3:E | C300/seq1033 reservation |

There are **five new journal records**. All 15 original D records remain on
chip. The 16 original C records are archived byte-for-byte on the host before
rotation; they will no longer be on chip. Latest boot policy, generation
bindings, wear counts and prior-wear uncertainty flags carry forward.
Final expected journal:20 valid records, latest C300/seq1033.

Tracked erase counts, decimal:

| Counter | Before | After |
| --- | ---: | ---: |
| B2:8 | 595 | 596 |
| B2:9 | 264 | 265 |
| B2:A | 12 | 13 |
| B3:C | 52 | 53 |
| B3:E | 27 | 28 |
| B3:D | 33 | 33 |
| B3:F | 24 | 24 |
| MON A / B | 41 / 48 | 41 / 48 |

The plan archives original C SHA256
`0e59f864a791b3f30a7a7d49b9d0729831dbe5eaaf2d8eeecf3be54ef788f017`
and D SHA256
`8daa3d0bcc62e86fd66cc62d289d66b307c00e8f8787bbfe173e7a80d736d402`.
Any different starting image, journal, counter or nonidentical preimage invalidates
this forecast and stops the transaction before its next erase.

## Preservation and acceptance

Keep saved default B, its generation8 binding, enabled-bank mask, entries,
delay and other policy bytes. MON A/B g8 and golden F are not rewritten.
Preserve all SRAM, WORKSPACE, RTC/trim/PF flags and EEPROM. Take fresh owner
RAM0200–66FF and ZP00–DF escrow and independently restore/read it back.

Use the existing guarded OPAQUE RAM protocol. Before each component request,
verify the exact sector preimage. After each request, independently compare
the planned journal and component postimage; stop on any unexpected result.
No automatic retry or extra erase is included.

After the four component replacements, test native M1/M2/M3/W/APPS and actual
MAINT LOAD from the new board-stored WF/03 bundle. Check both cold reload and
reload over a valid old RAM cache, spaces/bad arguments, WB5 PROGRAM Table,
BATCH, AUTO/NO, CLOCK refresh and return. No PROGRAM Store or owner-app
fixture is part of this installation. Verify full SRAM equality and every
flash-bank postimage. A separately armed receiver will request one physical
RESET to check the unchanged saved B default; no USB power interruption.

Restore owner RAM/ZP and finish at the original MON B/B3> prompt with COM4
released. Restoring owner RAM can restore the older valid workbench cache:
use **MAINT LOAD** to deliberately load the new tools afterward. The current
RTC/NTP sampler profile, schedule, baselines and old samples are preserved;
any needed admission update is based on the exact installed hashes.

ASM/DBG remain deferred, nonblocking follow-on work. Published downloads,
release tags and the existing Foundation F image stay unchanged.
