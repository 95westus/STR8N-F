# STR8N-F 0.3.0-rc1 — BASE1 / PR05

> Give me 4KB, I can give you 4 boards.

With ~32KB RAM shared by four selectable bank environments.

This candidate consolidates the completed 2512 source/hardware closeout into
a portable operator ZIP and source ZIP. It includes **Python Serial Console
0.1.0**, pinned pyserial, function-key RAM loading, all three installation
hosts and their unchanged prebuilt engines, matching RAM tools, guides,
checksums and scoped acceptance receipts.

F remains **0.3.0 g00000001 / BASE1 / PR05**, exactly 4096 bytes, frozen at
`8f4d35ac66730daa773515980983fcf442be3b1bdf1e523d3752ec3615657cc1`.
Only C/D/F belong to the minimum persistent footprint; owner opaque space is
116 KiB. OS identity and service status stay in the running image.

The reviewed 2512 cases passed: existing-journal upgrade, BASE1/terminal
acceptance, CONFIG/opaque boot, WDC migration, programmer-F provisioning and
named chip-idle C/D recovery. See [status and receipts](RELEASE_STATUS.md).

**Migration from the newly extracted ZIP remains NOT RUN.** The package is
for that next test, not a published final release or qualification of every
board/layout/CPU/adapter. F stays golden. No power cuts or hardware actions
are part of this packaging step; 2205 remains excluded.

Follow [installation](INSTALLATION.md), [terminal use](SERIAL_CONSOLE.md) and
the [ZIP acceptance workflow](RELEASE_WORKFLOW.md). Older candidate ZIPs and
published v0.2.0 remain historical and unchanged.
