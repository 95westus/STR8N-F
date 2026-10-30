# Checkpoint 1: g0034 versus frozen BASE1

Read-only source/artifact review, October 29, 2026. **Decision: g0034 A/B
cannot be used unchanged under N-F 0.3.0.** F's existing header guard rejects
them; bypassing that guard would expose further private-call and RAM conflicts.
Start a shared BASE1 monitor core and selectively port useful source logic.
This is an initial compatibility inventory, not a new hardware or CPU-model pass.

See the [five-checkpoint plan](MON_AB_PLAN.md), the
[machine-readable inventory](../monitors/review/g0034-base1-compatibility.json)
and [review tool](../tools/review_mon_ab_dependencies.py).

## Reference identity and evidence

The reference is STR8-N **2.0rc1 g0034**, generation `00000034` (52 decimal),
`rc1-r10p2-current`. It is distinct from the b15/PR05 prototype monitor template
retained in this N-F source tree. That template contains disabled provider hooks
and private calls; it must not be labelled as the original g0034 source.

The retained parent-project fixture is `tests/baselines/rc1-r10p2-current.json`;
its selected saved build is `BUILD/current-g0034-selected`. No build was run.
The two 4096-byte images match the fixture exactly:

| Slot | SHA-256 | Linked body |
| --- | --- | --- |
| A | `dead579f351dd09e77c8160517cf2f5537604329c8e3598fff3ac2c6ebc9f674` | A080-AE06, 3463 bytes |
| B | `cecce80957b3a7e7d0738afc325cc22c18bf7fd761c121c7b14e65be3c92a29e` | B080-BE06, 3463 bytes |

Saved linked S-record bytes match the corresponding slot bytes; saved map files
identify symbols and body limits. Recursive source/include hashes are recorded
in the inventory. An older saved build was excluded when its generation/hash
proved to be g0032 rather than g0034. Mutable `src/current` is not used as the
authoritative reference for this report. No owner flash/RAM capture is published.

## Boot/header compatibility

Both g0034 images have the expected MI/01 slot/bank/ABI fields, SN signature,
A084/B084 reset entry, A087/B087 prompt entry, payload bounds and matching CRC.
Their private contract is the little-endian value **52313032**, stored as
`32 30 31 52` (ASCII `201R`). BASE1 requires bytes `50 52 30 35` (`PR05`) at
header offsets 14-17 hex. That is the observed header rejection.

The [frozen loader](../src/core/str8n-v2-boot.asm) checks those bytes before
launch. Keeping the standard image shape does not make internal dependencies
compatible. New images must generate their own appropriate entry/reset behavior,
header, identity, CRC and PR05 binding; do not merely replace four header bytes.

## ABI and private-call inventory

The public RAM descriptor remains `RA`, format 1, 13 calls at **7E60**, with
entry slots **7E64-7E88**. The old and new public header addresses agree.
Calls require IRQ disabled and decimal clear; 65C816 calls require E=1,
D=0, DBR=0, PBR=0. Native interrupt vectors do not imply native-mode service calls.
ROM facade calls require B3 visible; the public RAM facade is bank independent.

The g0034 monitor itself calls private worker/helper targets directly rather
than the public RAM jump slots. Across A and B, the textual inventory has
168 private RAM call/jump sites, 20 private F sites, 10 E-provider sites,
6 indirect sites and 438 own-image sites. These are source-site counts across
both variants, not runtime frequencies. DB-encoded gateways were reviewed
separately; the tool does not disassemble arbitrary code or execute instructions.

| Dependency | g0034 | BASE1 | Porting action |
| --- | --- | --- | --- |
| Console PUTC implementation | 7ACB | 7B13 | Use public RAM PUTC at 7E6D |
| GETC implementation | 7A3E | 7A21 | Use public RAM GETC at 7E70 |
| RX_RESET implementation | 79E5 | 798F | Use public RAM RX_RESET at 7E79 |
| CRC init / byte helpers | FAB4 / FABD | F8D4 / F8DD | Keep CRC in the monitor/tool or use an explicitly exact-F-bound private adapter |
| Private worker end | 7B81 exclusive | 7BE8 exclusive | Reallocate old debugger/gateway code; do not write this worker |
| Public parser calls | No public line/word/byte parser contract | Prototype private slots exist | Give Mona its own shared line/token parser; do not advertise prototype slots as public ABI |
| C/W/P/F/I/U journal and update paths | Original private F/worker semantics | Journal operations dispatch through JE_HANDLER; reset selects no-service | Keep original writers out of the minimal core; design any later adapter separately |
| Console state at 7D02 | USB/ACIA enumeration | USB/ACIA enable mask, including both | Use console facade; do not transplant direct state assignments |

The source inventory records 32 differing private worker symbols. Some early
worker addresses happen to agree; that does not establish a compatible worker
contract. BASE1's matching private CONFIG/OPAQUE engine is not part of the
legacy g0034 image simply because the F dispatch slots have familiar addresses.

## Entry shims and RAM ownership

The g0034 header's A048/B048 entry code copies **15 bytes to 7B81-7B8F**,
sets the BRK handler pointer at 7E02/7E03, clears 7BFC-7BFF debugger state and
then enters the linked monitor. The copy-loop bytes were checked directly in
both saved sectors. BASE1's worker occupies **7800-7BE7**: this old entry copy
would overwrite it if the header check were bypassed.

The optional UX utility provider also places its gateway at **7B90-7BD3**;
its saved gateway map gives G_END=7BD4. That placement conflicts with the same
BASE1 worker. The g0034 monitor's separate 96-byte batch gateway at **7C90-7CEF**
contains fixed private targets and must be treated independently.

| RAM / I/O | Existing role and consequence for the new contract |
| --- | --- |
| 0000-00DF | Owner ZP; no implicit monitor scratch allocation |
| 00E0-00FF, 0100-01FF | System scratch and runtime stack; define clobbers and interrupt assumptions |
| 0200-66FF | Owner application/escrow range; any monitor borrow must be declared |
| 6500-66FF | Optional g0034 RTC/I2C service code/state; it can reduce usable application RAM to 64FF |
| 6700-67FF | BASE1 journal frame scratch |
| 6800 onward | READBACK service while that RAM tool is active; not proof of permanently free monitor RAM |
| 7800-7BE7 | Frozen BASE1 worker; no g0034 debugger or XIP gateway copies here |
| 7C00-7C28 | Shared line buffer; 7C29-7C2F are BASE1 dual-console state |
| 7C40-7C6F and nearby scratch | CONFIG/journal/boot dispatch state; define lifetimes before reuse |
| 7C80-7C8F | Shared data buffer |
| 7Dxx | Config, queue, boot/journal, provider and session state; old absolute offsets require review |
| 7E00/7E10 groups, 7E20 onward | Handler pointers, vectors and public RAM facade; preserve installed services |
| 7EE4-7EF4, 7DF9-7DFC | Legacy utility/batch/return state; not a general-purpose stable ABI |
| 7Fxx | Memory-mapped I/O; reads/writes can have side effects |

This is an ownership inventory, not the new Mona allocation. Checkpoint 2
will choose that allocation and explicit ownership transitions. The minimal
monitor should not silently consume owner RAM or initialize optional hardware.

## Optional providers and rich status

| Legacy provider | Guard / use | Decision for minimal Mona |
| --- | --- | --- |
| B3:E000-EFFF, `NA`,01,3F | CRC-admitted extension; E008 command dispatch, E00B legacy S/R/T, E00E map, E014 service init | Not required; its monitor and private-F dependencies need a separate port |
| B3:8000 RTC component, `RC`,3,7 | Optional service kernel validates the sector and installs 512 bytes at 6500; publishes SV state | Not required; no automatic RTC/I2C service installation |
| B3:8900 banner, `BT`,5,3 | Publishes 7D0F banner pointer; associated EF03 time-command hook | Optional status module later, with explicit provider binding |
| B3:9000 SPI/journal component | Banner/provider validation and optional command routing | Distinct legacy optional subsystem; not N-F's C/D boot/wear journal |
| B2:8000-D7FF, `UX`,3,42 | Monitor checks CRC; batch gateway routes through D0EA and utility gateway at 7B90 | Not required; existing gateway conflicts with BASE1 worker |
| B2:D800-E1FF / E200-EBFF / F region | Full-system status, battery, local-display/VERSION assets | Rich status is not contained in the A/B monitor alone; keep separately optional |
| B1 source/ASM and debugger occupants | Full-system tools reached through extensions/utilities | Not needed for the first independent monitor |

Header/CRC validity is only admission, not a promise that an optional provider
is compatible with BASE1, read-only, or safe to initialize. Legacy providers
embed old worker/kernel targets too. Their detailed device protocols and write
paths are outside this first inventory. Do not copy the full-system sector map
into N-F's owner space by assumption. In particular, EDU/RTC/SRAM status should
report unavailable when an optional module/hardware is absent.

The simple public BOARD_QUERY supplies CPU/console flags; it is not the richer
per-board identity, RTC, battery or SRAM service. That distinction lets the
initial monitor run without those optional assets.

## Reuse decisions and checkpoint 2 inputs

Reuse selected parser, safe dump formatting and command-table ideas as source
after removing their private aliases and old memory assumptions. New common
modules should provide console adaptation, bounded parsing, image identity,
bank-safe inspection, optional-service admission and explicit application/
recovery transitions. Compile common source into independent A/B images first.

Public RAM RESET returns through F's saved boot policy; it can relaunch the
same image. HOLD is not a generic recovery command: BASE1 uses BOOT_ACTIVE
and launches the active image's reset entry. A deterministic Q-to-REC path
must be designed against the pinned foundation in checkpoint 2; no new F
entry point is being added by this review.

The initial monitor will not inherit legacy flash/config/update commands,
debugger hooks, automatic application startup or blanket optional-provider
probing. Those are individual later features. This preserves the small,
independent common core without changing frozen F.

## Reproducing this file inventory

From the N-F source directory, with an explicitly supplied saved g0034 build
and matching fixture:

```text
python tools/review_mon_ab_dependencies.py --g0034-build PATH-TO-SAVED-BUILD --g0034-fixture PATH-TO-rc1-r10p2-current.json --report NEW-REPORT.json
```

The tool reads files and emits a new report; it never imports a serial library,
opens a port, invokes an assembler, rebuilds firmware or executes target code.
It preserves existing reports. The retained original monitor/board images stay
outside this repository; only project-artifact hashes and source/call evidence
are recorded here. No boards, images, boot settings, history or owner RAM changed.
