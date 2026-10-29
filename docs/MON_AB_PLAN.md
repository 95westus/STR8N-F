# MON A/B: five-checkpoint development plan

Branch: `codex/mona-monb`. Foundation: immutable N-F `v0.3.0`,
**0.3.0 g00000001 / BASE1 / PR05**, with exact dependency pins in
[base1-dependency.json](../monitors/base1-dependency.json).

## Checkpoints

| # | Work and deliverable | Exit condition | Current status |
| --- | --- | --- | --- |
| 1 | Review g0034 compatibility: identify exact A/B reference images, public/private calls, providers, entry shims and RAM ownership | A source-backed reuse/replace decision, named incompatibilities and an evidence inventory; no claim of execution compatibility | Initial review complete; [findings](MON_AB_COMPATIBILITY_REVIEW.md) |
| 2 | Define the shared monitor contract: entry/reentry, identity, console, parsing, bank selection, RAM/scratch, application launch and deliberate recovery return | Written interface and memory allocation; minimal command set and optional-provider behavior agreed; no F changes | Next |
| 3 | Implement the minimal shared Mona core: prompt, help, memory inspection and recovery return | A bounded candidate with local parser and public RAM console calls; no required E/B2/EDU provider; slot images and manifest produced by one planned build invocation | Planned |
| 4 | Qualify A and B as independent occupants using the same core | Correct slot/header/CRC/private binding and separate identity; authorized real-board entry, commands, handoff/return and preservation checks pass for both | Planned; no board access authorized by this document |
| 5 | Add useful personalities through command tables/modules | Launcher/status and maintenance features added as individually reviewed increments while common behavior stays shared | Follow-on |

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
  original owner RAM escrow and preservation/readback. Current work is source
  only: no ports, flashing, power cuts or board access, including 2205.

## First review result

The exact g0034 A/B pair is **not a binary-compatible BASE1 monitor**. Header
contract mismatch already blocks launch. Its entry shim and optional utility
gateway also overlap BASE1 worker RAM, and several private call addresses moved.
The common public RAM facade remains available at the same addresses.

Proceed to checkpoint 2 by defining a small BASE1 monitor contract. Use selected
g0034 parser/display logic as reference, replace its entry and private bindings,
and treat rich service/status providers as separately ported optional modules.
