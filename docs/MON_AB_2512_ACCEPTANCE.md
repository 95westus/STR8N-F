# Mona A/B: 2512 hardware checkpoint

**Passed, 2026-10-29.** Mona **0.1.0-dev g00000001**, built once, completed
the [reviewed trial](MON_AB_2512_TRIAL_SCOPE.md) on **2512 / 65C02 / FT245 / COM4**.
The exact candidate hashes and evidence hashes are recorded in the
[validation receipt](../monitors/validation/2512-mona-0.1.0-dev-g00000001.json).
This closes checkpoint 4 of the [development plan](MON_AB_PLAN.md).

## Behavior observed

The RAM candidate passed 21 checks before monitor-sector writes. A and B then
passed 34 ROM checks in total, including separate physical RESET startup through
frozen F, identity/status, help, bank selection and comparison against a saved B0
dump, protected execution/I/O refusal, overflow rejection, CRLF, BS/DEL, Ctrl-C
and ESC. Each monitor reentered its own entry and Q reached REC> despite saved
default B. Explicit G handoff worked B to A and A to B.

Both slots retain EDU, SSRAM, RTCC, Battery and Wear rows. Compatible optional
provider adapters are not yet ported, so EDU/SSRAM/RTCC/battery use `--`.
Wear reads the selected, fully CRC-validated journal record; the observed maximum
was B2:8, `$000250` (592). Battery and wear use the shared `*` caveat:

```text
* Battery condition/prior flash wear unverified; counts are tracked attempts.
```

## Writes and preservation

All counts below are decimal; journal page addresses are hexadecimal.

| Operation | Monitor sector | Reservation | Sequence | A / B count afterward |
| --- | --- | --- | --- | --- |
| Install Mona A | B3:A | C200 | 1001 | 36 / 42 |
| Install Mona B | B3:B | C300 | 1002 | 36 / 43 |
| Restore original A | B3:A | C400 | 1003 | 37 / 43 |
| Restore original B | B3:B | C500 | 1004 | 37 / 44 |

Exactly four monitor erases and four append-only wear reservations were used.
There were **zero F writes, zero C/D erases and no power cuts**. C/D/F counts
remain 52/32/24; every other counter also remains unchanged. All three original
journal records remain byte-for-byte intact, followed by four new records.
Saved default B, enabled mask 15, entries 8/8/8/8 and prior-wear uncertainty
remain unchanged.

Independent paired final bank reads verified original A/B and all other owner
images. Only the four planned journal pages differ from the original flash
capture. F still has SHA-256
`8f4d35ac66730daa773515980983fcf442be3b1bdf1e523d3752ec3615657cc1`.
Original owner RAM `$0200-$66FF` and ZP `$00-$DF` were restored and independently
read back. The escrow was the latest verified pre-helper checkpoint plus the
owner's idle confirmation; fresh checks covered ZP and the RAM suffix, with the
helper-overwritten prefix retained from escrow.

**Final state: REC>, COM4 released, original images installed; Mona is not left
installed.** No other board was accessed. Published N-F files, tags and downloads
were unchanged.

## Host interruptions and continuation

The first host handoff stopped before sending a replacement request: an extra
ESC/CR prompt probe confused the OPAQUE handshake. No flash write occurred.
Physical reset, independent complete-bank reads and owner RAM restoration passed
before resuming with the unchanged OPAQUE tool and its fresh startup prompt.

After the two successful installs and A's checks, B's reset receiver expired
before the owner pressed RESET. It released COM4 without further writes. The
continuation freshly verified all four banks against the installed state,
rearmed and captured B's physical startup, completed B/handoff checks, and used
only the remaining two approved restore writes. There were no reinstalls or
automatic flash retries. Both interrupted runs remain in the private evidence.

## Limits and next step

This qualifies these three candidate hashes on 2512 only. It does not qualify
65C816 execution, another console adapter, native GUI keyboard use, or execution
and return from owner applications in another bank. The build manifest retains
its historical `NOT_EXECUTION_QUALIFIED` creation-time labels; the separate
validation receipt records the subsequent hardware result without rebuilding or
changing candidate bytes. No CPU simulation or second build was performed.

Checkpoint 5 remains: optional status adapters and useful monitor personalities.
CONFIG/OPAQUE integration is not implemented in Mona; those remain separate
tools. F's ABI stays frozen and Mona remains an unreleased development component.
