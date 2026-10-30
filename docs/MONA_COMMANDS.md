# MON A/B g00000008: board-stored services

STR8-N **0.1.0-dev g00000008** is installed in both slots on 2512, using frozen
N-F 0.3.0 / BASE1 / PR05. [Acceptance](MON_AB_G8_2512_ACCEPTANCE.md) records both
slot checks, physical saved-default B boot and exact owner RAM/ZP restoration.
The prompt B0> through B3> shows the selected data bank; slot identity stays
in the banner. Q/reentry starts with data bank 3 again.

M1/W use the optional E dispatcher without borrowing owner RAM. WB2 g4 is stored
in B2:8/9; it borrows 4800-66FF and leaves application RAM 0200-47FF while loaded.
MAINT/CLOCK accepts a valid compatible RAM module and loads flash only if it is
absent/invalid. Owner restoration reinstated cached g3 on2512. To explicitly
load current flash g4, use **B2**, then **G 8000**; Q returns to MON B. No host
BIN is needed. See [AUTO acceptance](MON_STORE_AUTO_2512_ACCEPTANCE.md).

CLOCK is a read-only page. FLASH currently aliases the workbench. Advanced
CLOCK, the full sector editor/erase/copy, merged CONFIG menu and complete
[2.0b35 parity](MON_B35_PARITY.md) remain open. Mona is retired; old filenames
and immutable qualification artifacts retain their historical spelling.

## Commands

| Command | Function |
| --- | --- |
| `?` | Help |
| `M`, `M1`, `M2`, `M3` | Sector-format grid, layout notes, or wear counters; read-only |
| `W` | All32 tracked erase counts in hex; shared prior-wear caveat |
| `APPS` | Native service catalogue; compatible owner-app discovery remains planned |
| `CLOCK` | Use cached module or load flash if absent; read/refresh RTC, Q back; no SET/history administration |
| `MAINT`, `FLASH` | Enter cached module or load flash if absent; Q returns to the active monitor |
| `BATCH cmd;cmd` | Loaded WB2 returning-command subset, 34 text bytes; full core/app parity open |
| `B0`-`B3` or `B 0`-`B 3` | Select the flash data bank; RAM is common to all banks |
| `D addr [end]` | Hex/ASCII dump; default 16 bytes; explicit larger ranges allowed |
| `M addr byte...` | Checked ordinary owner-RAM edit, 1-8 bytes, with readback |
| `!M addr byte...` | Explicit force edit, 1-8 bytes; B3:C/D/F always protected |
| `TIME` | Fresh bounded EDU Rev D RTCC sample; no clock-setting or flag clearing |
| `V` | Status, including the last labelled RTCC sample and tracked wear maximum |
| `G addr` | Explicit application entry; public HOLD restarts the active monitor |
| `L` | ROM MON A/B: enter frozen F's raw RAM BIN loader; Ctrl-C before payload returns REC> |
| `T [bank]`, `R [bank] name\|address [L]` | Loaded WB2: Table/Restore; suffix L loads only |
| `AREA bank first last`, `AREA` | Loaded WB2 g4: declare/close a B0/B1 owner flash window; no flash write |
| `S bank address\|AUTO RAMfirst RAMlast [name]` | Loaded WB2 g4: explicit or automatically determined flash start; YES, no erase; [details](MON_STORE_AUTO.md) |
| `HELP` | Full loaded-module help |
| `EDU [ON\|OFF]`, `SRAM`, `WORK` | Loaded WB2: explicit session EDU policy and read-only layout/capacity |
| `Q` | Deliberately return to REC>, regardless of the saved default |

Addresses and data are hexadecimal. Lowercase is accepted. Parse/overflow/
range checks cover the whole input before an edit begins. Ctrl-C/ESC cancel
input; Ctrl-C stops a core dump between rows. Both keys stop WB2 Table/BATCH.
An edit already being committed is not a
transactional rollback operation. A RAM smoke image refuses G and ordinary M
into its code pages.

`TIME` replaces the development g2 clock command T. T now dispatches to the
loaded WB2 record table; missing/corrupt modules are refused. Native maps/wear and the service front door now work. Full app discovery,
source/ASM/DEBUG, interactive Modify and dump continuation/paging remain planned.
Dump ranges are no longer limited to 256 bytes. A range intersecting $7F00-$7FFF
is refused as a whole; ordinary D does not inspect I/O.

## Dump and ordinary Modify

```text
B3> D 2000 203F
B3> M 2000 41 42 43 00
2000: 41 42 43 00                                      |ABC.|
B3> D 2000 2003
```

The shown addresses are examples, not free-space declarations. M intentionally
changes owner RAM. Editable ranges are owner ZP $0000-$00DF and application RAM
$0200-$66FF. Stack, system ZP, monitor/worker/vector state, I/O and all ROM are
excluded from ordinary M. The monitor verifies each stored RAM byte and echoes
an independently read hex/ASCII row. A hardware verify failure can leave a
partial edit and reports that explicitly.

G8 reserves 4800-66FF against ordinary M while WB2 passes admission.
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

The richer startup profile, persistent EDU policy, SSRAM allocation and battery age policy
remain unported. Their rows use `--`; TIME supplies only a labelled device-time
sample with no inferred zone. Battery health and prior physical wear retain
the shared `*` caveat. No native 65C816 debugging or alternate-console
qualification is implied by the foundation's advertised vector capabilities.


## BATCH and board settings

The current BATCH allowlist is B/bank, T/Table, ?, HELP, EDU and bare SRAM/WORK
status. All separators and allowed command names are checked before the first
command; individual arguments are checked when that command is reached. A
failure stops subsequent commands. The queue is separate from console input;
Store/YES, loaders, PREP, R/run and application handoff are excluded. Positive
ESC and Ctrl-C cancellation passed during Table inside BATCH, with result $03
and the following bank command unexecuted. WB2 adapts frozen F's Ctrl-C-only
facade to recognize queued ESC; ordinary noncancel typeahead is not consumed.

```text
B3> M1
B3> W
B3> MAINT
WORKBENCH> BATCH B1;T;B3
WORKBENCH> CLOCK
CLOCK> R
CLOCK> Q
WORKBENCH> Q
B3>
```

Examples show navigation, not free-storage declarations. CONFIG/OPAQUE remain
matching standalone N-F RAM tools: Q to REC> and use the Python console's
existing loading workflow. The planned merged menu does not make those old
private utility entry points compatible. The accepted
[FLASH/MAINT design](MON_BOARD_SERVICES_PLAN.md) records the next increment.
