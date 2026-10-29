# Mona common contract, revision 2 (g2 RTCC increment)

Foundation: exact N-F `v0.3.0`, F generation 00000001, BASE1 / PR05.
F stays frozen. This contract is for a new independent monitor core, not a
claim that g0034 images are compatible. [Checkpoint 1](MON_AB_COMPATIBILITY_REVIEW.md)
records why the old entry shim and private bindings cannot be retained.

## Images and entry

The first qualified candidate is **Mona 0.1.0-dev g00000001**. The current
increment is **g00000002**, whose explicit RTCC reader passed a RAM trial on
2512; g2 A/B ROM startup is untested. Both slot builds have
the same commands and implementation. The banner identifies MON A or MON B;
an optional RAM smoke image identifies itself as RAM. No monitor is yet released.

Each A/B artifact is a 4096-byte MI/01 image for B3:A or B3:B, with PR05,
new reset/prompt entry vectors at A084/A087 or B084/B087 and valid header/payload
CRC. Its SN/02 signature starts at offset 80 hex. Both entry vectors perform
the same safe initialization for the first revision. The old DBG1 header shim
and gateway are absent. Unimplemented private SR table entries refuse locally.

Entry requires IRQ disabled, decimal clear, B3 visible; 65C816 requires E=1,
D=0, DBR=0, PBR=0. F supplies this mode for a normal A/B launch. The monitor
checks the RA/1/13 facade and the pinned F before using private adapter calls.
Runtime identification includes the F locator/descriptor identity and whole-F
CRC16; the build and installation manifests retain the stronger SHA-256 pin.
An admission failure does not use private recovery or bank-switch helpers.

## Memory ownership

| Range | Contract |
| --- | --- |
| 0200-66FF and ZP00-DF | Owner RAM; ordinary Mona startup and inspection do not write it |
| 6A00-6AFF | Mona volatile state, bounded line buffer and display buffer |
| ZP E0-FF and stack 0100-01FF | System scratch; ABI/adapter clobbers permitted; no application resume state promised |
| 6700-67FF frame | Borrow only for read-only journal status validation; no writer installed |
| 7800-7BE7 | Preserve the installed BASE1 worker byte-for-byte |
| 7C/7D system state | Use only declared, pinned adapter fields and existing service buffers; not a general allocation arena |
| 7E pointers/vector/facade region | Preserve F's installed vectors; no debugger hook or gateway installation |
| 7Fxx | I/O; memory inspection refuses any range intersecting it |

6A00 is outside owner escrow 0200-66FF and outside the current READBACK service
at 6800-69B6. A RAM smoke image still borrows low RAM through raw L and needs
original pre-helper escrow; it does not inherit the ROM image's preservation
claim. Applications may reuse monitor state after a one-way handoff; monitor
reentry always initializes it again.

## Public calls and the exact-F adapter

Console initialization, PUTC/GETC, RX reset, cancel checks, hex output and CPU/
capability queries use the existing public RAM jump slots. The common core
owns its bounded line/token parser and CRC implementation. It does not call
old g0034 private console or CRC addresses.

The adapter binds only the following BASE1 private behavior:

- Read up to 16 preflighted bytes using V2W_READ and its existing selected-bank,
  address/count and 7C80 buffer fields. Restore B3 before returning to ROM.
- Execute a preflighted address through V2W_EXECUTE; it switches bank in RAM
  and performs a one-way handoff. No hardware reset or flash command is issued.
- Establish BOOT_ACTIVE for a slot and the no-journal-service dispatch pointer.
  The first monitor does not install a journal writer.
- Read the boot-selected journal page, copy it to 6700, validate its complete
  record CRC/commit and display the maximum tracked erase-attempt counter.
- Observe receive-error/source/queue state for complete-line rejection and
  CR/LF ownership, without altering console enable policy.
- Enter pinned BOOT_RECOVERY for Q, after resetting the RX session and stack.

These are private dependencies pinned to exact F, not new public ABI promises.
Isolate them in one adapter module and emit their addresses in the build manifest.
Public RAM RESET follows the saved default. Public HOLD restarts the active
monitor; neither is substituted for Q's deliberate recovery path.

## Initial commands

| Command | Behavior |
| --- | --- |
| `?` | Help |
| `V` | Mona/slot/F identity, CPU and console/capability flags; no optional-device probing |
| `T` (g2) | Explicit EDU Rev D RTCC sample; reads no RTC data automatically at startup; V later shows the retained sample |
| `B` / `B 0` through `B 3` | Inspect/set the volatile data bank; no boot setting is saved |
| `D address [end]` | Hex inspection, default 16 bytes, maximum 256 bytes, fully preflighted before reads |
| `G address` | Explicit application handoff using the selected bank and allowed entry; no implicit default boot |
| `Q` | Deliberately enter REC> regardless of the saved default, without saving settings |

Addresses are hexadecimal, 1-4 digits. Reject malformed/trailing input and
overflow; never execute a valid-looking prefix. Support CR/LF/CRLF, BS/DEL,
bounded lines and initial Ctrl-C/ESC cancellation. Cancel a dump between rows.
Input errors or queue overflow reject the entire line. Multi-port command
ownership follows the pinned BASE1 receive state; no ACIA hardware pass is claimed.

D refuses wraparound, inverted/oversize ranges and the whole command if it
intersects 7F00-7FFF. It may inspect owner/system RAM and the selected bank's
ROM but cannot write them. B changes only a volatile monitor variable.

G admits application RAM 0200-66FF or flash 8000-FFFF, excluding B3:C/D/F.
The operator supplies a real entry point for their image; inspection does not
validate an application. Cross-bank return uses public HOLD to restart the
active slot; it is not an RTS into the old application context. The RAM smoke
variant may refuse G because it has no installed monitor return slot.

## Optional modules and later work

No E extension, B2 utility provider, RTC/SPI service, EDU add-on, debugger,
filesystem, assembler or automatic startup program is required. Startup and V
always retain **EDU, SSRAM, RTCC, Battery and Wear** status rows. Compatible
optional adapters will populate EDU/SSRAM/battery data; until then the
rows use `--` rather than fabricating values. Wear can report the boot-selected,
fully CRC-checked journal page's maximum tracked count without a provider.
G2's [RTCC adapter](MON_AB_RTCC_ADAPTER.md) populates RTCC only after explicit T.
It uses the existing Mona state allocation and no legacy provider or owner RAM.

Battery and wear rows carry the console-safe `*` symbol. One shared legend
states that physical battery condition/prior flash wear are unverified and
counts are tracked attempts only. Do not repeat "unknown" on those rows.
The status display does not claim a physical battery test or lifetime wear.
Both variants remain alike at the owner's request; personalities are deferred.
CONFIG/OPAQUE remain separate tools rather than hidden write commands.

The [expanded usability target](MONA_USABILITY_PLAN.md) adds planned RAM Modify,
loading, richer startup/maps and an optional debugger. This document describes
the implemented g1/g2 contract; those planned commands are not working g2
features. TIME/record-T naming, editable ranges, debugger context ownership and
module placement must be settled in the next implementation contract.

Hardware execution is checkpoint 4; the [scoped 2512 result](MON_AB_2512_ACCEPTANCE.md)
now records the first pass. Further trials still require concrete candidate hashes, exact
allowed monitor sectors, fresh image/history/settings backups and original RAM
escrow before flashing. Completing the 2512 trial does not authorize further
writes or supersede other work using a serial port.
