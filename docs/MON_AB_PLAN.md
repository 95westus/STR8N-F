# MON A/B: five-checkpoint development plan

Branch: `codex/mona-monb`. Foundation: immutable N-F `v0.3.0`,
**0.3.0 g00000001 / BASE1 / PR05**, with exact dependency pins in
[base1-dependency.json](../monitors/base1-dependency.json).

## Checkpoints

| # | Work and deliverable | Exit condition | Current status |
| --- | --- | --- | --- |
| 1 | Review g0034 compatibility: identify exact A/B reference images, public/private calls, providers, entry shims and RAM ownership | A source-backed reuse/replace decision, named incompatibilities and an evidence inventory; no claim of execution compatibility | Initial review complete; [findings](MON_AB_COMPATIBILITY_REVIEW.md) |
| 2 | Define the shared monitor contract: entry/reentry, identity, console, parsing, bank selection, RAM/scratch, application launch and deliberate recovery return | Written interface and memory allocation; minimal command set and optional-provider behavior defined; no F changes | [Revision 1 defined](MON_AB_CONTRACT.md) |
| 3 | Implement the minimal shared Mona core: prompt, help, memory inspection and recovery return | A bounded candidate with local parser and public RAM console calls; no required E/B2/EDU provider; slot images and manifest produced by one planned build invocation | A/B/RAM candidates built once; exact hashes qualified on 2512 in checkpoint 4 |
| 4 | Qualify A and B as independent occupants using the same core | Correct slot/header/CRC/private binding and separate identity; authorized real-board entry, commands, handoff/return and preservation checks pass for both | [2512 acceptance passed](MON_AB_2512_ACCEPTANCE.md); originals and owner RAM restored |
| 5 | Add optional status adapters and later command modules | Useful status and maintenance features added as individually reviewed increments while common behavior stays shared | [G2 RTCC RAM trial passed](MON_AB_G2_RAM_ACCEPTANCE.md); g2 ROM trial pending; owner requests A/B remain identical |

Checkpoint 4 is the usable A/B foundation. Checkpoint 5 is incremental; it
does not block that foundation or N-F 0.3.0. Similar A/B candidates are useful
during development so one known-good image can be retained. Different roles
do not require unrelated codebases.

## Scope and working rules

- Keep F frozen; no new F ABI, release-tag change or replacement downloads.
- Keep monitor identity/generation separate from F generation and journal sequence.
- Share source modules compiled into independent slot images first. A mandatory
  shared flash provider is not required for the minimal monitor.
- Do not relabel or patch g0034's header to bypass BASE1's rejection. Its
  private implementation and entry shim are incompatible.
- Reuse logic only after reviewing its dependencies. No automatic full-system
  layout, RTC, EDU/SPI initialization, storage formatting or startup application.
- Begin with inspection rather than flash/config mutation commands. Existing
  CONFIG/OPAQUE tools remain separate until an explicit integration is designed.
- No CPU model, offline regression group, reproduction build or speculative
  second build. Build only when the implementation is ready or changed code
  makes it necessary. File/source evidence checks remain part of this review.
- Hardware work needs an explicit target and reviewed writes, fresh backups,
  original owner RAM escrow and preservation/readback. The owner authorized the
  reviewed 2512/COM4 A/B trial; no other boards or power cuts are included.
  F stays frozen; failure before successful RAM smoke prevents monitor flashing.

## First review result

The exact g0034 A/B pair is **not a binary-compatible BASE1 monitor**. Header
contract mismatch already blocks launch. Its entry shim and optional utility
gateway also overlap BASE1 worker RAM, and several private call addresses moved.
The common public RAM facade remains available at the same addresses.

That review led to the shared BASE1 contract and new core qualified in checkpoints
2-4. Checkpoint 5 has begun with an explicit read-only RTCC adapter. At the owner's
request, A/B remain identical; separate personalities are deferred. EDU mode,
SSRAM layout and battery policy adapters remain planned. F stays frozen.
