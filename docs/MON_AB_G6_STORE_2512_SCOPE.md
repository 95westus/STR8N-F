# 2512: WB1 g3 Store and selected-bank prompt g6

Prepared 2026-10-29 for the owner's continuation, including necessary flashing,
and request to replace MonaB> with Bx> for the selected data bank. The earlier
permission named 2512/B0 any; this scoped trial uses only B0:9 and restores it.
All owner bytes, images outside the deliberate A/B update, boot policy and
history remain protected. No other board or port, F change, power cut, SRAM
write or published-kit/download update is included.

## Candidates and behavior

Mona g6 uses B0> through B3> in ROM and RAM, following the selected data bank.
Active MON A/B remains in the status banner. Same A/B commands and frozen F.
WB1 g3 adds explicit `AREA bank first last` ownership bounds and
`S bank flash RAMfirst RAMlast [name]`. Bare AREA clears the window. B0/B1 only,
8000-DFFF; source RAM0200-4FFF. AREA does not infer free space or change flash.
It remains RAM state and may survive a reset that retains RAM; loading or
restarting WB1 clears it. It is not a persistent allocation/profile format.

Store checks the complete record extent erased, binds YES confirmation to the
requesting console, skips its optional LF, writes with no erase, verifies each
programmed byte and commits SR01's3F marker last. It honors the foundation NMI
gate during the foreground unit; arbitrary owner NMI/DMA concurrency is outside
the contract. Cancellation is before that programming unit; once accepted,
the bounded unit finishes or halts in RAM on a programming/verify failure.
Never return into ROM while flash-idle state is uncertain. SR01 still has no
payload CRC. No C/D write happens for Store itself, because it does not erase.

G6 and WB1 g3 are new candidates, not qualified until the following closes.
G5/WB1 g2 qualification and backups remain retained separately.

## Fresh escrow and RAM trial

Use installed g5's native D to capture fresh owner RAM0200-66FF and ZP00-DF
before loading any helper. Capture all four banks twice; verify frozen F,
installed g5 and thirteen records through CB00/seq1010. B0:9 must match the
complete original erased sector, but its use is based on owner authorization,
not erased-state inference. Archive all original sectors/owner RAM durably.

Load WB1 g3 and g6 RAM. Check B3> initially, B0>/B1>/B2>/B3> after selection,
status still says RAM/slot identity, and T/R changes reflect their selected bank.
Use a bounded RAM2000-203F sample containing a reviewed public PUTC/HOLD HELLO
prefix plus data/FF bytes. Review the exact expected SR01 header+payload before
any S confirmation. No private-ABI legacy program is run.

Check unarmed/invalid/protected/out-of-window requests, prewrite cancellation,
and occupied-target refusal with no prefix write. Declare AREA0 9000 9FFF.
Write at most three small records wholly within B0:9, including non-sector-start
and duplicate-name cases. Verify complete raw bytes, Table, load-only Restore,
name ambiguity refusal, address Restore and the public HELLO return. Test clear
AREA and malformed/CRLF confirmation. No sector erase or boot-setting command
belongs to these Store tests. Existing EDU/SRAM status remains read-only.

## Cleanup and optional ROM installation after RAM acceptance

Seal exact complete B3 postimages before writes, admit each fresh preimage,
and never automatically retry an unknown write completion.

| Operation | Expected append | Erase | Expected counter |
| --- | --- | --- | --- |
| Restore original B0:9 after Store tests | CC00 / seq1011 | B0:9 once | 9 to10 |
| Install g6 A | CD00 / seq1012 | B3:A once | 39 to40 |
| Install g6 B | CE00 / seq1013 | B3:B once | 46 to47 |
| Bind the existing B default to g6 | CF00 / seq1014 | None | No change |

Thus at most three sector erases total: one test cleanup and two monitors.
Zero C/D erases or F writes. Preserve all thirteen old raw records; final valid
count17. C52/D32/F24 remain unchanged, and the same B default, enabled mask15,
entries8/8/8/8, delay and uncertainty flags remain. Only its generation binding
changes5 to6. All three B0:9 records are temporary and removed by its exact
restoration; the retained cleanup erase count must not be rolled back.

Admit/test A before replacing B, verify Bx> follows data-bank changes and module
returns, and verify the same B default boots g6. Independently capture every
bank after cleanup/install and match sealed postimages. Restore/read back all
fresh owner RAM/ZP, evicting WB1 deliberately. Release COM4 with g6 ready if
installed. Update development docs/receipt only; the N-F release stays frozen.
If fresh state differs or a candidate fails, stop before the next flash step,
inspect actual completion and restore owner RAM through the verified RAM path.
