from distutils.sysconfig import get_python_inc
import os
import sys


include_dirs = []

# If in a virtualenv, add its include directory
if sys.exec_prefix != sys.base_exec_prefix:
    include_dirs.append(os.path.join(sys.exec_prefix, "include"))

py_include = get_python_inc()
plat_py_include = get_python_inc(plat_specific=True)
include_dirs.extend(py_include.split(os.path.pathsep))
if plat_py_include != py_include:
    include_dirs.extend(plat_py_include.split(os.path.pathsep))

print(" ".join(f"-I {dir}" for dir in include_dirs), end="")
