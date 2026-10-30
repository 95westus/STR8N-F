# 2512 g5/WB1 continuation and A/B installation scope

2026-10-29. The owner instructed: **"continue, including it you have to flash"**.
Proceed with the prepared RAM trial first. This authorizes necessary g5 A/B
installation after that trial passes; it does not permit F changes or other
boards. The earlier RAM-only document describes that first stage, not a veto
on this later authorization. No additional install confirmation is requested.

Target: 2512/COM4/FT245 A10MQFLCA only. Leave 2205,2604,2609 and other boards
alone. No power cuts. Keep the published release kit/downloads unchanged.

## Fresh baseline and RAM stage

Capture owner RAM/ZP from installed g4 before any RAM BIN, then capture all
four banks twice. Full fresh captures must match the admitted g4 baseline.
Archive original A/B separately. RAM trial uses the exact g5/WB1 candidates in
[the checkpoint manual](MONA_WORKBENCH_WB1.md); preserve the actual fresh owner
bytes, not assumptions from an old receipt.

The session EDU profile and explicit guarded SRAM PREP are included: PREP can
acknowledge disabled CB flags only when the other VIA idle checks pass. No
active VIA configuration is forced, no guard is bypassed, and no PROGRAM or
WORKSPACE byte, format, allocation or message is written. If the guard still
refuses, record that limit rather than claiming a successful SRAM read.

## B3 scope after RAM acceptance

The fresh baseline has ten valid records through C800/seq1007. Freeze and
verify exact expected complete B3 postimages before starting each operation:

| Operation | Journal append | Erase target | Result |
| --- | --- | --- | --- |
| Install canonical g5 A | C900 / seq1008 | B3:A once | A count38 to39 |
| Install canonical g5 B | CA00 / seq1009 | B3:B once | B count45 to46 |
| CONFIG C B | CB00 / seq1010 | None | Same B default, generation binding4 to5 |

Final planned counts are A39/B46/C52/D32/F24 (decimal). Zero C/D erases, zero F
writes, and all ten prior raw journal records retained exactly. Entries8/8/8/8,
enable mask15, delay, uncertainty flags and default choice B stay unchanged.
Only the necessary saved-B generation binding changes. All other bank/sector
contents remain exact; the two replaced monitor originals remain on the host.

Use the existing matching OPAQUE RAM replacement path for A/B: it reserves the
erase before touching the target, verifies the sector and returns to recovery.
Install canonical g5 bytes directly. No extra !M flash install-marker check is
needed: force.inc is unchanged and was already qualified on g4. No F updater,
C/D provisioner, SRAM writer or legacy app/maintenance writer is involved.

Admit and test A from recovery before touching B. Test native L Ctrl-C before
payload and a normal WB1 load, Q/HOLD to A, Table/Restore and SRAM behavior.
If A fails, stop with original g4 B intact; do not automatically repeat an
erase. After B installation, independently read B3 again, test B and handoff,
then append the single default generation binding. Unknown completion always
requires readback before deciding a next action; never blindly retry a write.

## Closeout

Independently read all four banks twice. Require exact sealed postimages,
golden F, all old C/D pages, all owner images outside A/B and expected new
counts/policy. Verify saved-default startup and identify whether its evidence
is a warm handoff or a physical RESET. Restore fresh owner RAM0200-66FF and
ZP00-DF and independently read back every byte from the installed ROM monitor.

Owner-RAM restoration evicts the RAM-only WB1 module. Leave identical g5 A/B
installed with B default, but document that WB1 must be loaded again using L
to use T/R/EDU/SRAM/WORK. No flash sector is silently claimed for persistent
WB1 storage. Source/ASM/DEBUG, Store and persistent WORKSPACE messages remain
future work. Release COM4 and write the receipt, preservation hashes and honest
qualification limits. Additional erase targets or repeated erases need a new
concrete scope assessment; this document budgets only the two above.
