# Storage through APPS: bounded checkpoint

Owner direction: continue automatic Store start-address selection and stop
after APPS. Source/ASM, DEBUG, WORKSPACE messages and the full FLASH editor
remain outside this checkpoint. F stays exact BASE1/PR05; use only 2512/COM4.
Preserve owner images, boot policy, tracked wear, owner RAM/ZP and all SRAM.

## Implementation order

1. Keep flash Store/AUTO; port the existing SS1/SS2 PROGRAM directory format,
   payload CRC, page allocation, commit-last Store, Table and checked Restore/run.
   Select PROGRAM explicitly; never use WORKSPACE or format implicitly.
2. Add deliberate `MAINT LOAD` and shared storage syntax/discovery. A compatible
   old cached module remains usable until an explicit reload. AUTO determines
   a start within the selected backend; it never selects a backend itself.
3. Add APPS listing, compatible image admission and deliberate named launch/
   return. List native CLOCK/MAINT/FLASH and supported PROGRAM/owner images;
   retained legacy private-call assets must not be advertised as compatible.
4. Qualify on2512 from fresh complete backups, then install the accepted tools
   within a separately reviewed journal-rotation scope. Stop after APPS.

## Space plan

Keep application RAM 0200-47FF. Extend the tool bundle to B2:8/9/A, with a simple
bounded copy loader for WB2 and a separate PROGRAM provider. Run provider code
in6B00-77FF, below frozen worker7800; use non-owner scratch6700-69FF. Validate
both headers and full CRCs before dispatch. Save/restore monitor6A state while
using a512-byte loader at6900. The added B2:A legacy-utility sector must be backed
up and included in the reviewed scope. Force edits can invalidate provider code;
admission must refuse it. Compression was considered but rejected here to keep
the loader bounded and avoid temporarily borrowing more application RAM.
No F ABI or monitor-slot rewrite is needed for the private storage extension.

First inspect/back up the full131072-byte SPI SRAM twice using guarded reads.
Record the actual mounted layout, directory and eligible test extents before
admitting PROGRAM writes. No WORKSPACE write, layout/format change, mode-register
write or electrical interruption is included. Restore every changed SRAM byte
after the live tests, independently read it back, and restore owner RAM/ZP.
The owner subsequently approved one specific exception: retire superseded
SSRAM slot7's commit at0023F (A5 to00), whose11224-byte CLK payload at00800
exactly matches the retained CLOCK payload at03400. Retain the newer CLK at06000
and the different flash CLOCK atB1:B000. Archive both full SRAM captures and the
original64-byte directory block; do not format, move payloads or collect other
records merely because names match. This cleanup is separately reported from
temporary test-byte restoration.

## Journal boundary

At the prior checkpoint: latestDD00/seq1027; one ordinary appendDE00 remains,
DF00 is reserved intent, C occupied. Installing new B2/E code and restoring a
B0 app fixture will exceed that room. Before flashing, archive complete raw C/D
and review exact target erases, native C/D rotation, retained latest counts and
boot policy, and where older raw rows will survive. This plan does not authorize
an unreviewed C/D erase. Continue independent implementation while review is
pending; do not consume the final slot speculatively.
