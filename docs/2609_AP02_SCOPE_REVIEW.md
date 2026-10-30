# 2609 AP/02 flash-app launch: target review

**Owner approved: “Approve two-erase B0:9 trial.”** October
30, 2026, 65C816 emulation / FT245, MON B g8 and services g4. The owner asked
to qualify named flash-app launch with a reviewed target. 2512 PROGRAM is a
separate no-flash trial. 2205 and 2604 are excluded; no power cuts or resets.

**Closed:** [execution, original-WDC restoration and RTC readmission passed](2609_AP02_ACCEPTANCE.md)
within exactly these two erases. The approval grants no retry or further
flash-write allowance. The original 17 rows are retained; final 19 rows.

## Fresh target admission

Fresh native owner RAM/ZP double escrow, four-bank double captures before/
after, restoration and original REC> return passed. The journal has 17 valid
records, D000/seq1031, default S, mask 00. **B0:9 is not blank: it belongs to
the retained WDC image.** No owner-sector candidate in B0/B1/B2 is fully
erased. This review requests temporary use of B0:9000-9FFF, exact restoration
of its 4096 bytes, and verification of the complete original WDC bank.
Erased bytes or a map label alone do not grant target ownership.

Original sector SHA256:
`9222ad4ca64e3b11661accc7d9a20906f9d7988927fc773ee1e74f4e2dbb2d56`.
Original complete WDC B0 SHA256:
`1398d9551f7072ff36203307f55b7e41204f2579ce667515920a2703845eef94`.
Both original banks/captures and the separate sector are backed up on the
host. The original WDC image is temporarily altered during the trial and
must be restored before closeout. F/recovery and MON B stay intact.

## Exact write budget

| Operation | Flash change | Journal |
| --- | --- | --- |
| Install unsealed AP/02 fixture with existing OPAQUE | One B0:9 erase/program | D100/seq1032; B0:9 count 2 to 3 |
| Seal header CRC, then payload CRC | Four 1-to-0 byte cells at 901C-901F, native guarded !M; no erase | None |
| Restore the original WDC sector with OPAQUE | One B0:9 erase/program | D200/seq1033; B0:9 count 3 to 4 |

**Two sector erases total**, both B0:9; two append-only reservations; zero
C/D erases, F writes, MON A/B/E replacements or other image writes. All 17
original raw journal rows remain on chip. Final 19 valid rows, D200/seq1033;
C=78/D=48/E=45/F=31 unchanged, B0:9=4 (decimal). All other counters, saved
default S, mask 00, entries 8000, delay and prior-wear flags carry forward.
No automatic retry or extra erase allowance.

Reuse the existing 88-byte public-console/HOLD example at 9020. Only its AP/02
CPU byte changes 02 to 16 and the header CRC is recalculated; no code rebuild.
First leave both CRC fields FF to check header refusal, seal the two header
CRC cells to check payload refusal, then seal the two payload CRC cells to
check valid inventory and `APP APPDEMO` execution directly from flash.
Verify `?` redisplay, then bare Q through public HOLD back to MON B. Do not
send a trailing CR to the app's immediate Q command.

Before each mutation, require its admitted preimage. Independently compare
each planned full-bank/journal result before continuing. Restore owner RAM/
ZP before running the app so native post-return Dump can prove app/HOLD
preservation. Restore the exact original WDC sector, compare every final
bank and old journal row, independently restore/read back owner RAM0200-66FF
and ZP00-DF, then return REC> and release COM8.

There are no SPI SRAM data/WORKSPACE, EEPROM, RTC SET/trim/PF writes. The
existing RTC sampler bytes and profile remain unchanged; advance its source
admission for the two new journal rows using the new preserving receipt, and
perform a read-only requalification. Preserve its schedule, samples and
baselines. This does not qualify new65C816 native mode or an old vendor app.
ASM/DBG stay deferred. Published downloads and frozen F stay unchanged.

Private sealed plan in the parent project:
`output/qualification/2609-AP02-scope-20261030-r1/plan.json`, SHA256
`01b1753b72c20069f85f89db7226b489d8a97dd603115d2a13b42f8700fb50e8`.
Fresh capture receipt SHA256:
`4b6bb79e60d26df4a9cb3309c08af71200e60dc082c6f77ae2b0b755cc52134f`.
