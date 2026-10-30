# 2512: unplanned D rotation and exact-history restoration

2026-10-29. The g6 plan incorrectly counted CF00 as an ordinary append slot.
Native CONFIG's JE_SPACE reserves pageF for a peer-erase intent. After CC00,
CD00 and CE00 were used, CONFIG C B wrote its D-erase reservation at CF00,
erased the occupied D sector once and committed the new root at D000.
This exceeded the reviewed zero-C/D-erase scope. It was a planning error;
the native writer behaved as its source specifies. No additional erase is
needed or planned to remediate it.

Read-only paired inspection confirms:

- F is exact, A/B are the intended g6 images, and B0/B1/B2 and B3:8/9/E are exact.
- The journal is valid: newest sequence1015, seventeen records, same B default,
  generation6, enabled mask15, entries8/8/8/8, delay and other retained metadata.
- Counts are B0:9=10, A40/B47/C52/D33/F24. D's extra physical erase cannot be
  undone; its count33 must be retained. The intended three erases also occurred.
- The twelve old C records remain exact. The original D000/sequence998 record
  was erased by rotation, but its complete raw256 bytes were durably backed up
  before any RAM program or flash write. Fresh owner RAM/ZP has been restored
  and independently verified after inspection.

## Minimal compensating action

Restore the exact archived D000 record at blank **D100-D1FF**, commit byte last.
This is an older history record, not a new policy/counter snapshot. The newest
D000/sequence1015 record stays unchanged, including the real D count33. The
strict journal classifier admits the restored older record without changing
the selected default, generation, current counts or uncertainty flags. All
thirteen original raw records will then be present again; the old D record's
physical location becomes D100. Expected total valid records: eighteen.

The private RAM helper is fixed to that one page. It checks RA/13, exact frozen
F CRC and a byte-exact preimage of all A000-DFFF before writing. The archived
record is embedded from the original verified backup. It uses only the pinned
RAM byte programmer after the BRK hook, never an erase or native allocation/
rotation command. It verifies every programmed byte and the complete row.
Re-running it after success refuses the changed preimage rather than repeating
a write. No F, other image, boot-setting, SRAM or additional erase is included.

This compensating append completes the owner's preservation requirement within
the ongoing authorized continuation. It does not make the earlier extra erase
part of the original scope. Retain the observed wear count and original logs,
then independently recapture all banks, restore/read back fresh owner RAM/ZP,
verify physical B-default boot and release COM4. Published downloads stay unchanged.

## Prevent recurrence

The new read-only `tools/native_journal_room.py` reports ordinary slots and the
reserved intent page. On the original CB00 preimage it reports **three**
zero-erase native operations, not four, and identifies occupied D as the next
rotation target. A future no-C/D-erase operation plan must fit this bound before
any mutation begins. Never assume every blank C/D page is an ordinary slot.
