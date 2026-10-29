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

The [five-checkpoint plan](MON_AB_PLAN.md) and [shared contract](MON_AB_CONTRACT.md)
are recorded. Checkpoint 1's [compatibility review](MON_AB_COMPATIBILITY_REVIEW.md)
identified the exact g0034 pair and its conflicts. A new common core now builds
A/B and RAM smoke candidates in one build pass. Their exact hashes passed the
[scoped 2512 hardware trial](MON_AB_2512_ACCEPTANCE.md): 21 RAM checks and 34 ROM
checks, including physical A/B startup, handoff between the slots and Q to REC>.
This is a development checkpoint, not a new monitor release or broader CPU claim.

EDU, SSRAM, RTCC, battery and wear remain visible status fields. Unavailable
provider data uses `--`; battery/wear use one `*` caveat. The monitor reads
tracked wear without installing a journal writer. The owner authorized the
[reviewed 2512 trial](MON_AB_2512_TRIAL_SCOPE.md) completed with four monitor
erases and four wear reservations, no F writes and no C/D erases. Original images,
boot settings and owner RAM/ZP were restored; old records remain intact. The board
ends at REC> with COM4 released and no Mona image left installed.
Optional EDU/SSRAM/RTCC/battery adapters remain checkpoint 5 work.
No F rebuild or CPU simulation occurred. Original checkpoints remain in Git history.
