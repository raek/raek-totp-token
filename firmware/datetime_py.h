#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "datetime.h"

PyObject *datetime_to_unix_time_py(PyObject *self, PyObject *args);
