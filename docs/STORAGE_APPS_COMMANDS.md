# PROGRAM storage and APPS development checkpoint

These optional services depend on frozen STR8N-F v0.3.0 BASE1/PR05 and MON/g8.
The new WB2/g5, PROGRAM provider and services/g3 are separate components.
Their2512 RAM acceptance is recorded separately from installation. Until the
expanded B2:8/9/A and E installation is approved and verified, the installed
g4 workbench does not gain these commands. Published foundation ZIPs are unchanged.

## PROGRAM and flash records

After installation, `MAINT LOAD` deliberately reloads the current flash tools,
including their companion provider, even when an older compatible workbench
is cached. Ordinary `MAINT` may keep a valid old cache. Loading borrows RAM
4800-66FF; applications use0200-47FF. Provider code uses6B00-77FF and scratch
6700-69FF. F and monitor A/B are not replaced by this checkpoint.

```text
MAINT LOAD
EDU ON
SRAM
T P
S P AUTO 3000 3016 HELLO
YES
R P HELLO L
R P HELLO
Q
```

`EDU ON` selects the explicit Rev D profile; it is not presence proof. Busy
pins/flags are refused. `SRAM PREP` is an explicit acknowledgement of disabled
CB flags, with no SPI clocks. `SRAM` reports the admitted primary boundary;
page00 denotes10000. No command formats the chip, changes its mode register,
resizes PROGRAM or silently switches to WORKSPACE.

`S P AUTO start end name` stores the inclusive CPU-RAM source range in a free
PROGRAM page run, shows the chosen destination and requires YES. NO leaves
storage unchanged. Its saved load/entry is the source start. An explicit
page-aligned destination replaces AUTO, for example `S P A000 3000 3016 HELLO`.
AUTO chooses an address within the selected backend, never the backend itself.
Payload CRC is verified before committing the directory record last. Names
have1-16 uppercase letters, digits, hyphens or underscores. Same-name Store
creates a higher-sequence version in another free slot; it does not overwrite
or reclaim older records. Full/corrupt geometry is refused.

`R P name L` restores the latest live PROGRAM version without running it.
`R P name` restores and runs its saved entry. Payload CRC is checked before
any application copy and again while copying. All destinations must fit the
current caller's available application RAM. A retained legacy CLOCK image can
be listed yet correctly refused because it exceeds47FF or uses old providers.

| Command | Discovery/selection |
| --- | --- |
| `T` | Selected flash bank, then PROGRAM when EDU is enabled |
| `T 0` through `T 3` | Explicit flash bank only |
| `T P` | Committed PROGRAM records, with slot/kind/sequence |
| `R name [L]` | Selected flash bank plus admitted PROGRAM; ambiguity is refused |
| `R bank name [L]` | Explicit flash bank |
| `R P name [L]` | Explicit PROGRAM backend |
| `R bank address [L]` | Existing explicit SR01 flash-record address form |

An implicit name collision requires bank/P/address selection; it never picks
the first match. Flash SR01 has no payload checksum. Its existing Store/AUTO
requires an explicit AREA and fresh FF bytes, and never erases. PROGRAM's
native SP/01 format includes payload and directory CRCs. These are distinct
formats; neither is a boot/wear journal or a WORKSPACE message log.

2512's SS1 primary layout has PROGRAM0800-0FFFF. The approved cleanup retires
only superseded slot7 at0023F, freeing44 pages and one slot. The retained CLK
at06000 and CLOCK at03400 are different builds. Current free PROGRAM space is
39936 bytes across156 pages, before subsequent owner stores. No payload move
or format was performed. SS2 admission is implemented; this live write trial
qualifies the actual SS1/64K PROGRAM layout on2512.

## APPS and named launch

```text
APPS
APP APPDEMO
Q
```

APPS lists native CLOCK/MAINT/FLASH and CRC-admitted AP/02 owner images. APP
performs deliberate named launch; the example's Q uses the public HOLD call
to return to MON B. APPDEMO is a temporary qualification fixture, restored to
the original B0 image afterward. Its source is `apps/examples/appdemo.asm`.

AP/02 images start at a4K sector boundary in B0/B1/B2 or B3:8/9. The32-byte
header declares PR05, total image length, entry, CPU, public-ABI-only use and
a zero-padded name of at most11 characters. Header and body CRCs must match;
the entry must lie inside the admitted body, and bounds must avoid protected
regions. Duplicate admitted names are refused. See `tools/build_app_example.py`
for the exact header encoding. Header recognition in M1 is inventory, while
APPS performs execution admission. Retained legacy AP/01/private-provider
images and arbitrary PROGRAM records are not advertised as compatible apps.

Immediate or periodic current-time collection now has a separate
[host collector](TIME_SAMPLES.md), using native TIME without storage writes.
On-board WORKSPACE logging, full CLOCK administration, the4K FLASH editor,
source/ASM and DEBUG remain separate work. This checkpoint stops after APPS.
