# Mona g00000005: monitor and WB1 commands

Mona **0.1.0-dev g00000005** provides the same commands in A and B, on frozen
N-F 0.3.0 / BASE1 / PR05. This is a development monitor, not a replacement N-F
release. The [g5 / WB1 acceptance](MON_AB_G5_2512_ACCEPTANCE.md) covers installed
2512 A/B and the physical B default. G4's force evidence is retained in its
[earlier receipt](../monitors/validation/2512-mona-g00000004-install.json).

The [WB1 module](MONA_WORKBENCH_WB1.md) adds Table/Restore and explicit read-only
EDU/SRAM status. WB1 g2 is RAM-qualified, not stored in flash. Load it with L
when needed; restoring owner RAM evicts it. No persistent module sector has
been allocated.

## Commands

| Command | Function |
| --- | --- |
| `?` | Help |
| `B0`-`B3` or `B 0`-`B 3` | Select the flash data bank; RAM is common to all banks |
| `D addr [end]` | Hex/ASCII dump; default 16 bytes; explicit larger ranges allowed |
| `M addr byte...` | Checked ordinary owner-RAM edit, 1-8 bytes, with readback |
| `!M addr byte...` | Explicit force edit, 1-8 bytes; B3:C/D/F always protected |
| `TIME` | Fresh bounded EDU Rev D RTCC sample; no clock-setting or flag clearing |
| `V` | Status, including the last labelled RTCC sample and tracked wear maximum |
| `G addr` | Explicit application entry; public HOLD restarts the active monitor |
| `L` | ROM Mona: enter frozen F's raw RAM BIN loader; Ctrl-C before payload returns REC> |
| `T [bank]`, `R [bank] name\|address [L]` | Loaded WB1: Table/Restore; suffix L loads only |
| `EDU [ON\|OFF]`, `SRAM`, `WORK` | Loaded WB1: explicit session EDU policy and read-only layout/capacity |
| `Q` | Deliberately return to REC>, regardless of the saved default |

Addresses and data are hexadecimal. Lowercase is accepted. Parse/overflow/
range checks cover the whole input before an edit begins. Ctrl-C/ESC cancel
input and stop a dump between rows. An edit already being committed is not a
transactional rollback operation. A RAM smoke image refuses G and ordinary M
into its code pages.

`TIME` replaces the development g2 clock command T. T now dispatches to the
loaded WB1 record table; missing/corrupt modules are refused. Maps, Store,
apps/maintenance routing, source/ASM/DEBUG, interactive Modify and dump
continuation/paging remain planned.
Dump ranges are no longer limited to 256 bytes. A range intersecting $7F00-$7FFF
is refused as a whole; ordinary D does not inspect I/O.

## Dump and ordinary Modify

```text
MonaB> D 2000 203F
MonaB> M 2000 41 42 43 00
2000: 41 42 43 00                                      |ABC.|
MonaB> D 2000 2003
```

The shown addresses are examples, not free-space declarations. M intentionally
changes owner RAM. Editable ranges are owner ZP $0000-$00DF and application RAM
$0200-$66FF. Stack, system ZP, monitor/worker/vector state, I/O and all ROM are
excluded from ordinary M. The monitor verifies each stored RAM byte and echoes
an independently read hex/ASCII row. A hardware verify failure can leave a
partial edit and reports that explicitly.

G5 additionally reserves 5000-66FF against ordinary M while WB1 passes admission.
The RAM smoke monitor declares its own code reservation to module Restore.
Forced !M may deliberately evict the module; a bad module CRC blocks dispatch.

Examples refused before any target write:

```text
M 2000 AA ZZ
M 00DF 11 22
M 66FF 11 22
M F000 00
```

## Forced Modify

`!M` is the override. It can write owner/system ZP, stack, RAM, vectors, worker
memory and I/O, and program allowed flash in the selected data bank. It does
not ask a second confirmation. Golden **B3:F** and the **B3:C/D boot/wear
journal** remain protected even under force. A/B and other owner images are
not protected from an explicit force command.

For example, `!M 0120 A5` requests an actual stack-page write. Raw RAM/I/O
edits report `Forced; no raw readback.` They do not automatically read the
target: an I/O read may acknowledge or act on the device. Use D to inspect
ordinary RAM where appropriate. Raw stores are staged as absolute instructions
in RAM so changing a ZP pointer cannot redirect later stores in that unit.

Forced system edits can stop the console, replace the selected hardware bank
or invalidate execution. Ongoing monitor code can reuse volatile locations
immediately afterward. No application-context resume or atomic update against
arbitrary NMIs is promised. Force targets may include the monitor itself;
ordinary M protections do not apply. Keep recovery available.

For flash, the complete unit must satisfy **old AND requested = requested**.
Identical bytes are skipped; a requested 0-to-1 change refuses the entire unit
before the first program pulse. The command **never erases**. It executes its
program/poll path from RAM, returns B3 and restores the running LED state after
successful completion, then displays readback. A program failure prints `!`
and halts in RAM; use physical RESET to return through golden F.

The bit-transition check is not a replacement for the flash manufacturer's
programming rules. Microchip's
[SST39SF010A/020A/040 data sheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MPD/ProductDocuments/DataSheets/SST39SF010A-SST39SF020A-SST39SF040-Data-Sheet-DS20005022.pdf)
requires sector erase before programming. Repeat-programming an already
programmed byte is not qualified here. The live tests used fresh FF cells in
newly erased A/B replacement sectors, not repeated programming of old data.

Crossing $FFFF or mixing RAM/I/O and flash in one unit is refused. Raw force
uses temporary writer storage at $6B00-$6B7F or $6D00-$6D2A, selected away from
its raw target; these are declared monitor workspace outside owner escrow.

## Boot and current limits

At REC>, `A` or `B` explicitly admits and enters that slot through F. Automatic
default A/B boot also checks the saved generation binding. Installing a new
generation does not silently change that binding; the matching RAM CONFIG
command `C B` can explicitly save B with its current generation. See the
[2512 binding review](MON_AB_G4_DEFAULT_BINDING_SCOPE.md).

The richer startup profile, EDU mode, SSRAM allocation and battery age policy
remain unported. Their rows use `--`; TIME supplies only a labelled device-time
sample with no inferred zone. Battery health and prior physical wear retain
the shared `*` caveat. No native 65C816 debugging or alternate-console
qualification is implied by the foundation's advertised vector capabilities.
