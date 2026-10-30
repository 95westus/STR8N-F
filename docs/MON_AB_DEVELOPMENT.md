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

## Current increment: generation 2

The owner chose to keep A and B identical. Both now include the same explicit
`T` RTCC sampler; `V` shows its last sample, with no automatic startup read and
no inferred time zone. [Adapter details and limits](MON_AB_RTCC_ADAPTER.md)
cover idle-pin admission, bounded I2C, restored DDRA, input-latch limits and
the distinction between register-pointer writes and RTC data writes.

G2 A/B/RAM candidates are built and stored separately under
`monitors/candidates/g00000002/`. The [g2 RAM trial passed](MON_AB_G2_RAM_ACCEPTANCE.md)
on 2512: two coherent RTCC samples, retained V display and unchanged flash/history,
with original owner RAM/ZP restored and COM4 released. No monitor ROM was installed.
G2 A/B ROM startup remains untested; g1's receipt does not qualify changed bytes.
EDU/SSRAM/battery adapters and the limited remaining slot space need the next review.

## Product direction: usable monitor

The owner expects familiar Dump/Modify, loading, rich board/startup status and
potential debugging. The [usability plan](MONA_USABILITY_PLAN.md) now maps that
command set to implemented versus planned behavior and supersedes a status-only
next increment. D/M/G/L/Q usability comes next; A/B stay identical. DEBUG belongs
at the monitor layer with its own workspace and hook/return contract. Only F
must remain the frozen 4KB foundation; larger features can use optional modules
without assuming any owner sector free. No new build or board action accompanies
this design checkpoint.

## Installed increment: generation 4

The owner requested installation on 2512, selected Dump/Modify first and added
!M with B3:C/D/F protected. [G4 acceptance](MON_AB_G4_2512_ACCEPTANCE.md) records
the exact installed A/B/RAM hashes and qualification limits. G3 was built but
superseded before installation. G4 adds hex/ASCII and longer dump ranges, checked
inline RAM/ZP Modify, explicit raw force, no-erase flash 1-to-0 preflight, and
TIME naming. Both A/B remain alike. The [manual](MONA_COMMANDS.md) distinguishes
these working commands from L/maps/DEBUG and full startup features still planned.

Only A/B were erased, once each, with original images backed up. C600/C700
retain those erase attempts; separately approved C800 binds the existing B
default to g4. F is unchanged, original records remain exact, and post-reset
full owner RAM/ZP readback matches escrow. Final context is MonaB>, COM4 free.
