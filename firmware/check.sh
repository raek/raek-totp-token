#!/usr/bin/env bash

set -u
set -e

if [[ ! -d .venv ]]; then
    python3 -m venv .venv
fi
source .venv/bin/activate
if [[ -z $(pip list | grep "^pytest") ]]; then
    pip install pytest
fi
python setup.py build install
pytest
