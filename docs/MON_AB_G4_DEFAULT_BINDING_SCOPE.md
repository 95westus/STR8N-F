# 2512: proposed saved-B generation update

**Approved and completed.** The owner answered "Approve binding B to generation
4". C800/seq1007 and the final physical saved-B boot passed. The remaining text
retains the reviewed pre-action scope; see [acceptance](MON_AB_G4_2512_ACCEPTANCE.md).

Both Mona g4 images are installed and verified, with native !M fresh-byte tests
passed. Original owner RAM/ZP are restored and the board is at MonaB> with
COM4 released. The two installation erases and wear reservations are complete.

The first physical default boot correctly entered REC>: saved B is bound to
generation **8000000F**, while the new B image is **00000004**. Frozen F checks
this binding before an automatic A/B launch. Explicit B admission works.
The install retained the old binding as part of preserving boot settings.

Proposed final action, requiring approval because it changes that saved binding:

- Use the existing exact matching RAM CONFIG command **C B** once.
- Append **C800, sequence 1007**: default remains B; bind generation 00000004.
- Nine existing records remain byte-for-byte; total becomes ten.
- All erase counts remain unchanged: A=38, B=45, C=52, D=32, F=24.
- Enable mask 15, entries 8/8/8/8 and uncertainty flags remain unchanged.
- **Zero sector erases, F writes or monitor-image writes.**
- Preserve/read back all images and original owner RAM/ZP; verify the saved
  default boot, then release COM4 with Mona B ready. No power cuts or other boards.

Fresh admission must match the complete post-install images, C700 record and
blank C800 page. If not, stop before C B. A sealed expected complete-B3 result
is retained privately. Do not repeat either monitor-sector installation.
