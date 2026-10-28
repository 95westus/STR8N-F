# STR8N-F 0.3.0 â€” BASE1 / PR05

F generation 00000001 is source/binary frozen. This toolkit is an unpublished
candidate with hardware acceptance pending. No board was modified to prepare it.

The kit includes a Python serial console with function-key file sending:

```text
python -m pip install -r requirements-console.txt
python tools/nf_console.py
```

F10 connects to the selected port. At REC>, F2 chooses a RAM BIN and F4 sends
it after SEND BIN; F5-F8 load MAP, CONFIG, OPAQUE and DEMO directly. Each has
a button. See the [console guide](docs/SERIAL_CONSOLE.md) for all keys,
Ctrl-C rules and the pending hardware acceptance checks.

Startup prints:

```text
STR8N-F 0.3.0 g00000001
BASE1 / PR05
```

F then offers its boot/recovery chooser. OS identity and board/service status
belong to the image after handoff. No EDU, RTC or SRAM scan is added to F.

The programmer file is `firmware/payload/STR8N-F-BOOT-4096.bin`, exactly 4096
bytes for B3:F. Use your programmer/device's verified mapping. No full-device
image is supplied. C/D hold the journal; B0-B2 and B3:8/9/A/B/E are owner image
space. No MON, provider or automatic B0 backup copy is required. Programming
F alone does not convert occupied vendor C/D into journals.

F_FREEZE.json and identity.json describe the frozen image. The included
[identity contract](docs/F_IDENTITY.md) defines discovery. The exact file SHA
is in the manifests/checksum file; do not patch embedded identity text.

The new MAP RAM tool loads through recovery L. M 1 shows the two-character
grid; M 2 adds identification detail; M 3 adds wear counts. W+ is a known WDC
resident match and W? is possible WDC. Neither validates the whole bank or
proves a successful boot. WDC generation is --. See [RAM map](docs/RAM_MAP.md).

The [migration guide](migration-host/README.md) describes the verbose WDC RAM
route, private backups, physical-reset checks, independent flash readback and
owner-RAM restoration. The new live command remains behind explicit
--allow-unqualified; hardware has not accepted it. Python 3.11+ and pyserial
are needed only for a later live trial. Templates are host inputs, not generic
unconditionally executable installation files.

Use matching BASE1 CONFIG, OPAQUE and READBACK. [OPAQUE host](docs/OPAQUE_HOST.md)
reads/backs up, replaces and independently verifies a selected image sector;
C/D/F remain protected. CONFIG separately saves bank entry/default. The
[current limits](docs/ISSUES_RESOLVED.md) include hardware acceptance,
existing-journal F upgrades and generic live F-recovery provisioning.
