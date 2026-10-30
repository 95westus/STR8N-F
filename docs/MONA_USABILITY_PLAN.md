# MON A/B: usable monitor target

Direction clarified 2026-10-29: MON A/B should provide the familiar practical monitor
experience, including Dump/Modify and useful startup status. A and B remain
identical. The small g1/g2 cores are implementation checkpoints, not the final
feature target. The next increment prioritizes everyday monitor commands over
adding more isolated status fields.

## Current acceptance: full 2.0b35 parity

The [full parity checklist](MON_B35_PARITY.md) is the current completion gate.
It explicitly requires BATCH, AUTO T/S/R across flash and SSRAM PROGRAM, APPS,
source/ASM/DEBUG and every baseline workflow. The older incremental sections
below record delivery history; they do not reduce that scope. The Mona name
is retired; existing built artifacts retain their historical names.

## Full workbench is the completion target

The owner clarified that R/T/S **Restore/Table/Store**, apps, MAINT/CONFIG/OPAQUE
and the source/assembler/debugger environment remain part of the intended
product. G4's monitor commands do not replace or complete that environment.
Larger modules are an implementation method; calling them optional does not
remove these capabilities from the full workbench's acceptance criteria.

The 2512 g4 saved readbacks confirm retained component signatures and exact
preservation outside the replaced A/B images and appended C/D records:

| Component | Retained evidence / present access | Remaining work |
| --- | --- | --- |
| Restore/Table/Store records | B1 SR/01 records retained | Port R/T/S command dispatch and checked record storage/loading |
| Source editor/store | B1:9 NS/01/01 component retained | Port its version-paired assembler/storage interfaces |
| Assembler | B1:E AP/01/01 application and continuation in F retained | Review BASE1 host calls, entry/return and source/output ownership; integrate ASM |
| Debugger | B1:A DG/01/01 component retained | Port its private bindings/context/traps; integrate DEBUG |
| Apps and maintenance services | B2 UX utilities and B3:8/9/E service/extension images retained | Compatible discovery, dispatch and return; no blind legacy entry |
| CONFIG/OPAQUE/MAP | Matching host RAM BINs remain available from REC> | Provide coherent MON A/B launch/menu access and preservation rules |
| EDU / SPI SRAM | PROGRAM/WORKSPACE formats and source retained; g4 install issued no SPI writes | WB1 builds a guarded read-only SS2 adapter; qualify, then reconnect source/program storage and separate WORKSPACE messages |

These are retention/source-inventory findings, not new execution qualification
of old binaries under BASE1. The old A/B originals are backed up on the host.
Only the monitor sectors were replaced; the full old command dispatcher was
not automatically ported with the preserved services.

The completion workflow is **edit source -> assemble -> Store -> Table ->
Restore -> run -> debug -> return to MON A/B**, with apps and maintenance/config
accessible from the same environment. Keep both A/B interfaces alike and F
frozen. Next prioritize the command/module bridge, R/T/S and app/maintenance
access, then complete source/ASM and DBG integration. Further standalone D/M
polish does not take priority over restoring this workflow.

## Size and layer boundaries

Only STR8N-F must remain the frozen **4096-byte foundation**. Its A/B admission
contract also bounds each entry image to a 4096-byte sector with a 3968-byte
payload ceiling. That is an entry-image constraint, not a requirement to fit
every monitor, debugger and device service into that sector.

G2 currently uses 3704 payload bytes, leaving 264. Do not turn that remainder
into the product specification. Keep basic inspection/editing/recovery usable
in each slot, and admit larger services as separately checked optional modules.
The first layout review must decide which code stays in the slot and where
additional code/state can live. Moving the RTCC implementation out of the core
is an option if needed; g2's tested bytes remain retained as a checkpoint.

Optional modules need an explicit descriptor, compatibility/version/CRC checks,
declared flash and RAM ownership, bank-safe calls and a defined return path.
Missing or incompatible modules must leave basic D/M/G/Q operation available.
No B0/B1 user space, B2 area or B3:8/9/E sector is automatically reserved.
Choose any extra placement from an actual board inventory and reviewed install
manifest. F, C/D and existing owner images remain protected.

## Familiar command set

This table is a target and porting inventory, not a list of already working
MON A/B commands. G2 hardware evidence covers its RAM candidate only; g1 has the
separate A/B startup trial.

| User command | Intended behavior | Current MON A/B state / next action |
| --- | --- | --- |
| `?` | Concise grouped help; advertise installed commands and identify unavailable modules | Basic help exists; expand as commands land |
| `B0`-`B3` | Select the data/inspection bank; no boot-policy save | Existing parser accepts adjacent or spaced bank digit; retain both forms |
| `D addr [end]` | Useful hex dump, ASCII column, continuation and cancel/paging | G4 adds hex/ASCII and ranges beyond 256 bytes; paging/continuation remain planned |
| `M addr byte...` | Modify ordinary application RAM, with complete preflight and displayed readback | G4 implements inline 1-8-byte owner ZP/RAM edits; interactive editing remains planned |
| `!M addr byte...` | Explicit force to ZP/stack/RAM/I/O and allowed flash, no erase | G4 implements it; owner chose B3:C/D/F protection; dangerous active-system edits are not qualification tests |
| `G addr` | Explicit application entry with a documented monitor-return convention | Basic admitted one-way launch exists; owner-application return still needs qualification |
| `L` | Receive a host RAM BIN using the matching console workflow | Available in REC>, not yet integrated at the MON A/B prompt |
| `TIME` | Fresh bounded RTCC read/display through an admitted device profile | G4 uses TIME; g2's temporary T alias is removed and T is reserved for records |
| `V` | Refresh the monitor's overall status display | Exists; g2 RTCC is a labelled retained sample, not an automatic new read |
| `M`, `M1`, `M2`, `M3` | Summary/grid, ranges/reservations, tracked wear view | Existing RAM MAP tool is separate; map forms need a monitor adapter |
| `W` | Detailed tracked wear counts with the shared caveat | G2 only displays a maximum; port the full read-only view |
| `F addr byte...`, `I start end` | Explicit journaled flash edit/erase with confirmation and protected-region checks | Matching OPAQUE exists separately; do not copy the old private flash worker calls |
| `C ...`, `P A\|B` | Inspect/save boot policy and choose the saved monitor default | Matching CONFIG exists separately; integrate through its reviewed journal path |
| `J0`-`J3` | Familiar explicit bank boot/recovery navigation | Port only after documenting configured-entry versus reset-vector behavior under BASE1 |
| `U A\|B` | Replace a monitor through an admitted, backed-up, journaled update | Separate installation tools exist; no MON A/B update command yet |
| `S ...`, `R ...`, `T ...` | Named flash-record save/load/list, as in the familiar monitor | Legacy record/provider dependency review and port required; these are not boot/wear journal messages |
| `MAINT`, `SRAM`, `WORK`, `EDU` | Useful hardware/storage pages and explicit configuration | Legacy providers are not compatible merely because their signatures exist; port as optional modules |
| `BATCH ...` | Bounded complete-command sequences with ESC cancellation | Required parity gate: legacy bounded queue, ESC, failure stop and checked command-result/confirmation behavior |
| `DEBUG` | Enter disassembly/register/breakpoint/step tools | Planned monitor module; details below |
| `ASM` / source editor | Edit, assemble, retain/restore source and run generated output | Legacy B1 components retained; compatible integration is a required full-workbench deliverable |
| `Q` | Deliberately return to REC>, regardless of the saved default | Implemented; retain |

Do not reuse top-level `R`, `S`, `C` or `B` for conventional debugger shortcuts:
they already have record/config/bank meanings here. The debugger can use such
letters inside a distinct `DEBUG>` prompt. `TIME` is the intended clock name;
`T` must be available for the familiar record-list command. The temporary g2
clock alias was not a released compatibility promise; g4 reserves bare T.

`M` needs deliberate disambiguation: bare M and a sole selector 1/2/3 are map
requests; an address followed by bytes is an edit. Never execute a valid prefix
of malformed or overlong input. Keep unavailable map selectors distinguishable
from a rejected RAM-edit address.

## First implementation increment: D/M/G/L/Q

1. Settle the core/module size budget before building. A/B share the same source
   and commands. No speculative reproduction build or CPU model is required.
2. Add inline `M addr byte...`, initially 1-8 bytes. Parse every byte and validate
   the entire target span before its first write. Default editable ranges are
   owner ZP `$0000-$00DF` and owner RAM `$0200-$66FF`, minus any explicitly
   installed provider reservation. Reject the stack, system ZP, monitor/service
   state, worker, vectors, I/O and ROM. RAM is common across selected flash banks.
3. Stage edits in monitor-owned RAM, honor cancellation before committing the
   checked unit, read back, and display the resulting address/bytes. This is an
   intentional user edit; startup/inspection still preserve owner RAM. Do not
   claim that multiple writes are atomic against arbitrary application NMIs.
   A later interactive M session can offer current value/new value/next/quit.
4. Improve D with hex/ASCII, useful larger ranges and continuation/paging, while
   rejecting an entire range that intersects I/O and preserving Ctrl-C/ESC.
5. Integrate host RAM loading and the application return path. Raw F L retains
   its existing idle-terminated, unframed transfer limits; do not invent CRC or
   length guarantees. A RAM-resident smoke monitor must not overwrite itself
   accidentally when testing this path.
6. Prepare a new exact-hash RAM candidate and preservation trial. A new trial
   identifies an explicit reversible RAM/ZP target and restores it. No board
   action or flash budget is authorized by this design document.

## Rich startup display

The user's example is the target level of usability. Keep MON A/B's own name,
version and generation, with the frozen N-F identity separate. Do not print the
old STR8-N 2.0b35 identity on a new MON A/B implementation.

The exact old pre-monitor A/B VALID/chooser transcript is not in frozen BASE1.
F's chooser remains unchanged. After entry, MON A/B can report validated A/B
headers/generations and the saved default, followed by the richer status.
An additional pre-entry selector would be a separate boot image, not an excuse
to edit golden F or silently add a second countdown.

Illustrative desired monitor portion, **planned, not captured output**:

```text
STR8-N <version> g<generation> / MON A / B3 / 65C02
Foundation: STR8N-F 0.3.0 g00000001 / BASE1 / PR05
ABI 65C02 | 816E | 816N-VEC
MONITOR A gen <validated generation> VALID
MONITOR B gen <validated generation> VALID default

Board: <configured board ID>
RAM <actual declared application range>
EDU ON
SSRAM: PROGRAM payload <validated bytes>
SSRAM: WORKSPACE <validated bytes>
RTCC: <weekday/date/time> (<configured offset>)
FLASH: journal OK; max tracked <count> (<bank:sector>)*
Battery: within age policy*
* Battery health/prior flash wear unverified; counts are tracked erase attempts.

B3> ?
<implemented monitor commands and available modules>
```

The familiar bank prompt should show the selected data bank; active monitor
A/B stays visible in the banner/status. No physical board ID is inferred from
CPU/console flags. A board/profile record supplies ID, EDU enable policy, wiring,
time convention/offset and any battery installation/service date. Its storage
and import need a separate design; do not put monitor metadata into C/D or
reuse legacy RAM flags as if BASE1 initialized them.

Startup collection is bounded and profile-driven. When a verified profile
enables the matching EDU wiring, an RTCC adapter may read automatically; absent
hardware must return promptly. G2 has only an explicit T read and no such profile
or automatic collection yet. An RTCC response alone does not prove EDU mode or
validate an SRAM layout. Read-only SSRAM layout checks must not format, repair
or write the PROGRAM or WORKSPACE areas. Time zone/DST cannot be guessed from
the RTCC. The RAM line must reflect actual reservations; the guaranteed raw-L
application range `$0200-$64FF` and owner escrow `$0200-$66FF` are distinct.

Battery policy needs a valid stored date and usable clock; its result is not a
voltage/health measurement. Flash journal CRC/counter validity is not a physical
wear or endurance test. Use the single `*` caveat and `--` where policy/provider
data is absent. Avoid unconditional "wear check OK" or a fabricated age status.

## Debugger at the monitor layer

Yes: a usable monitor should be the way into debugging. Make the implementation
an optional, compatible monitor module, available from both identical slots.
Start with disassembly and register display/edit, then RAM BRK/breakpoints and
single-step/continue. Inspect registers captured from a real trap or explicit
debug launch; normal startup does not contain an interrupted program context.

BASE1 already exposes RAM interrupt-handler pointers, including emulation BRK
at `$7E02`. This permits a separately installed handler without rebuilding F.
It does not make the old debugger binary compatible. Source review found the
old debugger using owner ZP `$D0-$D9`, `$7000-$73FF` context/stack/ZP/trampoline
storage, private session fields at `$7BFC-$7BFF` and a registry at `$7C30`, plus
generated legacy flash/monitor targets. Its A/B entry shim also conflicts with
the BASE1 worker, as the earlier compatibility review records.

Before porting, assign a new explicit workspace, review bank-safe execution
and trap entry, preserve original hook pointers, and define enable/disable and
exit restoration. Keep normal MON A/B entry separate from a debugger prompt that
must retain an application's captured stack/register state. No old gateway or
shim may overwrite `$7800-$7BE7`.

Qualify 65C02 first, then 65C816 emulation. Native debugging needs explicit
16-bit register/stack/direct-page/bank/width handling; the displayed 816N-VEC
capability alone is not debugger qualification. RAM breakpoints deliberately
change bytes and must restore them. Do not implement flash breakpoints by
silently erasing/programming owner sectors. Disassembly may inspect ROM while
such execution/step paths remain unsupported.

## Delivery order and current boundary

1. Practical common core: retain g4 D/M/G/Q and add the load/module bridge.
2. Reconnect Restore/Table/Store, apps and maintenance/config/opaque access,
   preserving the familiar TIME versus record-T distinction.
3. Integrate source editor/ASM and the complete edit/assemble/store/restore/run
   workflow with declared source/output/workspace ownership.
4. Integrate DEBUG: disassembly/registers, then reviewed RAM trap/step/continue
   and reliable return to MON A/B.
5. Complete rich startup, maps/wear views and storage pages through the
   same admitted modules. Preserve all of these in the full-workbench target.

The order can overlap source reviews, but write-capable features get separate
preservation scopes. Existing g1/g2 evidence stays valid for its exact bytes;
the full expanded monitor remains unfinished. Subsequent g4 work implements
Dump/Modify and force; see the [command manual](MONA_COMMANDS.md) and installation
receipt. This original planning checkpoint itself made no build or board access.
Published N-F downloads, 2205 and all other boards remain untouched.

## G5 / WB1 build checkpoint (2026-10-29)

[WB1](MONA_WORKBENCH_WB1.md) has built RAM candidates for T/R, session EDU
control and read-only SRAM layout/capacity. G5 builds the shared load/module
bridge and protects admitted module and RAM-monitor reservations. **Not yet
live-qualified or installed:** 2512 still runs g4. Review the
[RAM-only scope](MON_AB_G5_WB1_RAM_SCOPE.md) before a new trial.

EDU/SRAM is required work: PROGRAM storage, source SAVE/LOAD and WORKSPACE.
Persistent messages/metadata use an explicitly admitted append-only WORKSPACE
allocation, outside PROGRAM and C/D. WB1 does not inspect/adopt existing
WORKSPACE allocations or write SRAM. Store, app/maintenance routing, source/
ASM and DEBUG remain open; this checkpoint does not close the full workbench.

## G5 / WB1 hardware closeout (2026-10-29)

[2512 acceptance](MON_AB_G5_2512_ACCEPTANCE.md) now closes the g5 RAM/ROM bridge
and WB1 g2 read-only checkpoint. Identical A/B images remain installed, B is
bound to generation5 and physical default boot passed. Fresh owner RAM/ZP was
restored and verified afterward, evicting the RAM module deliberately. Reload
WB1 through native L when needed. F and published downloads remain unchanged.
The earlier build-only section above is historical; it is not the current
qualification state. SS1 status is live-qualified; SS2/fallback remains a source
implementation without positive hardware evidence here. Store, app/maintenance
routing, source/ASM/DEBUG and WORKSPACE message allocation/writes remain open.

## G6 / Store checkpoint (2026-10-29)

G6 now uses the selected-bank B0>..B3> prompt and keeps slot identity in the
banner. WB1 g3 adds explicit AREA/S and passed a real Store/Table/Restore/run
cycle, including cancellation and duplicate handling. This closes the basic
flash-record Store port; no allocator or payload checksum is implied.
[Acceptance](MON_AB_G6_2512_ACCEPTANCE.md) records the unplanned native D rotation,
its exact-history restoration and retained extra wear count. Future zero-erase
plans must use the native capacity check before writing. Next: apps/maintenance
routing, source/ASM/DEBUG and WORKSPACE allocation before persistent messages.

## Current next increment

G6 closes manual flash Store only. BATCH, AUTO T/S/R for flash and SSRAM
PROGRAM, and APPS remain required and unimplemented. Follow the module/layout
then storage/apps/BATCH checkpoints in [full parity](MON_B35_PARITY.md).
The existing 43-byte slot and 30-byte WB1 tails are not a full-workbench budget.

## G7 / WB2 build checkpoint

[G7/WB2 g1](MON_AB_G7_WB2.md) has built the shared command result, a bounded
returning-command BATCH subset and a temporary 4000-66FF module reservation.
It is not execution-qualified or installed; g6 remains on 2512. The
[RAM-only scope](MON_AB_G7_WB2_RAM_SCOPE.md) preserves every flash byte, boot
setting and owner RAM/ZP. Automatic T/S/R for flash and SSRAM PROGRAM, APPS,
complete BATCH and full b35 source/output RAM behavior still require integration.

## G8 / board-services checkpoint

[G8 acceptance](MON_AB_G8_2512_ACCEPTANCE.md) is the current installed state on
2512. It restores M1/W directly, adds read-only CLOCK and loads WB2 from B2:8/9
for explicit tools. The module occupies 4800-66FF, leaving 0200-47FF for apps
while loaded. A/B retain identical commands and Bx> prompts. The earlier g7
build-only statement is historical. See the [services plan](MON_BOARD_SERVICES_PLAN.md)
for the next FLASH editor and merged MAINT/CONFIG work; AUTO storage, full apps,
source/ASM/DEBUG and WORKSPACE messages remain open.
