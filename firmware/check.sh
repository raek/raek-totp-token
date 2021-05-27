#!/usr/bin/env bash

set -u
set -e

if [[ ! -d .venv ]]; then
    python3.9 -m venv .venv
fi
source .venv/bin/activate
pip install -r requirements-dev.txt
python setup.py build install
flake8 *.py
mypy --strict .
pytest -v
