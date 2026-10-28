# STR8N-F

Boot user images in **B0, B1, B2 or B3** on the WDC banked 65C02/65C816 board. STR8N-F puts the bootstrap, bank selection and RAM recovery loader in the single **B3:$F000–$FFFF** sector. User images supply their own application code.

**v0.1.0-preview.1 is a source preview.** The 4096-byte F image retains the existing b15/PR04 firmware identity and bytes. This repository makes that bootstrap and its matching RAM tools independently buildable; it does not yet provide a general factory-WDC migration or wear-history import utility. See [release status](docs/RELEASE_STATUS.md) before installing.

| Component | Purpose |
|---|---|
| `STR8N-F-BOOT-4096.bin` | One 4096-byte ROM sector at B3:F000; reset, boot choices, recovery and RAM services |
| `STR8N-F-CONFIG-RAM.bin` | Inspect settings/wear; enable bank entries and save a default; blank-only journal initialization |
| `STR8N-F-OPAQUE-RAM.bin` | Read or replace an allowed 4096-byte opaque sector with preimage and payload CRC checks |
| `STR8N-F-DEMO-RAM.bin` | Exercise F console, CPU/capability queries and RAM execution |

The three RAM BINs load at **$0200** through F's raw `L` command. They are not flash images. The F BIN is not a RAM program. Built files and SHA-256 values are in [firmware/manifest.json](firmware/manifest.json).

Start with the [operator guide](docs/OPERATOR_GUIDE.md), [installation boundaries](docs/INSTALLATION.md) and [opaque transfer protocol](docs/OPAQUE_PROTOCOL.md). The [build guide](docs/BUILD.md) covers rebuilding from this repository alone.

For an already provisioned compatible board, the boot sequence is:

1. Install and verify the intended user image in its bank.
2. Load CONFIG; inspect with `B`, `C` and `W`.
3. `B 1 9000` enables B1 with entry $9000. `C 1` saves B1 as the default. Each command saves immediately.
4. `Q` restarts through F. `S` selects recovery at the boot menu; `0`–`3` select an enabled bank.

These addresses are examples, not an image format requirement. A B1 selector containing BASIC/Forth/reserved slots is a user image with its own entry point and internal layout. This preview does not bundle those applications.

Run the offline checks with Python 3.11 or newer:

```text
python tools/verify.py
python tests/test_boot_and_opaque.py --build firmware --out build/cpu-check
```

The tests use synthetic banks and both CPU models. They do not open serial ports. The [qualification record](validation/qualification.json) states their limits. Original project provenance is recorded in [ORIGIN.json](ORIGIN.json); MIT and vendored BSD notices are retained.
