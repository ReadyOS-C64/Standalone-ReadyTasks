#!/bin/bash
set -euo pipefail

DISK_FILE="${1:-readytasks.d64}"
APP_FILE="${2:-readytasks.prg}"

if command -v x64sc >/dev/null 2>&1; then
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

# Attach disk for app file I/O, and autostart the single standalone PRG.
"$VICE" \
  -drive8type 1541 \
  -drive8truedrive \
  -devicebackend8 0 \
  +busdevice8 \
  -8 "$DISK_FILE" \
  -autostartprgmode 1 \
  -autostart "$APP_FILE"
