import argparse
import re

from cffi import FFI  # type: ignore


parser = argparse.ArgumentParser()
parser.add_argument("-m", "--module-name",  required=True)
parser.add_argument("-f", "--header-file",  required=True)
parser.add_argument("-i", "--preproc-file", required=True)
parser.add_argument("-c", "--callbacks-file", required=True)
parser.add_argument("-o", "--output-file",  required=True)
args = parser.parse_args()

with open(args.callbacks_file, "rt", encoding="utf-8") as f:
    callbacks = set(line.strip() for line in f)
callbacks_regex = "(" + "|".join(re.escape(c) for c in callbacks) + ")"

with open(args.preproc_file, "rt", encoding="utf-8") as f:
    declarations = f.read()
# Remove compiler-defined macros
declarations = re.sub(r"^#define __\w+__",
                      "",
                      declarations,
                      flags=re.MULTILINE)
# Make macro value always be "..."
declarations = re.sub(r"^(#define \w+).*$",
                      lambda m: m.group(1) + " ...",
                      declarations,
                      flags=re.MULTILINE)
# Mark callbacks with special CFFI syntax
declarations = re.sub(r"^(.*\b" + callbacks_regex + r"\b.*)$",
                      lambda m: 'extern "Python+C" ' + m.group(1),
                      declarations,
                      flags=re.MULTILINE)

builder = FFI()
builder.cdef(declarations)
builder.set_source(args.module_name, f'#include "{args.header_file}"')
builder.emit_c_code(args.output_file)
