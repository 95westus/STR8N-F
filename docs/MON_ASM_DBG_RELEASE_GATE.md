# ASM and DBG are required for the next MON/tools release

Owner direction, October 30, 2026: **include ASM and DBG in this release**.
This is a release requirement for the next monitor/tools kit. Published
Foundation v0.3.0 and MON/tools preview 1 remain immutable historical releases.

**4K Foundation. Up to four banked environments.** Foundation remains the
exact 4096-byte F image, g00000001 / BASE1 / PR05. The resident development
tools belong to the optional monitor environment and have their own version,
generation, memory use and qualification receipts. No expanded F ABI is
required by this plan.

## Required operator workflows

| Tool | Required before the next release |
| --- | --- |
| ASM | Deliberate launch; numbered insert/replace/delete, NEW/LIST/PASTE and cancellation; existing line editing; labels/local labels/EQU, the supported 65C02 instruction set and directives; ASM, LST, SYMS and useful source diagnostics; DUMP/S19; checked output bounds, run and return |
| Source persistence | Preserve the existing AS/1 capsule semantics; named SAVE/LOAD with explicit flash/PROGRAM backend, source validation, CRC and unsaved-edit confirmation; source and output ownership reported; no implicit owner-sector or WORKSPACE allocation |
| DBG | Deliberate activation and BRK entry; registers and checked editing, disassembly, memory dump/modify, RAM breakpoints, step, step-over and continue; X/HOLD exit restores patched bytes, interrupt pointers and return hooks |
| Integration | Same front door from MON A/B; usable Python-terminal workflow and manual examples; tested failure/refusal paths; source/assemble/debug/store/restore/run round trip |

Initial CPU scope is 65C02 and 65C816 **emulation** with direct page, DBR and
PBR zero and IRQ masked. Native assembly/debugging is outside this increment.
816 instruction differences must remain explicit: the legacy decoder already
avoids treating 65C02 RMB/SMB/BBR/BBS bytes as those instructions on an 816.

## Reviewed legacy dependencies

The preserved b35 candidate remains the parity reference. The later local
`src/current/assembler`, `source-store` and `debugger` supply the existing
EQU/LST/SYMS, diagnostics, console-editing and corrected DBG1 implementations.
Their unmodified source snapshot is reference-only, recorded under
`monitors/devtools/legacy-reference/`; no old executable is admitted by copying
that source. Existing branches, source and hardware references stay intact.

| Binding | Required BASE1 adaptation |
| --- | --- |
| ASM calls NS_INIT/NS_EDIT/NS_DISPATCH at legacy B1:9000 offsets | Link the companion source module from generated symbols; preserve parser/dirty-state semantics |
| Source helper calls B2:D6A9 storage and uses B0:8-D as its source arena | Adapt the request/range contract to current PROGRAM and explicitly admitted flash storage; erased space alone grants no allocation |
| ASM output/source/symbol/state buffers | Publish exact bounds for every variant; avoid the MON 6A00 state, provider 6B00-77FF and the provider's 6700-69FF scratch; load modules without destroying active source |
| Legacy DBG BRK wrapper | Replace its assumed bank/Y/X/A pushes with an explicitly paired wrapper for the public BASE1 emulation BRK pointer at 7E02; BASE1 itself preserves the ordinary hardware frame |
| Legacy DBG monitor D/M offsets and 7DF9 return hook | Provide checked memory commands and return routing without the old monitor offsets or a hook in the C/D scanner's private state |
| Legacy flash guards at 78A8/E9E8 and fast-return pocket | Remove those old mutation/record interception bindings; derive any necessary bank bridge from exact PR05 symbols and explicitly own its RAM |
| Opcode/disassembly tables | Derive addresses from the newly linked assembler map; keep the decoder and stepper paired to those exact tables |
| HOLD and interrupt ownership | Save/validate hooks before publishing a complete handler; refuse an existing owner; restore hooks, breakpoints and bank context on every exit or failed activation |

The current F worker ends at 7BE8 and its private bank selector is 7848.
Legacy active-debug flags at 7BFC and 7Dxx monitor fields cannot be reused
merely because their addresses existed in b35. C/D scanner state, RAM console,
vectors, monitor state and providers require a complete allocation review.
Keep public RAM console calls; pin any necessary private adapter to frozen F.

## Implementation and qualification order

1. Import/hash the existing readable source, record private bindings, then
   define paired module headers, generated entry symbols and RAM ownership.
   Reuse the existing editor/assembler and decoder/stepper rather than creating
   a second language or a host-only substitute for the resident tools.
2. Port the assembler/source service and debugger independently of F. Review
   branch ranges and layout before each concrete increment; build once and
   reuse the resulting bytes. Do not run routine CPU simulations or rebuild
   the foundation/workbench merely to obtain another copy.
3. Prepare RAM-first qualification with explicit borrowed RAM/vector ranges,
   original owner escrow, protected flash/boot policy and complete cleanup.
   Any PROGRAM/flash fixture writes require their own exact admitted scope.
4. On 2609, enter a commented example, assemble/export/check its bytes, run and
   return; debug a RAM program through BRK, register edits, breakpoints,
   S/N/C and X. Check cleanup after an error, cancellation and HOLD. Verify
   unchanged flash/settings, restored owner RAM/ZP and every borrowed hook.
5. Repeat the matched CPU-sensitive workflows on 65C02 within a separately
   reviewed board scope. Keep 2604's integrated rc1 reference and 2205's
   firmware intact. Other boards are outside the current PROGRAM authorization.
6. After RAM gates pass, review exact component sectors, native journal room,
   preservation and erase history before installation. A development-bank
   layout is an optional image allocation, not a Foundation reservation.
7. Build a new candidate kit with the qualified ASM/DBG payloads, examples,
   terminal, manual and receipts. Test the extracted kit. The current frozen
   release downloads and tags are not replaced.

## Release status

**Open — blocks the next monitor/tools release.** Source import/review is
preparation; no BASE1 ASM or DBG execution pass is claimed yet. Positive
PROGRAM qualification is a separate gate and cannot substitute for ASM/DBG.
The next candidate must carry both required components and their exact live
receipts before it can be described as meeting this release goal. Full b35
parity remains tracked in [the parity checklist](MON_B35_PARITY.md).
