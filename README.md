# STR8N-F 0.3.0 — BASE1 / PR05

F is now self-identifying and **source/binary frozen**, generation **00000001**.
This is an unpublished candidate. The authorized 2512 known-b15 upgrade and
preserving BASE1/PR05 hardware case passed, including native console keys and
original RAM/image/history preservation. Broader release acceptance remains
pending; 2205 is untouched. See the [2512 result](docs/2512_BASE1_ACCEPTANCE.md)
and [release checklist](docs/RELEASE_STATUS.md). Existing release archives were
deliberately left unchanged.

Startup now prints:

```text
STR8N-F 0.3.0 g00000001
BASE1 / PR05
```

The existing chooser/recovery commands follow. F identifies boot/recovery;
the running OS/image owns its own identity and board/service status.

| Flash | BASE1 role |
| --- | --- |
| B0/B1/B2:8-F | Owner opaque images |
| B3:8/9/A/B/E | Owner opaque images |
| B3:C/D | Boot settings and erase-accounting journal |
| B3:F | Exactly 4096 bytes of bootstrap/recovery |

Opaque capacity is 116 KiB. Optional A/B monitor-selection compatibility does
not reserve those physical sectors. No MON, EDU, VERSION provider or SPI SRAM
is required. Available targets may still contain owner data.

The append-only identity change preserves existing PR05 private addresses,
worker/vector bytes and hardware vectors. The FI locator at F03C points to a
bounded identity record. F has 367 usable tail bytes.
[F_FREEZE.json](F_FREEZE.json) binds its exact bytes and inputs. See the
[identity contract](docs/F_IDENTITY.md) and [resolved issues](docs/ISSUES_RESOLVED.md).

F generation 00000001 is a new component counter. The existing SNBT field for
optional monitor generation stays 8000000F; journal sequence is separate.
Changing a setting, OS name or RAM catalogue does not change F generation.
The current toolkit still uses matched PR05 private calls; a general public
ABI migration is not claimed.

The new `STR8N-F-MAP-RAM.bin` supplies `M 1` grid, `M 2` sector detail and
`M 3` wear detail. W+ means recognized WDC resident bytes; W? means possible
WDC; U+ unknown; .. erased; F+ admitted running F. WDC recognition covers
F800-FFFF only and does not validate the whole bank or prove bootability.
See [RAM map details](docs/RAM_MAP.md). Load the RAM tool through recovery L.

Serial Console 0.1.0 is included for interactive use and function-key RAM
loading. Install `requirements-console.txt`, then run `python tools/nf_console.py`.
F2 selects a file, F4 loads it from recovery, and F5-F8 load MAP/CONFIG/OPAQUE/DEMO.
F10 explicitly connects; nothing opens on startup. See the
[console guide and full key table](docs/SERIAL_CONSOLE.md). Host checks and the
preserving 2512/BASE1 native-key/dialog trial pass. Other platforms and the
remaining write/failure matrix are still pending. F is unchanged.

Check existing files:

```text
python tools/verify_base1.py
python tools/boot_identity.py firmware/payload/STR8N-F-BOOT-4096.bin
```

For a later RAM catalogue change:

```text
python tools/build_base1.py --only map --out build/fresh-map-output
```

Frozen F is copied/hash-checked, not assembled. No routine reproduction build,
CPU model or device action occurs. See [build policy](docs/BUILD.md).

Six matching payloads are prepared: F, CONFIG, OPAQUE, DEMO, READBACK and MAP.
The independent NFM1/NFA1 helpers are reused without rebuilding. BASE1 host
prompts, SHA/size checks and map guards match these files. Checks are static or
host-only; no target instructions or devices ran.

Hardware acceptance, existing-SNBT F upgrades and generic live F-recovery
provisioning remain release gates. The WDC command remains explicitly
unqualified. Published v0.2.0 and previous MIN1/compaction checkpoints are unchanged.
