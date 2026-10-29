# MON A/B development on N-F 0.3.0

Branch: `codex/mona-monb`, based directly on the immutable `v0.3.0` source
checkpoint `a5f1d83f6a7017eb30e6268c6e0b1fd12fce6a8d`.
The [dependency manifest](../monitors/base1-dependency.json) pins exact F bytes,
generation 00000001 and BASE1 / PR05. N-F is the foundation; monitors are
separate optional images with their own name, version and generation.

## Initial scope

- Develop compatible MON A and MON B occupants; Mona is the chosen optional
  monitor name. A/B may offer different personalities or be alternative images.
- Keep richer board/status output, application menus and subsystem navigation
  in the monitor/application layer.
- Define application handoff and deliberate return to recovery. Restarting
  through F uses the saved default and can launch the same image again.
- Start with the retained g0034 monitor's ABI calls, RAM ownership and provider
  dependencies. Its existing bytes are not proof of BASE1 compatibility.
- Respect the current A/B header, CRC, entry and PR05 compatibility checks.
  Ordinary opaque images use a configured bank entry instead.

F remains frozen at exactly 4096 bytes. This branch does not expand F's ABI,
move the release tag or change published downloads. C/D stay boot/wear journal
space; A/B remain optional occupants of owner image space.

The [five-checkpoint plan](MON_AB_PLAN.md) is now recorded. Checkpoint 1's
[initial compatibility review](MON_AB_COMPATIBILITY_REVIEW.md) identifies the
exact g0034 pair, its private-call dependencies and RAM conflicts. It is not a
BASE1-compatible binary; the next checkpoint defines a new shared contract.

No new MON binary is built or qualified. No simulation, flashing or board
access occurs; image, settings, history and owner-RAM preservation constraints
remain. The original branch-creation checkpoint is retained in Git history.
