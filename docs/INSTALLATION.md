# Installation boundaries

## Preserve the board first

Inventory the CPU, bank layout, entry addresses and resident firmware. Save complete original bank images, settings, erase history and any attached SRAM/provider data. Verify two independent reads agree before a destructive operation. Original WDC firmware and owner captures are not distributed by this repository.

B0 may be the owner's WDC backup. Preserve that B0 unless the owner explicitly assigns it as an installation target. Opaque installation and boot configuration are different operations: selecting an entry must not implicitly copy sectors or replace a backup.

## The F-only image

`firmware/payload/STR8N-F-BOOT-4096.bin` is **exactly 4096 bytes** for **B3:$F000–$FFFF only**. Reset vector is $F004. For a physical flash programmer, the bank/sector offset depends on its selected device and wiring; calculate and verify the actual address mapping before programming. Do not write this file as a complete 32 KiB bank or 128 KiB device image. Verify the programmed 4096 bytes byte-for-byte, reset into F and confirm `REC>`.

A factory WDC board needs an audited RAM migrator to perform that F-only write while keeping original banks unchanged. That board-specific migrator is not included in this source preview. Its eventual public workflow must back up WDC, choose the backup bank, preserve/import wear evidence, write only F, verify and stop at `REC>`. A blanket full-flash image would violate that workflow.

## C/D journals and wear counts

F-only recovery and DEMO do not require C/D. Saved bank/default choices and normal opaque erase accounting require compatible, valid C/D journals.

CONFIG `I` is a **blank-only primitive**: it refuses any nonblank byte in either journal sector and never erases them. It creates default S, all banks disabled and zero observed erase counters with unknown history marked. Those zeros mean no recorded erases in this journal, not a lifetime count or proof of unused flash. Factory programming also contributes unknown history.

Do not use this primitive to replace owner counts or invent a lifetime starting value. Existing C/D must be inspected and preserved or restored with a qualified owner-history process. The general factory provisioning policy and wear-history import tool remain release gates. The previously qualified board-specific history importer is not silently generalized by this preview.

## Optional sectors

| B3 sector | Role in this layout |
|---|---|
| 8, 9, E | Potential opaque/provider space; inventory before use |
| A, B | Optional matching monitor slots |
| C, D | Configuration and wear journals |
| F | Bootstrap and recovery |

B3 user booting is supported at a configured allowed entry when an appropriate image is present. It does not make all B3 sectors available. Journal relocation to D/E or SPI SRAM is a future layout change, not a configuration option in this build.

## Stable release acceptance

The remaining migration, recovery, actual opaque installation and cold-boot tests are listed in [release status](RELEASE_STATUS.md). No board was flashed to produce this standalone preview. Preserve the current hardware-qualified b15 image identity until an explicit firmware change is independently qualified.
