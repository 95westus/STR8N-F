# BASE1 build and freeze policy

`python tools/verify_base1.py` checks existing files only. It does not assemble,
emulate, open a port or flash a device. Historical CPU reports are not current
BASE1 qualification.

The identity build compiled F once and built affected CONFIG, OPAQUE, DEMO,
MAP and READBACK against it. Worker/vector images were unchanged; NFM1/NFA1
were reused. No reproduction build or CPU model ran.

F_FREEZE.json now locks F. For a later source change requiring RAM assembly:

```text
python tools/build_base1.py --only map --out build/new-map
```

Selections: config, opaque, demo, map, readback. Use a fresh output directory.
Unselected payloads and frozen F are reused with hashes checked. Inspect the
output manifest before promoting changed RAM files. WDC tools are required
only for actual assembly; no installation or publication is automatic.

Old F/full-system builder paths are retired or redirect to the canonical RAM
builder. Initial-F mode is already consumed. A future boot defect needs a new,
reviewed F generation and reference proof, not an override of this lock.
