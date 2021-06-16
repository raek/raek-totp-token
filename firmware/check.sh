#!/usr/bin/env bash

set -u
set -e

tup
if [[ ! -d .venv ]]; then
    python3.9 -m venv .venv
fi
source .venv/bin/activate
pip install -r requirements-dev.txt
python setup.py build install
flake8 *.py
mypy --strict .
rm -rf build/temp.*/*.gcda
rm -rf *.gcov
pytest -v
rm -rf coverage
mkdir coverage
gcovr --print-summary --html-details -o coverage/index.html
gcov build/temp.*/*.o
