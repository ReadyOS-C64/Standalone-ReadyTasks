#!/bin/bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"

DISK_FILE="${1:-readytasks.d64}"
APP_FILE="${2:-readytasks.prg}"
VICE_CONSOLE="${VICE_CONSOLE:-0}"
VICE_BIN="${VICE_BIN:-}"
VICE_PRG_MODE="${VICE_PRG_MODE:-0}"
VICE_DEBUG="${VICE_DEBUG:-0}"

if [ -n "$VICE_BIN" ]; then
  if ! command -v "$VICE_BIN" >/dev/null 2>&1; then
    echo "Error: VICE_BIN is set to '$VICE_BIN' but that executable is not in PATH." >&2
    exit 1
  fi
  VICE="$VICE_BIN"
elif command -v x64sc >/dev/null 2>&1; then
  VICE="x64sc"
elif command -v x64 >/dev/null 2>&1; then
  VICE="x64"
else
  echo "Error: VICE emulator not found (x64sc or x64)" >&2
  exit 1
fi

if [ ! -f "$DISK_FILE" ]; then
  echo "Error: Disk image not found: $DISK_FILE" >&2
  exit 1
fi

if [ ! -f "$APP_FILE" ]; then
  echo "Error: App PRG not found: $APP_FILE" >&2
  exit 1
fi

CMD=(
  "$VICE"
  -drive8type 1541
  -drive8truedrive
  -devicebackend8 0
  +busdevice8
  -8 "$DISK_FILE"
)

if [ "$VICE_CONSOLE" = "1" ]; then
  CMD+=(-console -sounddev dummy)
fi

if [ "$VICE_PRG_MODE" = "1" ]; then
  CMD+=(-autostartprgmode 1)
fi

CMD+=(-autostart "$APP_FILE")

# Attach disk for app file I/O, and autostart the single standalone PRG.
if [ "$VICE_DEBUG" = "1" ]; then
  printf 'VICE command:' >&2
  printf ' %q' "${CMD[@]}" >&2
  echo >&2
fi

set +e
"${CMD[@]}"
rc=$?
set -e

if [ "$rc" -ne 0 ]; then
  echo >&2
  echo "Error: VICE failed to launch (exit code: $rc)." >&2
  echo "Troubleshooting:" >&2
  echo "  - Force a specific emulator binary: VICE_BIN=x64 make run" >&2
  echo "  - Try console mode in headless terminals: VICE_CONSOLE=1 make run" >&2
  echo "  - Toggle PRG inject mode explicitly: VICE_PRG_MODE=1 make run" >&2
  echo "  - Print the exact launch command: VICE_DEBUG=1 make run" >&2
  echo "  - If GTK/GSettings errors appear, run from a desktop GUI session or install an SDL-capable VICE build." >&2
fi

exit "$rc"
