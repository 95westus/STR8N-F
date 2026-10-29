# Proposed MON A/B trial: 2512, frozen BASE1

Authorized candidate scope, not a hardware result. After reviewing the exact
four-erase A/B install/restore budget, the owner answered: "Use 2512; idle and
COM4 free." The target is 2512/COM4 only. Fresh admission and RAM smoke still
precede monitor writes. No device result is claimed by this document.

## Candidates

Mona **0.1.0-dev g00000001**, built once from the shared core. All candidates
are NOT_EXECUTION_QUALIFIED. The [contract](MON_AB_CONTRACT.md) and
[candidate manifest](../monitors/payload/manifest.json) define the interface.

| Image | Destination | SHA-256 |
| --- | --- | --- |
| A, 4096 bytes | B3:A000-AFFF | `10d7b3d2bdacf892e7d8b4079dae495ed5473613f7d60b3aa54c1bfddc6058a5` |
| B, 4096 bytes | B3:B000-BFFF | `bca8d0b52568309c0cd2004a0e2c3fbce96f04cacc9889ffe5dc48f4bccce519` |
| RAM, 2587 bytes | 0200-0C1A, temporary smoke test | `1ca0de5f7ffd24ec996649b651a8cc86ac4012de415ec5451a5f98ca3f520034` |

F must match frozen SHA-256
`8f4d35ac66730daa773515980983fcf442be3b1bdf1e523d3752ec3615657cc1`
before any trial. A mismatch stops. No F write, rebuild or replacement is allowed.

## Write budget and preservation

- Proposed board **2512 / COM4 / 65C02 / FT245** only, after verifying its
  actual USB identity and that the port is released. Other boards, including
  2205, remain excluded. An occupied port is not closed forcibly.
- At most **four monitor-sector erases**: install A, install B, restore original
  A, restore original B. Both originals must be durably captured and independently
  verified before replacement. No other owner-image sector is a scratch target.
- Up to **four append-only C/D erase reservations**, one per monitor-sector
  replacement, using the matching OPAQUE path. No C/D erase or journal reset.
  Fresh admission must prove adequate erased append space for the whole plan;
  otherwise stop before the first write. Latest counts carry forward.
- Boot settings are not changed. Recovery is selected at startup by the host;
  the test must not run unrelated saved application images. No default-save test
  or additional CONFIG write is part of this scope.
- No power cuts, external programming, EDU/SPI/RTC configuration, storage format,
  or deliberate power-fail injection.
- Preserve original owner RAM 0200-66FF and ZP00-DF. Original **pre-helper escrow**
  and its continuity/freshness must be established before any helper upload.
  A dump made after loading a helper is not a substitute for overwritten bytes.
  Stop if valid escrow cannot be established from the latest verified checkpoint
  and board-idle history. Mona's 6A00-6AFF state and system scratch are separate.

Exact journal addresses, sequences, before/after counts and image preimages
depend on a fresh device capture and must be sealed in the private live plan.
The budget above does not authorize unplanned rotation or restoring counters
to earlier values. The trial ends with original images/settings and verified
owner RAM restored, current wear accounting retained, REC> and COM4 released.

## Execution order

1. Obtain target/port confirmation and establish original RAM escrow. Acquire
   the shared serial lease. Verify frozen F and capture all banks independently
   twice, saving current settings/history and target-sector originals privately.
2. Load the RAM smoke candidate first. Exercise identity/help, the retained
   status rows and symbol legend, syntax/overflow/CR/LF/CRLF/BS/DEL/cancel,
   bank selection and safe dumps. Compare reported wear with the captured record.
   RAM G must refuse; Q must reach REC>. A failure stops before monitor writes.
3. Admit the exact four-replacement plan and append-space budget. Install A/B
   through matching OPAQUE, with reservation before erase, readback and CRC/SHA
   checks. Observe each image through F's own A/B validation and entry path.
4. Repeat inspection/parser/status checks independently in A and B. Verify Q
   reaches REC> despite the existing default. Exercise bounded G handoff only
   to the admitted candidate monitor entry; do not execute owner opaque images.
5. Restore original A/B through preimage-bound OPAQUE operations. Independently
   compare every final bank, requiring only the planned C/D append pages to
   differ from the original. Preserve all old journal rows and all other counts.
6. Restore and read back original owner RAM/ZP. Finish at REC>, release COM4,
   and record a result that distinguishes installation, execution, restoration
   and any incomplete stage. No automatic flash retry follows a failure.

Physical RESET may be requested to recover from a halted candidate or to
verify actual startup. The receiver must be ready before a reset request.
The golden F recovery path remains the anchor throughout.
