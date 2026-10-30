# Proposed Mona g2 RAM-only trial: 2512

**Prepared scope, not authorization or a hardware result.** Board 2512 / COM4 /
65C02 / FT245 only, after the owner confirms the board idle and port free.
All other boards remain excluded. No flashing, journal appends/erases, boot-policy
changes, power cuts or F changes are included. The previous four-write A/B trial
is closed and is not reused as a new erase budget.

Exact candidate: `MONA-0.1.0-dev-g00000002-RAM.bin`, 3695 bytes, entry `$0200`,
SHA-256 `43d26db41be05f12a153aa31a7b628ce210a18795db5b3fdcd538e840b324a4c`.
Review [the RTCC adapter's access and latch limits](MON_AB_RTCC_ADAPTER.md)
before enabling T; the wire protocol changes the RTC address pointer but no
RTC register data, EEPROM contents or flags.

1. Establish pre-helper owner RAM/ZP escrow from the final g1 restoration receipt
   and owner-confirmed idle continuity. Acquire the serial lease, verify 2512's
   USB identity and frozen F, and independently capture all four banks twice.
   Check live ZP and RAM beyond the helper against escrow. Stop on any mismatch;
   never substitute a post-helper prefix for original owner RAM.
2. From REC>, load only the exact g2 RAM candidate. Verify generation 2, retained
   status fields and no automatic hardware probe. Verify `T garbage` refuses,
   help, V, basic inspection, cancellation and Q-to-REC behavior.
3. Invoke explicit T only on the reviewed EDU Rev D wiring. If its idle-pin/
   input-latching guard refuses, record the refusal and stop device sampling;
   do not reconfigure the VIA to make it pass. Otherwise verify date/time against
   the candidate's sampled raw bytes and normalized fields, refresh with a
   second T, and check V labels the retained sample. No SET, calibration, flag
   acknowledgment, battery policy change or SPI/SRAM access is included.
4. Return to REC>, independently read every bank and require exact equality
   with the before capture, including all C/D records and F. Restore original
   owner RAM `$0200-$66FF` and ZP `$00-$DF`, read both back, leave REC> and release
   COM4. Record build-only versus observed behavior and any incomplete check.

No native keyboard GUI, 65C816, A/B ROM startup or electrical fault injection
claim follows from this RAM trial. Failed bus/clock/invalid-calendar paths remain
unqualified unless actually observed; do not write fake RTC dates to cover them.
