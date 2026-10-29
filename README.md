# STR8N-F — BASE1 / PR05

**MON A/B development branch:** [five-checkpoint plan](docs/MON_AB_PLAN.md)
and [checkpoint 1 compatibility findings](docs/MON_AB_COMPATIBILITY_REVIEW.md).
Mona generation 1 A/B and RAM candidates were built once and passed the
[scoped 2512 trial](docs/MON_AB_2512_ACCEPTANCE.md). Original images and owner RAM
are restored. [Generation 2 adds an explicit RTCC reader](docs/MON_AB_RTCC_ADAPTER.md)
whose [RAM trial passed on 2512](docs/MON_AB_G2_RAM_ACCEPTANCE.md); g2 A/B ROM
startup remains untested. A/B remain identical at the owner's
request. Mona remains unreleased and N-F v0.3.0 remains the frozen foundation.

> Give me 4KB, I can give you 4 boards.

*With ~32KB RAM shared by the selected bank environment.*

One 4096-byte bootstrap/recovery component opens four selectable flash banks
for your own images and environments. Four bank environments share that RAM;
hardware qualification is listed below. The raw-L application range is
$0200-$64FF; preservation tools escrow $0200-$66FF and owner ZP $00-$DF.

**STR8N-F 0.3.0 is the scoped 4KB foundation release.** F remains
**STR8N-F 0.3.0 g00000001 / BASE1 / PR05**, source and binary frozen.
The reviewed 2512 cases and the [2609 extracted-ZIP existing-SNBT upgrade](docs/2609_RC1_ZIP_UPGRADE_ACCEPTANCE.md)
passed. The final package retains the same runtime files and corrects rc1
documentation; it has no additional live trial. Packaged WDC/programmer-F
provisioning routes remain untested. See [release notes](docs/RELEASE_NOTES.md),
[rc1 findings](docs/RC1_KNOWN_ISSUES.md),
[closeout status](docs/RELEASE_STATUS.md) and [ZIP workflow](docs/RELEASE_WORKFLOW.md).

## Included

- Exact 4096-byte programmer F BIN, also supplied beside the ZIP.
- Matching CONFIG, OPAQUE, DEMO, MAP and READBACK RAM BINs.
- **Python Serial Console 0.1.0**, function-key transfers, pinned pyserial
  requirement and [terminal guide](docs/SERIAL_CONSOLE.md).
- Verbose WDC RAM migration, programmer-installed-F C/D provisioning and
  known-b15 existing-journal F upgrade tools, with prebuilt engines.
- SHA-256 manifest/checker, installation guides and scoped hardware receipts.

No assembler is needed to use the kit. Owner/vendor firmware, captured RAM,
per-board plans and private qualification packets are not supplied.

## Start the Python terminal

Install Python 3.11+ with Tk, extract the complete operator ZIP, then run:

```text
python -m pip install -r requirements-console.txt
python tools/verify_release_kit.py .
python tools/nf_console.py
```

Select the port and press **F10** to connect. At an observed REC>, **F2**
chooses a RAM BIN and **F4** loads it; **F3** sends at an observed SEND BIN.
**F5-F8** load MAP, CONFIG, OPAQUE and DEMO. **F9** controls a private log;
**F12/Ctrl-C** cancels before the first BIN byte. Every shortcut has a button.
The console does not connect or migrate automatically. Disconnect it before
a migration CLI owns the same port. See [quick start](docs/QUICK_START.md).

Raw L runs received RAM after input idle, without a length/CRC guarantee.
Loading borrows owner RAM; use the migration escrow/restoration procedure
when preservation is required.

## Boot and storage

Startup prints:

```text
STR8N-F 0.3.0 g00000001
BASE1 / PR05
```

F then offers its chooser and recovery. The running image supplies its own
OS identity and EDU, RTC, SRAM or other service status. **Mona** is the
name chosen for a future optional monitor/launcher; [it is planned](docs/MONA.md),
with no Mona binary or expanded F ABI in this release.

| Flash region | BASE1 role |
| --- | --- |
| B0/B1/B2:8-F | Owner opaque images |
| B3:8/9/A/B/E | Owner opaque images; A/B monitors are optional occupants |
| B3:C/D | Persistent boot settings and erase-attempt journal |
| B3:F | Exactly 4096 bytes of bootstrap/recovery |

Opaque capacity is **116 KiB**. F needs no MON, EDU, provider or SPI SRAM.
Available addresses may already hold owner data. CONFIG saves enable/entry/
default; OPAQUE installs admitted image sectors. Installing and choosing a
default boot are separate operations.

The programmer file is firmware/payload/STR8N-F-BOOT-4096.bin for B3:F only,
not a whole-chip image. F alone does not convert occupied C/D. Choose the
route in [installation](docs/INSTALLATION.md):

| Starting state | Route |
| --- | --- |
| WDCMONv2, no recognized N-F journal | [WDC migration](migration-host/README.md) |
| Frozen BASE1 F already installed | [Live C/D provisioning](docs/LIVE_CD_PROVISIONING.md) |
| Supported b15 F and valid SNBT | [Journal-preserving F upgrade](docs/JOURNAL_F_UPGRADE.md) |

Damaged/conflicting or unsupported history is refused. Prior lifetime remains
unknown; tracked evidence can carry forward. Zeros do not prove unused flash.
Normal recovery assumes F stays golden. No hardware action or power-cut
test is part of this release packaging.

## Qualification boundary

2512 evidence covers BASE1 reset/recovery, native console keys/dialogs, Ctrl-C
and BIN loading, CONFIG/opaque write-and-boot, reviewed chip-idle C/D recovery,
WDC migration and programmer-F provisioning. The extracted rc1 existing-SNBT
upgrade and terminal core checks also passed on 2609/65C816 emulation/FT245.
Other CPU modes, adapters, occupied
layouts and electrical interruptions remain unqualified. 2205 stays excluded.
The explicit --allow-unqualified switch remains for those broader limits.

F generation, toolkit version, console version and journal sequence are
independent. [F_FREEZE.json](F_FREEZE.json) and the
[identity contract](docs/F_IDENTITY.md) bind F. Its SHA-256 is
`8f4d35ac66730daa773515980983fcf442be3b1bdf1e523d3752ec3615657cc1`.
Packaging copied verified existing firmware without rebuilding, simulation,
board access or publication. The later 2609 upgrade is recorded separately;
the tested rc1 ZIP remains immutable.
