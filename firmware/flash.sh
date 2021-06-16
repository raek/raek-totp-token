#!/usr/bin/env bash

# Usage:
#     ./flash <app name> [avrdude args...]
#
# Custom programmer device:
#     DEVICE=/dev/ttyXXX ./flash <app name> [avrdude args...]

set -e
set -u

tup

filename=build/bin.avr/"$1".hex
if [[ ! -f $filename ]]; then
  echo "File does not exist: $filename"
  exit 1
fi
shift

echo "Flashing: $filename"

avrdude -v -p atmega32u4 -c avr109 -P ${DEVICE:-/dev/ttyACM0} -U flash:w:"$filename":i "$@"
