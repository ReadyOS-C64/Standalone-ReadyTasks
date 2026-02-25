#!/bin/bash
set -euo pipefail

APP_FILE="${1:-readytasks.prg}"
DISK_FILE="${2:-readytasks.d64}"
README_FILE="${3:-disk/readme.seq}"
DISK_NAME="readytasks,st"
DISK_ENTRY="readytasks"
README_ENTRY="readme,s"

if ! command -v c1541 >/dev/null 2>&1; then
  echo "Error: c1541 not found in PATH" >&2
  exit 1
fi

if [ ! -f "$APP_FILE" ]; then
  echo "Error: app PRG not found: $APP_FILE" >&2
  exit 1
fi

if [ ! -f "$README_FILE" ]; then
  echo "Error: README SEQ not found: $README_FILE" >&2
  exit 1
fi

c1541 -format "$DISK_NAME" d64 "$DISK_FILE" \
  -write "$APP_FILE" "$DISK_ENTRY" \
  -write "$README_FILE" "$README_ENTRY"

echo ""
echo "Disk contents ($DISK_FILE):"
c1541 "$DISK_FILE" -list
