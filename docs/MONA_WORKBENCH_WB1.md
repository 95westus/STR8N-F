# Mona g5 / WB1: records and EDU/SRAM checkpoint

2026-10-29. **2512 qualification passed: g5 installed in A/B; WB1 g2 RAM-qualified.**
See [acceptance](MON_AB_G5_2512_ACCEPTANCE.md). Published kit/downloads and golden
F remain unchanged. The full workbench still requires Store,
apps, maintenance/config/opaque, source/ASM/DEBUG and SRAM storage/messages.

## Implemented in candidates versus planned

| Component | Candidate implementation | Status |
| --- | --- | --- |
| Mona g5 A/B | Identical commands; native L; checked WB1 dispatch; normal M respects module RAM | Qualified and installed on 2512 |
| Mona g5 RAM | Same bridge; L/G refused; Restore protects this monitor's code pages | Qualified on 2512 |
| WB1 g2 RAM | Table/Restore; session EDU control; guarded SRAM layout/capacity; Q to monitor | Qualified on 2512; reload after owner-RAM restoration |
| Store and apps/maintenance routing | Still required | Planned |
| Source editor/ASM/DEBUG | Retained legacy assets need compatible ports | Planned |
| SRAM PROGRAM/source writes | No write code in WB1 | Planned |
| Persistent WORKSPACE messages | Allocation review and append-only writer needed | Planned |

Current files and SHA-256:

| File under monitors/candidates | Bytes | SHA-256 |
| --- | ---: | --- |
| `g00000005/MONA-0.1.0-dev-g00000005-A.bin` | 4096 | `05fabfc5b5efc10eedaa70eabe773096f661a40241cfa3e757d004633bc9a87b` |
| `g00000005/MONA-0.1.0-dev-g00000005-B.bin` | 4096 | `13b399d70bcbee3e333dc35972e9f8d8a6515bd99aeb5dd81d1a95089571c8d2` |
| `g00000005/MONA-0.1.0-dev-g00000005-RAM.bin` | 3908 | `4bc99ac1c10c13552207a62f4665585fb30d687f89de35b5b9f4a6ed200934e8` |
| `wb1-g00000002/MONA-WORKBENCH-WB1-g00000002-RAM.bin` | 5376 | `63c5eab2b79ae4fbe5e9dd63e4f41a1bfc23c8bffbb306f7fc07976f7440f727` |

A/B payloads use 3917 bytes, leaving 51. WB1 g2 code uses 3997 of 5118 bytes,
plus its two-byte CRC trailer. F stays 4096 bytes with SHA-256
`8f4d35ac66730daa773515980983fcf442be3b1bdf1e523d3752ec3615657cc1`.

## Load and return

WB1 is an explicitly loaded **RAM program**, not a flash-space reservation.
No B0/B1/B2 or B3:8/9/E sector is allocated. Illustrative candidate commands
below are **not captured hardware output or approval to install A/B**:

```text
REC> L
SEND BIN
<send MONA-WORKBENCH-WB1-g00000002-RAM.bin>
WORKBENCH> ?
WORKBENCH> T 1
WORKBENCH> EDU ON
WORKBENCH> SRAM
WORKBENCH> Q
MonaB>
```

Q uses public RAM HOLD to return to the active monitor, or recovery if no valid
active monitor exists. It does not save boot settings. The module remains in
borrowed RAM until overwritten/restored.

G5 ROM adds L at the Mona prompt, tail-entering the exact frozen F loader.
First-byte Ctrl-C cancellation still returns REC>. This is idle-terminated raw
BIN with the existing limits, no length framing or whole-transfer checksum.
WB1 separately CRC-checks its module block before copying/entering it; that CRC
does not cover its raw loader. RAM-loaded Mona refuses L to avoid self-overwrite.

Older g4 has no L or module dispatch: use Q to REC> for loading there. The
qualification loaded g5 RAM separately while retaining WB1 at 5000, before
installing either slot. Installed g5 now provides native L and module dispatch.

## Commands

| WB1 command | Function |
| --- | --- |
| `?` | Shell help; g5 Mona's own ? lists the WB1 group |
| `B0`-`B3` | Select the data/record bank, no boot save |
| `T [bank]` | Bytewise cached SR/01 scan of selected bank 8000-DFFF |
| `R [bank] name\|address [L]` | Restore complete record; L=load only, otherwise explicitly run its load address |
| `EDU` / `EDU ON` / `EDU OFF` | Show/select session Rev D wiring policy; no probe or policy persistence |
| `SRAM` | Explicit guarded SS/01 or SS/02 layout and PROGRAM/WORKSPACE capacity read |
| `SRAM PREP` | Explicit disabled-CB flag acknowledgment after idle guard; no SPI clocks |
| `WORK` | Same read-only layout/capacity status; no allocation changes |
| `Q` | Shell: HOLD to active monitor; g5 Mona's own Q remains REC> |

Numbers are hex. Commands are uppercase-normalized and bounded to 40 characters;
malformed, overlong, cancelled or receive-error input is rejected as a whole.
T uses `+` for complete 3F, `?` for pending FF, and skips a structural record's
declared extent. A header is not an application compatibility or free-space claim.

SR/01 is a 24-byte header: SR, version01, state, LE16 RAM load and length,
then an optional canonical printable/NUL-padded 16-byte name. **It has no
payload checksum.** Restore compares each copied RAM byte with its flash source;
it cannot prove that an old payload is intact. Names are unique within the
selected bank here; the legacy cross-bank name search remains planned. All-hex
tokens are addresses. Use an address when a name is ambiguous.

Restore's complete destination must be 0200-4FFF and outside its RAM caller's
code reservation. Refused bounds fail before copying; cancel/verify failure
during copying reports a partial load. R without L is an explicit user launch,
not legacy private-ABI qualification. Saved 2512 data includes B1:8000 HELLO0200
(0200/0017) and B1:B000 CLOCK (2000/2FE2). Recheck live data before use; CLOCK
must stay load-only until ported. These are not scratch allocations.

## EDU/SRAM access and boundaries

Startup EDU OFF makes no SPI transaction. ON selects EDU Rev D wiring; it does
not prove hardware presence. PB0=SCK, PB1=MOSI, PB2=SRAM CS, PB5=MISO; PB3's
other CS stays high during a transaction. Before ORB reads/driving pins the
guard requires IER&18=0, PCR&F0=0, ACR&1E=0, DDRB&2F=0. Normal reads also
require IFR&18=0. Busy pins/pending CB flags refuse without ORB reads or clocks.
Only explicit PREP may read ORB to acknowledge disabled CB flags after the
other guards pass. It is never automatic.

The adapter sends only RDMR05 and READ03, with a fresh address/CS cycle per byte;
00/40/80 modes are accepted without WRMR. DDRB and sampled ORB are restored.
Input pins' prior output-latch values cannot be read: sampled ORB restoration
does not certify those hidden latch values. This foreground, masked-IRQ,
nonreentrant adapter does not arbitrate against an application's NMI handler.

Only 64-byte layout metadata at 00000, and if necessary 00240, is read.
Committed SS/02/08 needs CRC, nonzero generation, canonical reserved fields,
commit and supported boundary. A valid fallback is explicitly labelled for
primary review. WB1 g2 also validates primary SS/01: zero generation, fixed 10000 boundary,
CRC/reserved/commit checks and no fallback. Absent/invalid/uncommitted data is
not free space.
There is no WRITE02, WRMR01, format, repair, resize or write probe.

| PROGRAM boundary | PROGRAM payload | WORKSPACE after layout overhead |
| --- | ---: | ---: |
| 04000 | 14336 | 114656 |
| 08000 | 30720 | 98272 |
| 0C000 | 47104 | 81888 |
| 10000 | 63488 | 65504 |

These are **layout capacities, not free-space counts**. Existing WORKSPACE
allocations are not inspected/adopted. PROGRAM, source, WORKSPACE and messages
are not written by WB1.

Persistent messages/metadata belong in a separate append-only **WORKSPACE**
allocation, outside formatted PROGRAM space and C/D boot/wear history. EDU,
RAM, SRAM and RTCC status can become collected workbench events; they do not
belong in golden F. Log entries and persistent EDU policy are distinct.

Before enabling writes, inventory/admit existing WS/WC/SP allocations, select
a nonoverlapping bounded region, define version/length/type/sequence/CRC/commit,
then add bounded scan/append/full behavior. Replacement/deletion should append
supersession/tombstone metadata. Full/invalid logs must not trigger automatic
reclaim or formatting. Source SAVE/LOAD and PROGRAM retain separate ownership.
Messages should survive reset; retention without main power depends on the
actual battery/SRAM supply. Battery health and prior physical flash wear remain
`*` unverified; this module does not measure them.

## RAM and module interface

Raw transfer staging borrows 0200-16FF. The loader checks RA/01/13, exact frozen
F CRC16 and staged-module CRC before copying to 5000-63FF. State borrows
6400-66FF. Escrow/restore owner RAM and ZP before testing: this is intentional
RAM use, not a preserving startup feature.

The immutable 5120-byte block starts `MW 01 14 PR05`, JMP command at 5008 and
JMP shell at 500B. A big-endian CCITT trailer at 63FE/63FF, FFFF seed, gives zero
residue over all 5120 bytes. G5 checks header+CRC before every bridged command;
invalid/absent modules refuse while core D/M/G/Q remain available.

Call: A=data bank, X/Y=bounded NUL-terminated line. Caller writes 6550 with its
lowest Restore destination page (2 for ROM, 12 for this RAM candidate); shell
entry clears it. Return: C=handled,A=bank. Requires 65C02 or 816E, D/DBR/PBR=0,
SEI/CLD. This development contract does not extend F's public ABI.

Normal M protects 5000-66FF while WB1 passes admission. !M retains explicit
force behavior and may evict/corrupt it; subsequent dispatch must reject bad
CRC. B3:C/D/F protection remains. Owner-RAM restoration deliberately evicts WB1.

WDC builds and artifact layout/header/CRC checks passed; no CPU simulation or
offline regression group ran. Corrective builds resolved WDC's relocatable
EQU restriction and the RAM-client Restore overlap discovered during bridge
integration. Earlier logs/bytes are retained under ignored
`build/mona-workbench-checkpoints/`; no reproduction build was performed.

The [RAM-only scope](MON_AB_G5_WB1_RAM_SCOPE.md) and subsequent
[A/B installation scope](MON_AB_G5_2512_INSTALL_SCOPE.md) are closed by
[acceptance](MON_AB_G5_2512_ACCEPTANCE.md). Next: Store, apps/maintenance and
source/ASM/DEBUG. Future candidates still require execution qualification.

## Live continuation finding

The first 2512 RAM runs read a committed legacy SS1 layout, not SS2. WB1 g1
correctly refused it. The read-only g2 compatibility increment admits the
existing SS1 format without changing a byte of PROGRAM/WORKSPACE. Mona g5
A/B/RAM BINs were not rebuilt. Candidate manifests distinguish actual core
assembly inputs from unrelated WB1 files previously inventoried alongside them.
The host harness also now matches a prompt only at a line boundary, because
a dump of the RAM monitor can contain the literal prompt in its ASCII column.
The corrected trial and A/B installation passed, including physical saved-B
boot and full owner-RAM/ZP readback. The original g1 candidates and interrupted
host-run evidence are retained separately. SS2/fallback hardware paths remain
unobserved; the positive SRAM evidence is for this board's primary SS1 layout.
