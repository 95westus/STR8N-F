# g7 / WB2 g1: command results and bounded BATCH

**Built once on 2026-10-29; not execution-qualified or installed.** 2512 still
runs the qualified g6 / WB1 interface. These candidates do not change F, saved
boot settings, existing images or the published N-F kit. New banners and
artifact filenames use STR8-N / MON A/B; A and B remain identical.

## Memory and interface checkpoint

WB1's 30-byte remainder cannot accommodate the required storage/app/batch work.
WB2 is an explicitly loaded RAM development module, with more code space and a
shared completion-result interface. It does not reserve a flash sector or claim
unused SSRAM. The source for MON and WB2 shares `workbench-interface.inc`.

| Range | Use |
| --- | --- |
| 0200-26FF | Temporary raw-BIN transfer staging, including a 256-byte loader |
| 4000-63FF | WB2 immutable code/header/padding; CRC trailer at 63FE/63FF |
| 6400-66FF | Volatile module buffers/state; existing layout retained |
| 6550 | Caller Restore destination floor, in pages |
| 655F | Completion result |
| 6560-6562 | BATCH active flag, text size, queue position |
| 6580-65A2 | Separate 34-character queue plus terminator |
| 6A00-6AFF | MON state, unchanged |
| 7800-7BE7 and 7E60 facade | Frozen foundation worker/ABI, unchanged |

Header: `MW 02 24 PR05`. Command entry: 4008. Shell entry: 400B. The whole
9216-byte block must have CRC16/CCITT zero residue before MON dispatches.
g7 admits WB2 and rejects WB1; installed g6 admits WB1 and rejects WB2. Load
the matching module explicitly. There is no automatic module upgrade.

**While WB2 is loaded, Store sources and Restore destinations are limited to
0200-3FFF**, further restricted by a RAM monitor's code floor. Ordinary Modify
protects 4000-66FF while module admission passes. Force remains explicit and
can invalidate the module; B3:C/D/F stay protected. The loader copies from
0300-26FF to 4000-63FF without overlap, after checking the module and frozen F.

This is a temporary RAM development layout, not full 2.0b35 memory parity.
Restoring owner RAM evicts it. Larger source/output/application workflows still
need reviewed provider/overlay loading and a non-overlapping transfer/return
path. No permanent reduction of the full-workbench RAM target is accepted here.

## Command completion contract

The command entry receives A=data bank and X/Y=bounded NUL-terminated command.
It returns A=resulting bank. C=1 means handled; C=0 means syntax/unsupported.
The separate result at 655F distinguishes successful completion from a handled
error, which the old carry-only interface could not do.

| Result | Meaning |
| ---: | --- |
| 00 | Completed successfully |
| 01 | Syntax or unsupported command |
| 02 | Refused/failed, including unavailable storage, bounds, missing/ambiguous record |
| 03 | Canceled |
| 04 | Destination RAM may be partially loaded |

Each dispatch initializes the result. Store/AREA success messages no longer
pass through the error return. Existing cancellation and partial-load paths
return their distinct result. Non-returning application launch remains an
explicit handoff; it is excluded from this first batch subset. This private
interface is between monitor/modules, not an expansion of F's public ABI.

## BATCH subset

```text
WORKBENCH> BATCH B1;T;B3
WORKBENCH> BATCH EDU ON;SRAM;WORK
```

These are usage examples, not captured hardware output. Maximum text after
`BATCH ` is 34 bytes, matching b35. All separators and the whole command
allowlist are checked before execution. Empty/leading/trailing segments,
overlength input and nested BATCH are refused. Individual arguments are checked
by the normal dispatcher as each command runs. This is a sequence, not a
transaction: a later failure does not undo earlier commands.

The initial allowlist is B/bank, T/Table, ?, HELP, EDU and **bare** SRAM/WORK
status. The queue is stored separately from the current command line. A command
failure stops the sequence; Ctrl-C/ESC is checked between commands and during
Table. The result is printed on stop. Queue bytes are never console input.
Store/YES, SRAM PREP, R/run, loaders, G, Q, application handoff and core D/M/V
are excluded from this increment. They need their own checked adapter/return
behavior before they join BATCH. Full b35 batch parity remains open.

T/S/R are still manual flash-record operations. AUTO placement, cross-backend
resolution, SSRAM PROGRAM writes, APPS, source/ASM/DEBUG and WORKSPACE messages
are not implemented by this build. No SRAM write/format opcode was added.

## Storage/application port findings

The preserved b35 sources establish separate formats and responsibilities:

- Flash SR01 uses a 24-byte header, pending FF/complete 3F, load/length and a
  16-byte name. It has no payload CRC or independent entry address.
- `store/source/sram-store.asm` implements mounted PROGRAM requests for query,
  save/restore/run/delete/reclaim/explicit format. It allocates pages, verifies
  payload CRC and publishes records last. Its old RAM/private addresses conflict
  with the new monitor; it is a source-port reference, not a callable binary.
- `xip/source/utilities.asm` performs SRAM-to-flash transfer with an allocator
  request and confirmation, reloads its manager after staging, and commits the
  flash header after verified restore. A distinct SRAM entry cannot silently be
  represented by SR01. AUTO must preserve these format limits and ownership.
- `inputs/launcher.asm` validates app descriptors, vectors and image CRC before
  selecting the bank or transferring control. The old router/provider addresses
  are not BASE1-compatible. APPS discovery must report compatible availability.
- The b35 BATCH code validates its bounded queue and stops on failure/cancel;
  it also restricts raw loaders/jumps and unregistered program handoff.

Next implement backend-neutral Table/Store/Restore requests with explicit flash
arena and mounted PROGRAM ownership. The shared completion result is ready for
those adapters. BATCH is extended only as the individual workflows acquire
bounded return/confirmation behavior. [Full parity](MON_B35_PARITY.md) remains
the completion gate.

## Build evidence and next trial

[MON manifest](../monitors/candidates/g00000007/manifest.json) and
[WB2 manifest](../monitors/candidates/wb2-g00000001/manifest.json) retain source
hashes, artifact hashes and admission/layout facts. Each component was built
once; no reproduction build, CPU model or offline regression group was run.
Existing-binary hash/CRC/tail checks passed; these do not prove execution.

| Component | Linked bytes | Reserved bytes | Free bytes |
| --- | ---: | ---: | ---: |
| F (4096, frozen) | 3697 | 32 | **367** |
| MON A g7 (4096) | 3932 | 128 | **36** |
| MON B g7 (4096) | 3932 | 128 | **36** |
| WB2 g1 (9216 code block) | 5605 | 2 | **3609** |

The raw WB2 loader BIN is 9472 bytes. Candidate space can be reproduced from
the existing files, without rebuilding:

```text
python tools/monitor_space.py --monitor-manifest monitors/candidates/g00000007/manifest.json --workbench-manifest monitors/candidates/wb2-g00000001/manifest.json
```

The [2512 RAM-only scope](MON_AB_G7_WB2_RAM_SCOPE.md) is the next live gate.
Neither slot is installed before the RAM result is known. F, C/D and all images
remain write-excluded in that scope.
