import argparse
import re
import sys

from cffi import FFI  # type: ignore


parser = argparse.ArgumentParser()
parser.add_argument("-m", "--module-name",  required=True)
parser.add_argument("-f", "--header-file",  required=True)
parser.add_argument("-i", "--preproc-file", required=True)
parser.add_argument("-c", "--callbacks-file", required=False)
parser.add_argument("-o", "--output-file",  required=True)
args = parser.parse_args()

if args.callbacks_file:
    with open(args.callbacks_file, "rt", encoding="utf-8") as f:
        callbacks = set(line.strip() for line in f)
    callbacks_regex = "(" + "|".join(re.escape(c) for c in callbacks) + ")"

with open(args.preproc_file, "rt", encoding="utf-8") as f:
    declarations = f.read()
# Remove compiler-defined macros and other special macros
declarations = re.sub(r"^#define (__\w+__|CFFI).*$",
                      "",
                      declarations,
                      flags=re.MULTILINE)
# Make macro value always be "..."
declarations = re.sub(r"^(#define \w+).*$",
                      lambda m: m.group(1) + " ...",
                      declarations,
                      flags=re.MULTILINE)
# Mark callbacks with special CFFI syntax
if args.callbacks_file:
    declarations = re.sub(r"^(.*\b" + callbacks_regex + r"\b.*)$",
                          lambda m: 'extern "Python+C" ' + m.group(1),
                          declarations,
                          flags=re.MULTILINE)
# Remove empty lines
declarations = re.sub(r"^\s*$\n",
                      "",
                      declarations,
                      flags=re.MULTILINE)

try:
    builder = FFI()
    builder.cdef(declarations)
    builder.set_source(args.module_name, f'#include "{args.header_file}"')
    builder.emit_c_code(args.output_file)

except Exception as e:
    for lineno, line in enumerate(declarations.split("\n"), start=1):
        print(f"{lineno:3d}: {line}")
    print(e)
    sys.exit(1)
