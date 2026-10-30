# 2512 services g4 / WB5: RAM qualification scope

Owner requested continued 2512 qualification and preparation of a later
installation review. This stage is **RAM-only**, with no flashing or storage
writes. The installation plan will require separate exact-scope approval.
Use 2512 / COM4 / USB A10MQFLCA / 65C02 / FT245. Other boards remain excluded.

Use the existing services-g4 artifacts without rebuilding:

| Artifact | Use |
| --- | --- |
| RAM dispatcher, 4096 bytes, SHA256 f068f7d36f0f243aaf6c45d255e1059bc1e608ac36d0ac3524b6a1c7f8aa2b82 | Exact unmodified image at 2000–2FFF; a small separate RAM call bridge invokes entry2008 |
| Full WB2/SP1 RAM packet, 11264 bytes, SHA256 0ae64d54ff50f2f7c8132e1dad109dc06d36e348e3e2b0f4767d414d350b7842 | Existing raw loader places WB5 at4800–66FF and PROGRAM provider at6B00–77FF |
| Existing private PB reader, 767 bytes, SHA256 5dadab107c2663f6b75b8b2267b0ca480c3dcda854219b1635063cad68ff68a1 | Reuse only CRC-framed READ commands to capture SRAM; its W command is never sent |
| Qualified Foundation READBACK | Full-bank comparison and verified owner RAM/ZP restoration |

1. Acquire the shared serial lease, admit the installed MON B g8/65C02, and
   double-capture original owner RAM0200–66FF and ZP00–DF through native Dump
   **before** loading any RAM helper. This gives fresh prefix authority.
2. Double-read all four flash banks and require the admitted hashes, including
   F and every C/D record. Expected journal:31 valid rows, DE00/seq1028, saved
   B/g8. Abort on a changed board identity, image, journal or unavailable port.
3. Load the existing WB5/SP1 packet, check help, explicit EDU selection, guarded
   PROGRAM/WORK queries and Table. `SRAM PREP` may acknowledge disabled VIA CB
   flags through its existing guard, with no SPI clocks or RTC/PF acknowledgement;
   it cannot override an enabled pin/interrupt owner. Capture all128KiB SRAM.
4. Copy/verify the unmodified g4 RAM dispatcher and invoke it through a separate
   ordinary-RAM bridge. Check M1/M2/M3/W/APPS and missing-app refusal, cached
   MAINT/FLASH/CLOCK dispatch, read-only clock refresh and public return.
5. Check MAINT LOAD and spaced syntax against the actual older flash bundle:
   it must consume LOAD, select the forced loader path, then refuse the old
   bundle without calling the workbench. Extra arguments must be refused before
   any load. The g4 code/loader are not patched to manufacture a positive result.
6. Check WB5/SP1 bounded BATCH, missing-name Restore and AUTO preview followed
   by NO. Never send YES, run a retained owner program, format, retire a record,
   set the clock, change trim, or acknowledge RTC power-fail flags.
7. Read/compare all128KiB SRAM again; double-compare all flash banks. Restore
   original owner RAM/ZP using READBACK, return to the original ROM MON B/B3>
   context, and independently compare native Dumps. Release COM4 and restore
   RTC admission flags, leaving the existing schedule and samples intact.

Zero flash/journal/SRAM-data/WORKSPACE writes, resets, power cuts, firmware
builds or CPU simulations. RAM code, buffers and state are temporary and
covered by the owner escrow. Public interrupt/HOLD pointers are not patched.

## Boundary

This can qualify the actual g4 RAM dispatcher, current RAM tools and refusal
against 2512's older flash bundle. A successful **new** MAINT LOAD from board
flash remains pending installation of the matching WF/03 bundle and services.
The later review must account for native C rotation, raw history archived on
the host, exact component postimages and boot/wear carry-forward. No erase is
authorized by preparing that review. F stays golden and unchanged.
