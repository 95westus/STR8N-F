# 2512: automatic flash Store start address

**Passed and installed, 2026-10-29, 2512 / 65C02 / FT245 only.**
[Scope](MON_STORE_AUTO_2512_SCOPE.md),
[hash-only live receipt](../monitors/validation/2512-store-auto-wb4.json),
[commands and examples](MON_STORE_AUTO.md).

WB2 g4 is stored in B2:8/9. MON A/B stay g8, E services stay g2, the bundle's
own generation is 3, and F stays N-F 0.3.0 g1 / BASE1 / PR05. Only the changed
module was assembled/linked, once; loaders, E and monitor binaries were reused.
No CPU simulation, offline test group or reproduction build was run.

AUTO now means **determine Store's start address** inside the selected,
owner-declared flash AREA. It appends after complete/pending SR01 extents,
including their FF payload bytes. It does not choose a backend, reclaim holes,
erase, format or change a boot preference. Explicit addresses remain available.

## Live evidence

Fresh native owner RAM/ZP escrow and two complete matching bank captures
preceded the RAM load. B0:9 was admitted for temporary fresh-cell records and
was required to match an entirely FF original sector before any test write.

| Case | Observed result |
| --- | --- |
| No AREA / malformed AUTO / reserved RAM source | Refused before programming |
| Empty AREA | Target B0:9000; NO wrote nothing |
| Explicit record at 9000 with 256 FF payload bytes | Stored/read back; AUTO next selected **9118**, beyond the entire payload |
| Pending header at 9200 with 128 FF payload bytes | Table showed pending; Restore refused it; AUTO selected **9298** |
| Gap before the pending record | Preserved; append policy did not reclaim it |
| Full AREA / AREA crossing either record boundary | Refused before programming |
| Unknown occupied byte in AREA | Refused as unsafe/corrupt |
| AUTO-saved AUHELLO | Table, load-only Restore/readback, execution and public HOLD return to MON B passed |
| Installed module | RAM CRC invalidation forced checked flash reload of g4; MON B AUTO selected 9000 and NO left restored B0 unchanged |
| Existing services | M1/W and read-only CLOCK/return passed |

Complete readback matched exact fixture and final postimages. The pending
record was a controlled header fixture, not an electrical interruption test.
SR01 still has no payload CRC. These checks qualify the stated workflow,
not arbitrary legacy images or another CPU/console mode.

## Preservation and accounting

Exactly **three sector erases and three append-only wear reservations**:
restore original B0:9, then replace B2:8 and B2:9. The Store commands themselves
program fresh cells without erasing or appending wear records. No automatic
write retry, C/D erase, A/B/E/F write, boot binding change or power cut occurred.
No SPI/SSRAM write or RTC data-register write occurred; CLOCK performed reads.

| Tracked erase counter | Before | After |
| --- | ---: | ---: |
| B0:9 | 10 | 11 |
| B2:8 | 594 | 595 |
| B2:9 | 263 | 264 |
| A / B / C / D / E / F | 41 / 48 / 52 / 33 / 27 / 24 | unchanged |

All original 27 raw journal rows remain at their offsets. Final journal has
30 valid rows, sequence **1027 at DD00**. Default B/g8, mask0F, entries8/8/8/8,
delay, uncertainty mask and remaining boot policy are unchanged. B0/B1 match
their complete originals; other B2 assets and B3 images remain unchanged.
Fresh owner RAM 0200-66FF and ZP00-DF were restored, then independently read
through the installed monitor. Final state: **B3> / MON B g8, COM4 released**.
Other boards and published downloads were untouched.

Free bytes: **F 367; MON A/B 67 each; E 981; WB2 g4 63**. The two-sector module
still borrows 4800-66FF and leaves 0200-47FF for application RAM while loaded.
The captured owner RAM included valid WB2 g3. That older cache was restored
exactly, including its CRC; it is not the g4 copy now in flash. MAINT/CLOCK
accepts a valid compatible RAM module without checking its generation. Use
**B2, then G 8000** to explicitly load current flash g4; Q returns to MON B.
The bundle entry/loader code is unchanged from the qualified g8 bundle path.
The g4 flash reload and AUTO checks passed before the final owner restoration.
No cached RAM byte was invalidated after restoration merely to select g4.

## Next work and journal capacity

SSRAM PROGRAM Store/AUTO needs a separate write-backend port. Cross-backend
Table/Restore discovery, full apps/source/ASM/DEBUG, FLASH editing, CONFIG and
the remaining [b35 parity](MON_B35_PARITY.md) gates remain open. WORKSPACE
messages remain a separate admitted allocation outside PROGRAM and C/D.

Only **one ordinary zero-erase journal append remains, at DE00**. DF00 is the
reserved rotation intent and C is occupied. A future plan requiring more than
one native reservation must review C/D rotation and archive the old raw history;
no such rotation or C/D erase was authorized by this checkpoint.
