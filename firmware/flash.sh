#!/usr/bin/env bash

# Usage:
#     ./flash <filename.hex> [avrdude args...]
#
# Custom programmer device:
#     DEVICE=/dev/ttyXXX ./flash <filename.hex> [avrdude args...]

set -e
set -u

filename="$1"
if [[ ! -f $filename ]]; then
  echo "File does not exist: $filename"
  exit 1
fi
shift

echo "Flashing: $filename"

avrdude -v -p atmega32u4 -c avr109 -P ${DEVICE:-/dev/ttyACM0} -U flash:w:"$filename":i "$@"
