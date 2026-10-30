# WB1 g3: Store, Table and Restore

Historical WB1 checkpoint. Current MON A/B uses WB2 at 4800-66FF, with source
RAM 0200-47FF. See [AUTO Store](MON_STORE_AUTO.md) for the new start-address
selection increment and its live qualification status. The WB1 addresses and
loading example below describe the earlier immutable artifacts.

The Store implementation uses the existing SR01 flash-record format. It is a
RAM-loaded WB1 module, available through MON A/B's shared module interface. It
does not change the frozen F ABI or allocate flash automatically.

| Command | Function |
| --- | --- |
| `HELP` | Full module help, including Store, from MON A/B or WORKBENCH |
| `AREA bank first last` | Declare an inclusive owner-controlled flash window in B0/B1, 8000-DFFF |
| `AREA` | Close the current window |
| `S bank flash RAMfirst RAMlast [name]` | Save an inclusive RAM range as a flash record; YES required |
| `T [bank]` | List records; also selects the specified data bank |
| `R [bank] name\|address [L]` | Restore; L loads only, otherwise explicitly run |

AREA is an owner declaration, not a free-space scan. Choose an unused extent
that belongs to your record area; erased bytes inside an image or another
record are not automatically available. AREA writes RAM only and supplies no
allocator or record-overlap map. It can remain across a reset that retains RAM;
bare AREA or restarting/reloading WB1 closes it. It is not a saved boot setting.

Store source must be RAM 0200-4FFF. The whole 24-byte header plus payload must
fit the declared flash window and remain below E000. B2/B3 are excluded from
this Store profile. Named records have at most 16 printable non-space characters;
names are uppercase-normalized. Duplicate names are allowed, but name Restore
refuses ambiguity within the selected bank; use an address instead.

Illustrative owner-chosen addresses, not a declaration that your B0:9 is free:

```text
B3> L
SEND BIN
<send MONA-WORKBENCH-WB1-g00000003-RAM.bin>
WORKBENCH> Q
B3> R 1 HELLO0200 L
B1> AREA 0 9000 9FFF
B1> S 0 9000 0200 0216 HELLO
STORE, no erase; type YES> YES
Stored; verified bytes, commit last; no payload CRC
B0> T 0
B0> AREA
B0> R 0 HELLO
OK
<monitor startup banner>
B3>
```

Select the BIN with F2 in the Python console, type L at MON A/B, then press F3
at SEND BIN. Loading WB1 borrows 0200-16FF and 5000-66FF. Its runtime protects
5000-66FF against ordinary M. It is evicted when owner RAM is restored.

The programmer preflights the entire target span as FF before confirmation.
NO, Ctrl-C, an invalid YES line or a rejected request writes no record. The
YES dialogue stays with the requesting console and accepts CRLF input. Once
YES is accepted, the bounded foreground programming unit finishes or stops
in RAM on a programming/verify failure; cancellation is before that unit.
There is no automatic erase, overwrite, retry, rollback or pending-record repair.

The writer programs fresh header/payload bytes, skips FF values, compares each
programmed byte directly, then writes the complete marker 3F last. The normal
foundation NMI gate is preserved/held during the unit; arbitrary owner NMI/DMA
concurrency is outside this nonreentrant contract. A failure with uncertain
chip-idle status halts in RAM instead of returning into ROM. Recovery F remains
protected. No deliberate power-interruption/failure injection is part of this
checkpoint's qualification.

**SR01 has no payload checksum.** Verification confirms that the saved bytes
matched the current RAM source; it cannot certify future flash retention or
detect arbitrary later corruption. Pending/incomplete records are not admitted
by Restore. Storage allocation and source ownership remain the caller's job.

Store itself never erases or appends C/D wear history. Any later erase needed
to reclaim a sector belongs to a separately reviewed OPAQUE/maintenance path,
with a durable wear reservation and preservation backup. It must not silently
erase an occupied sector to make S succeed.

This stores flash program records. Persistent WORKSPACE messages and source/
PROGRAM SRAM writes are separate, still-planned work. Store does not format,
allocate or write SPI SRAM, and messages do not belong in boot/wear C/D.
Use R to execute an SR01 record. The matching OPAQUE installer remains the path
for directly bootable bank images. [2512 evidence and limits](MON_AB_G6_2512_ACCEPTANCE.md).
