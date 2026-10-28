# Release status

Repository/package name: **STR8N-F**. First public tag: **v0.1.0-preview.1**. Firmware lineage remains **b15 / PR04 / generation $8000000F**. Repository versioning does not rename or silently advance the on-board firmware identity.

This source preview extracts a small, directly buildable project around F and opaque B0–B3 booting. It contains no original WDC firmware, owner flash images, PF/RTC records, SRAM backups, board EUI/USB identities or personal wear counts. The CONFIG banner is generic. Synthetic counts in model tests are fixtures.

Completed preview checks:

- Two independent direct-source builds produce matching four-component BINs.
- SHA-256 checks bind the built files to the exact sources and baseline.
- Both CPU models pass 26 boot/config/opaque NOR test groups.
- Packaging and extracted-package checks require no parent-tree inputs.

These checks supplement the parent project's board-specific onboarding work. They do not convert that work into general factory-board or ACIA qualification.

Before a stable 1.0 release:

1. Finish the actual CONFIG save/restore exercise on the existing preserved board, retaining its wear, backup and SRAM evidence.
2. Extract a general factory-WDC backup/F-only RAM migrator and a journal initializer with explicit unknown-history/import policy. Verify that unrelated sectors remain unchanged and stop at REC> after each stage.
3. Provide a matching host opaque installer with identity admission, binary framing, escrow, progress, readback and clear recovery states. Perform the install/read/no-op/restore lesson on hardware with a designated sacrificial target.
4. Cold-boot every supported CPU/console/bank path, test missing/torn/conflicting C/D and monitor images, and exercise interrupted writes and power transitions. ACIA needs its own physical evidence.
5. Freeze the public service contract, image map, firmware identity and operator keystrokes, and reproduce the final release from a clean checkout.

MON A/B, VERSION/CAPS, MAINT and EDU/SRAM may become separate optional packages after extraction and testing. A B1 application selector and OSI BASIC/Fig-Forth images are another package with its own licensing and integration tests. A combined full-load BIN must declare every sector it replaces; it must not become the default factory onboarding path.

Publishing procedure for this preview: commit the prepared standalone tree, create `95westus/STR8N-F`, push main, then publish the ZIP and checksum as a GitHub **prerelease**. A stable release tag follows completion of the applicable gates above.
