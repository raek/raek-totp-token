#!/usr/bin/env bash

set -e
set -u

# Mandatory inlining
if 1>&2 grep pin_ "$1"; then
    1>&2 echo "Non-inlined occurrences found!"
    exit 1
fi
