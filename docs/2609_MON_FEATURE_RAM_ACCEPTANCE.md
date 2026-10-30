# 2609 optional MON/tools RAM readiness

**Passed October 30, 2026: 65C816 emulation / FT245 / COM8 only.**
The unchanged g8/services-g3 RAM composite has SHA-256
`0d8ca453877a71becbd21360a6757c37a1488c68f7a6aca9f8e2c75de90b6758`;
the full WB2 g5/SP1 packet has SHA-256
`0ae64d54ff50f2f7c8132e1dad109dc06d36e348e3e2b0f4767d414d350b7842`.
No firmware was rebuilt or flashed.

MON identity CPU $16, help, Dump, ordinary/forced RAM Modify with restored test
bytes, F/C/D refusal, B0 inspection, TIME, maps/wear, APPS inventory and missing-
app refusal completed. Two valid native calendar reads were observed. This is
not a clock-accuracy or owner-app launch qualification.

PROGRAM initially refused with $01. Existing guarded `SRAM PREP` acknowledged
disabled VIA CB flags without SPI clocks. The subsequent query admitted SS1
PROGRAM0800-0FFFF, and Table listed four retained CLK records. `BATCH T;T`
completed; bad separators were refused. Missing-name Restore and AUTO Store
preview were exercised; NO canceled with no record written. There were no
PROGRAM, WORKSPACE, mode-register, EEPROM, RTC calendar/trim or RTC PF writes.
Positive 816 Store/Restore/run and full BATCH parity remain unqualified.

The standalone tool shell's Q normally uses HOLD to return to an active ROM
monitor. This fixture saved public RAM jump 4C937E, temporarily used 4CAFF2 to
enter golden recovery, then restored/read back 4C937E. No F bytes changed.
This private fixture is not an operator installation procedure.

All four banks were freshly captured twice and compared after the trial;
every flash byte, image, setting and C/D record matched. Owner RAM0200-66FF
and ZP00-DF were restored/read back. The helper prefix retained its independently
captured, subsequently restored original authority; remaining RAM/ZP was freshly
double-read. Final REC>, COM8 released; existing RTC profile unchanged.

Earlier host attempts are retained: expected-refusal handling and a prompt
allowlist stopped early; RAM was restored. A later I/O dump was correctly
refused by MON and also restored. One attempt deferred to RTC ownership without
opening a port. The final run used PREP's existing guard directly. No packet
changes, resets, flash writes or changes to 2604 were required.

Private evidence:
`C:/SRC/STR8-N/output/qualification/2609-mon-features-ram-20261030-r6/`.
The candidate includes a hash-only receipt. ROM installation/physical boot
acceptance and source/ASM/DEBUG replacement remain pending.
