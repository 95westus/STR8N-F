# Store with an automatic start address

WB2 g4 is installed and live-qualified on 2512 for automatic flash Store
start-address selection. See the [acceptance](MON_STORE_AUTO_2512_ACCEPTANCE.md)
and [reviewed scope](MON_STORE_AUTO_2512_SCOPE.md). MON A/B remain g8, E remains
g2, and F and the published N-F kit stay unchanged.

| Command | Function |
| --- | --- |
| `B2`, then `G 8000`, then `Q` | Explicitly load the current board-stored module, then return to MON |
| `MAINT` | Enter an admitted cached module, loading flash only if it is absent/invalid |
| `AREA bank first last` | Admit an inclusive B0/B1 flash record arena, 8000-DFFF |
| `AREA` | Close the arena |
| `S bank address RAMfirst RAMlast [name]` | Store at an explicit start address |
| `S bank AUTO RAMfirst RAMlast [name]` | Determine the append start address in AREA |
| `T [bank]` | List selected-bank flash SR01 records |
| `R [bank] name\|address [L]` | Restore a unique selected-bank record; L loads only |

AUTO means **determine the start address**, with bank/backend already selected.
Cross-backend Table/Restore discovery is separate. SSRAM PROGRAM Store/placement
remains planned; this increment makes no SPI write.

## AREA and placement

AREA is the owner's declaration of a record arena, not proof of free ownership.
Never declare an extent belonging to an opaque image, source/compiler output or
another storage owner. B2/B3 are excluded. AREA is RAM state, not a saved boot
setting. It may survive a RAM-preserving reset; bare AREA, reloading WB2 or
entering its MAINT shell clears it.

AUTO scans from 8000 to the declared limit, recognizing complete and pending
SR01 records. A record crossing either AREA boundary is refused. Inside AREA,
only erased bytes and structurally valid records are accepted; unknown or
malformed occupied data is refused. Payloads are skipped by their full declared
length, so an FF suffix or entirely FF payload is never mistaken for free space.

The chosen address follows the last record. AUTO does not reclaim earlier gaps,
compact records, select another bank/backend or erase to create room. A complete
header/payload span must fit and be entirely FF. Full, unsafe or cancelled
requests leave flash unchanged. The explicit-address form retains its existing
blank-span preflight; choosing a legitimate record boundary remains the caller's
responsibility for that low-level form.

Source is inclusive RAM 0200-47FF; WB2 borrows 4800-66FF while loaded. The complete
24-byte header and payload must fit AREA below E000. Names contain up to 16
printable non-space characters and are uppercase-normalized. Duplicate names
remain allowed; name Restore refuses ambiguity. Use an explicit record address
to resolve it. SR01 has **no payload checksum**.

## Example

These are illustrative owner-chosen addresses. Replace them with your admitted
arena and intended RAM bytes; erased sectors are not automatically available.

```text
B3> B2
B2> G 8000
WORKBENCH> Q
B3> AREA 0 9000 9FFF
B3> S 0 AUTO 3000 30FF EXAMPLE
Target B0:9000
STORE, no erase; type YES> YES
Stored; verified bytes, commit last; no payload CRC
B0> T 0
B0> AREA
B0> R 0 EXAMPLE L
Loaded; RAM readback matched source. SR01 has no payload CRC.
```

The next AUTO Store appends after EXAMPLE's 24-byte header and 256-byte payload,
at 9118. Q deliberately returns to recovery; `R` without L explicitly executes
the stored program. A compatible program can return through public HOLD to the
active monitor. Owner RAM restoration reinstates exactly the captured bytes,
which may include an older valid WB2. MAINT/CLOCK accepts a compatible cached
module; use B2/G8000 to explicitly replace it with the current flash copy. The
Python terminal remains available for host RAM BIN transfers.

## Programming and preservation

The chosen bank/start address is printed before YES. NO, rejected YES, invalid
arguments, full/corrupt AREA or preflight cancellation write no record. A batch
queue cannot answer YES: Store remains outside the BATCH allowlist.

After YES the foreground unit finishes or halts in RAM on program/verify failure.
Fresh header/payload bytes are programmed and read back; FF values are skipped;
the complete marker 3F is written last. Pending records are reserved by AUTO and
not admitted by Restore. There is no automatic erase, overwrite, retry, rollback
or repair. The foundation NMI gate is held during programming; arbitrary owner
NMI/DMA concurrency is outside this nonreentrant contract.

Store never erases or appends wear history. Reclaiming a sector requires an
explicit journal-reserved maintenance/OPAQUE operation. Golden B3:F and C/D
remain protected. SR01 verification confirms current RAM/source equality, not
future retention or arbitrary later corruption. Direct bank boot images use
the matching OPAQUE/CONFIG workflow, separately from SR01 Store.

WORKSPACE messages and metadata stay outside PROGRAM and C/D. This increment
does not mount, format or write either SSRAM allocation.
