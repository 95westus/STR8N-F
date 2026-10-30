# Board services: conserve space and extend without changing F

Owner direction, 2026-10-29: continue with an extensible layout that conserves
flash/RAM; update 2512 as needed. F remains the exact frozen 4096-byte foundation.

## Roles and current increment

- MON A/B stay identical. M1 and W remain direct Bx> commands.
- B3:E is the optional extension dispatcher, not a new dependency of F.
  Read-only map/wear views execute there using scratch 6700-69FF. They neither
  load the workbench nor borrow owner RAM 0200-66FF or owner ZP 00-DF.
- The B2:8/9 bundle stores the larger tool and its bank-safe RAM loader. It
  uses two sectors, leaving B0/B1 and remaining assets untouched. Only explicit
  MAINT/CLOCK/FLASH invocation may load it; an ordinary map or unknown command
  cannot silently claim application RAM.
- The refined WB2 layout is 4800-63FF, with state 6400-66FF and application RAM
  0200-47FF while loaded. This saves 2KB against the earlier 4000-base prototype.
  The RAM bank-switch loader fits one 256-byte page at 7000, clear of the frozen
  7800-7BE7 worker. Restoring owner RAM evicts the tool; it reloads from flash.
- New read-only CLOCK reuses the qualified bounded RTC adapter. Advanced CLOCK
  administration and the legacy source/ASM/debugger/provider ports remain open.
  FLASH currently opens the workbench; it is not yet the complete editor below.

Use a shared dispatcher/parser/backend for views exposed in more than one menu.
Prefer flash execution for read-only code. Keep the bank-switch/busy kernels
in RAM and budget buffers only while a tool owns them. No automatic owner-sector
allocation, SRAM formatting or PROGRAM/WORKSPACE adoption is implied by a menu.
New command/provider generations do not change F's generation or public ABI.

## FLASH sector editor: accepted direction, still planned

Select an exact bank and 4KB sector, then read its 4096 bytes into a declared RAM
buffer. Display sixteen 16-byte rows per page, with hex/ASCII, next/previous
pages and row/column editing. Row 12/column A means offset 12A. Provide modify,
fill, copy, compare and reload/discard before an explicit program request.

Before programming, compare with the current sector and show changed bytes
and whether 0->1 transitions require erase/rewrite. Preserve unchanged sector
bytes during rewrite. Offer an explicit erase-only operation and verify all
results. Every actual erase attempt is journal-reserved before the chip command;
busy polling/program/erase/verify runs from RAM. Completion must not return
into code that the operation has replaced.

Override may relax format/ownership guards only for a specifically selected
admitted target. B3:C/D/F remain protected. Controlled monitor/service updates
retain their separate binding/accounting and recovery rules. The 4KB buffer is
temporary maintenance ownership, not a permanent startup reservation. Source,
compiler output and captured debugger context must not be overwritten silently.

## MAINT and CONFIG: one front end, explicit transactions

The intended MAINT menu contains status/map/wear, FLASH, boot CONFIG,
EDU/SRAM and CLOCK/board settings. M1/W stay directly callable as well.
Navigation can be shared; saving a boot preference, changing the RTC and
programming a sector remain distinct checked operations with visible targets.

Boot enable/entry/default/delay and wear history remain in C/D. Other board
messages/metadata use a separately admitted append-only SSRAM WORKSPACE
allocation when available, outside PROGRAM and source storage. Absent or
unmounted EDU/SSRAM returns a bounded error, never implicit formatting or
fallback writes into PROGRAM. Flash stores the tools so a host is optional
for ordinary use; the Python terminal remains console/file-transfer support.

The [full b35 parity checklist](MON_B35_PARITY.md) remains the completion gate.
The current [2512 scope](MON_AB_G8_2512_SCOPE.md) covers the small concrete
increment, not every planned page or advanced legacy operation.
