# ReadyTasks (C64)

ReadyTasks is a standalone Commodore 64 task outliner extracted from ReadyOS.

- Project site: https://readyos.notion.site
- License: MIT (see `LICENSE`)
- Copyright: (C) Karl Prosser 2026

## Features

- Hierarchical task list with indent/outdent
- Done toggles and progress counters
- Inline note editor per task
- Search across task text and note text
- Local static clipboard (copy/paste task + notes)
- File open/save compatible with ReadyOS Task List text format
- Black-background tuned TUI theme

## Requirements

- `cc65` (`cl65`)
- `c1541` (VICE tools) - to buld a D64 automatically
- `x64sc` or `x64` (VICE emulator) or another to run locally.

## Build

```bash
make
```

Outputs:

- `readytasks.prg`
- map file at `obj/readytasks.map`

## Build D64

```bash
make d64
```

Writes `readytasks` into `readytasks.d64`.

## Run In VICE

```bash
make run
```

Equivalent:

```bash
./scripts/run_vice.sh readytasks.d64 readytasks.prg
```

## Manual C64 Flow

```basic
LOAD"readytasks",8
LIST
RUN
```

## Controls

- `UP/DOWN/HOME/+/-`: navigation
- `RETURN`: insert new task
- `DEL`: delete task
- `SPACE`: toggle done
- `]` / `[` : indent / outdent
- `E`: edit task text
- `N`: edit task note
- `/`: search
- `F1` / `F3`: copy / paste
- `F5` / `F6` / `F7`: save / save as / open
- `F8`: help popup
- `RUN/STOP`: exit

## File Format

ReadyTasks uses the same line format as ReadyOS Task List:

- `indent done text` for tasks
- `>note line` for note lines belonging to the preceding task

This keeps files interoperable between ReadyTasks and ReadyOS.
