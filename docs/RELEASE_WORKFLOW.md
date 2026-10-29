# Candidate ZIP and migration acceptance

The reviewed 2512 source/hardware cases are closed. The next acceptance uses
the extracted **STR8N-F-BASE1-0.3.0-rc1.zip**, without development-checkout
fallback. That live ZIP migration test is **NOT RUN**. Building/checking an
archive does not close it or publish a final release.

## Required contents

- Frozen 4096-byte F and five matching RAM tools/component manifest.
- Python Serial Console 0.1.0, console_core.py, requirements-console.txt
  pinning pyserial 3.5, and F-key instructions.
- WDC capture/migrate, programmer-F C/D provisioner and supported b15 upgrade
  commands, prebuilt engines, and migrator/build.py's pure wrapper generator.
- Installation/boot/journal guides, scoped acceptance receipts, MANIFEST.json
  and a standalone kit checker. Original source paths stay unchanged.

Supply the identical 4K F BIN beside the ZIP, checksums and a source ZIP.
Do not include owner WDC images, RAM, per-board plans, raw logs or private
fixture packets. Source recipes are separate from owner-bound lab outputs.

## Build once from the source checkpoint

```text
python tools/package_base1.py --out dist/base1-rc1
```

Use a fresh directory. Packaging verifies and copies existing files; no
assembly, CPU model, serial port or flashing occurs. 0.3.0-rc1 identifies
the toolkit; F version/generation stay unchanged. Old archives remain intact.

## Check a fresh extraction

Run these from the new operator-kit directory:

```text
python tools/verify_release_kit.py .
python tools/verify_base1.py
python tools/nf_console.py --help
python migration-host/nf_migrate.py --help
python migration-host/nf_migrate_live.py --help
python migration-host/nf_provision_live.py --help
python migration-host/nf_upgrade.py --help
```

These commands open no port. Check every manifest member, ZIP/direct-F
checksums, F length/identity, local guide links and runtime dependencies.
Record the exact ZIP SHA-256. No firmware rebuild or simulation group is needed.

Install Python 3.11+ with Tk and the pinned requirements on the operator host.
Run the bundled terminal from the extraction. Its existing native-key
acceptance covers Windows/2512, not every host/adapter.

## Live ZIP migration test — pending

1. Identify the board and exact allowed footprint; leave 2205 excluded. Use
   no deliberate power cuts and keep F's golden-runtime boundary.
2. Use only extracted files. Assign the port, disconnect the terminal, obtain
   fresh independent backups/original escrow and review the real journal plan.
3. Select WDC migration, programmer-F provisioning or supported SNBT upgrade.
   A BASE1 board with valid SNBT proves a no-op, not WDC migration.
4. Execute the reviewed scope and retain verbose progress, durable erase
   intent, commits and physical RESET/recovery captures. No blind retry/replay.
5. Independently verify final banks, promised images/settings/history and
   original RAM/ZP restoration/readback. Finish at REC> with the port released.
   Include terminal/F-key/cancellation acceptance from this same extraction
   without overlapping CLI serial ownership.
6. Save a receipt binding ZIP SHA-256, manifest/component/source hashes,
   board/CPU/adapter, exact writes/counts, preservation results and limits.
   Only that evidence can mark packaged migration PASSED.

The candidate is ready for that reviewed next test. Other platforms/layouts,
interrupted provisioning and external programmer operation remain outside
the scoped happy-path evidence. See [status](RELEASE_STATUS.md).
