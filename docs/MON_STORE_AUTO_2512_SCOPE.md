# 2512: automatic flash Store start address

Owner direction: continue automatic determination of the storage start address;
earlier authorization allows continued 2512 development/flashing as needed and
B0 test use with restoration. Other boards, F and published downloads stay alone.

WB2 g4 adds `S bank AUTO RAMfirst RAMlast [name]`. Existing explicit addresses
remain available. AREA still admits the selected B0/B1 record arena. AUTO scans
structural SR01 records from 8000 so a record crossing AREA's start is detected.
Inside AREA, unknown/malformed occupied data or a record crossing its end is
refused. Complete and pending records reserve their entire header/payload span,
including FF bytes. AUTO selects the append tail after the last record; holes
are not reclaimed. Whole-span blank/source/bounds checks and YES remain in force.
It never selects another bank/backend, erases, formats or changes a boot setting.
SSRAM PROGRAM placement/writes and Table/Restore discovery are separate ports.

Build the changed module once, reusing the unchanged loader. E, A/B and F are
reused exactly. WB2 retains 4800-66FF and two flash sectors B2:8/9; no extra
application RAM or flash sector is allocated. G4 linked 7103 bytes, 63 free.

## Live gate and write limit

Only 2512/COM4 (FT245 A10MQFLCA), idle, no power cuts. Fresh native owner RAM/ZP
escrow precedes loading any RAM helper. Capture all banks twice and match the
current device checkpoint. Require B0:9 entirely FF and three ordinary native
journal slots before admitting any test write; otherwise stop before writing.

RAM g4 tests use only B0:9 for fresh-byte programming: explicit Store, AUTO on
empty/occupied arenas, all-FF payload extents, pending records, chosen address,
NO, syntax/range/full/cross-boundary/corrupt refusal, Table/Restore/run and the
public return path. Original AREA is an explicit test declaration, not inference
that erased owner flash is generally free. Read back every bank against exact
fixture postimages. No SSRAM or RTC transaction is part of this gate.

After a successful gate, restore original B0:9 with one journaled erase, then
replace B2:8/9 with the matching g4 bundle (two journaled erases). Maximum:
**three sector erases, three append-only wear reservations; zero C/D erases,
E/A/B/F writes or generation/default binding changes**. No automatic write retry.
On an earlier gate failure, restore B0 if needed and stop without installation.

Expected successful final counts: B0:9 **10->11**, B2:8 **594->595**, B2:9
**263->264**. A=41, B=48, C=52, D=33, E=27, F=24 stay unchanged. Journal sequence
1024->1027, 27->30 valid rows; original 27 raw rows retain their offsets.

After installation, force a RAM-module eviction, verify checked board-side load,
test AUTO selection/cancellation from installed B without another data write,
M1/W and CLOCK return. Verify all flash, boot policy and old rows, then restore
and independently read owner RAM 0200-66FF / ZP00-DF, warm-enter B g8, release
COM4 and checkpoint. Restore a valid older cached module as owner RAM too;
document B2/G8000 for an explicit current-flash reload instead of invalidating
captured RAM. No further physical RESET is needed for unchanged F/A/B.
