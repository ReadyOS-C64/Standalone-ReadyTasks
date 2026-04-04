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

## Download C64 Binaries
- [READY TASKS (.D64)](readytasks.d64)
- [READY TASKS (.PRG)](readytasks.prg)

## Screenshots

  <img width="711" height="538" alt="image" src="https://github.com/user-attachments/assets/0ffdb4a2-6520-4789-8d3b-9984722ccd86" />

  <img width="706" height="536" alt="image" src="https://github.com/user-attachments/assets/8bcc55fa-23e1-462d-a8b2-550b65e49b5e" />

  <img width="713" height="536" alt="image" src="https://github.com/user-attachments/assets/a6510f15-dedb-4cc1-b713-085130c0f077" />

  <img width="713" height="541" alt="image" src="https://github.com/user-attachments/assets/83ea8961-9a55-46a1-be95-8ceac52fa44f" />

## Requirements

- `cc65` (`cl65`)
- `c1541` (VICE tools) - to build a D64 automatically
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

Console mode (for headless terminals):

```bash
make run-console
```

You can also force the emulator binary:

```bash
VICE_BIN=x64 make run
```

Optional PRG inject mode (off by default to match ReadyOS run behavior):

```bash
VICE_PRG_MODE=1 make run
```

Print the exact VICE command for debugging:

```bash
VICE_DEBUG=1 make run
```

### Run Troubleshooting

- If `make run` fails with GTK/GSettings errors, your installed VICE binary is likely a GUI build that needs a desktop session.
- Try `make run-console` first.
- If `x64sc` fails, try `VICE_BIN=x64 make run`.
- If launch behavior differs from ReadyOS, leave `VICE_PRG_MODE` unset (default `0`).

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
