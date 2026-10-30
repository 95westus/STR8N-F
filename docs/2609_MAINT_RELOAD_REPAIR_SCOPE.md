# 2609 MAINT LOAD: additional scope review

**Approved by the owner and completed; see [acceptance](2609_MON_FEATURE_ACCEPTANCE.md).**
The original review and its exact additional limits are retained below.

MON B physically booted, preserved owner RAM/ZP and loaded CLOCK from flash.
Explicit MAINT LOAD exposed a dispatcher bug: it consumed LOAD but forwarded
the same option to the workbench, which accepts bare MAINT. Services g4 now
removes only the validated option, preserving leading/trailing-space handling.

Only the dispatcher was rebuilt, once. F, MON A/B, WB2, PROGRAM and the bundle
loader were reused. RAM g4 passed cold/warm/spaced forced reload, extra-argument
refusal before loading, bare MAINT, maps/wear/APPS, unchanged flash and restored
owner RAM/ZP. It remains uninstalled; current E is g3.

Applying g4 requires one B3:E replacement. The five ordinary C pages were used
by the approved installation; CF00 is reserved for intent. Native reservation
therefore also rotates occupied B3:D. **Two additional erases: D and E. Zero C
erases or F writes. No power cuts.**

CF00/seq1030 commits the E erase reservation and D rotation count; D is erased,
then D000/seq1031 commits the new root. E is then replaced and independently
verified. Expected counts: C78, D48, E45, F31. Other counts stay unchanged.

All 15 current C records remain at their exact locations. D's complete original
4KB sector is archived and hash-verified on the host before erasing it; its one
valid old record is D000/seq1014. That record will no longer be on the chip.
Final 17 valid records; latest D000/seq1031. Default S, mask00, entries8000 and
all other boot policy remain unchanged.

B0/WDC, B1, B2, B3:8/9/A/B/F, SRAM data, RTC/trim/PF history and owner RAM/ZP
remain protected. Restore/read back owner RAM/ZP, verify every bank and raw
postimage, return to REC>, and release COM8. No other board is involved.

Prepared originals, target E and exact C/D/E postimages:
`C:/SRC/STR8-N/output/qualification/2609-maint-reload-g4-scope-20261030/plan.json`.
Freshly re-admit those originals before execution. This is a new approval
because the previous five-erase budget is exhausted and D history moves to
the host. Published N-F and downloads remain unchanged.
