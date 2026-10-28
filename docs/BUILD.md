# Build and verify

The tree is self-contained. No script imports the parent STR8-N project, a local board backup or a historical builder. Python 3.11+ runs the offline checks. Rebuilding firmware requires the installed WDC `wdc02as` assembler and `wdcln` linker on PATH; these proprietary tools are not redistributed.

From the repository root:

```text
python tools/build.py --out build/one
python tools/build.py --out build/two
python tools/verify.py --build build/one --compare build/two
python tests/test_boot_and_opaque.py --build build/one --out build/cpu-one
```

Use fresh output directories. The builder copies `src/`, assembles the RAM worker and vectors first, regenerates symbol/image includes, links F and the three RAM tools, and checks every output BIN against `baseline.json`. It supplies a 4096-byte F image with reset/interrupt vectors and supplies matching S19s for inspection. F's own raw loader accepts BIN, not S19.

`firmware/` holds the preview's built candidate: payloads, symbol maps as JSON and a source-hash build manifest. `python tools/verify.py` verifies those files without requiring WDC. The model tests use the vendored BSD CPU cores, with synthetic flash and counters. They cover saved/manual B0–B3 entry, F-only recovery cancellation, CONFIG entry/default saves and opaque read/replace/no-op/restore with protected-sector and durable-wear assertions. They shorten polling/delays and CRC loops and cannot validate physical serial timing, power cuts or ACIA operation.

For packaging after verification:

```text
python tools/package.py --out dist
```

The ZIP uses an explicit public-file allowlist, a fixed timestamp and sorted paths. It excludes `.git`, build outputs, serial logs and owner backups. A file manifest and external SHA-256 accompany the package. GitHub CI verifies the checked-in candidate and runs the CPU/NOR suite; it does not claim to rebuild firmware without WDC.

The CONFIG candidate differs from its board-specific predecessor only in the same-length `2609` → `STR8` banner. Its addresses and instructions are unchanged. All other BINs retain their predecessor hashes. The baseline, provenance and validation files preserve that distinction.
