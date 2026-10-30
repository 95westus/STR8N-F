# Preserved ASM/DBG source reference

These 15 source files are byte-identical copies from the owner's local
`src/current` tree. `provenance.json` records their paths, sizes and SHA-256
hashes. Original source, historical branches, installed firmware and published
downloads were not changed by this import.

This is reference source for the planned BASE1 port, not a BASE1 payload or
an executable candidate. The files retain old private addresses and monitor,
storage, interrupt and bank assumptions. Do not assemble/install them as a
replacement for the frozen Foundation or current monitor tools.

The [ASM/DBG follow-on plan](../../../docs/MON_ASM_DBG_RELEASE_GATE.md) records
the adaptations and live qualification required before those features ship.
ASM/DBG do not block the current monitor/tools release.
