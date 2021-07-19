#!/usr/bin/env bash

set -u
set -e

if [[ ! -d .venv ]]; then
    python3.9 -m venv .venv
fi
source .venv/bin/activate
pip install -r requirements-dev.txt

tup
flake8 *.py
mypy --strict --allow-untyped-decorators .

rm -rf *.gcda
rm -rf *.gcov
pytest -v -k "not test_prop_"
rm -rf coverage
mkdir coverage
gcovr --print-summary --html-details -o coverage/index.html
gcov *.gcda

pytest -v -k "test_prop_"
