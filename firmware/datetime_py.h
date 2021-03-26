#pragma once

#include <Python.h>

#include "datetime.h"

PyObject *datetime_is_valid_py(PyObject *self, PyObject *args);
PyObject *datetime_to_unix_time_py(PyObject *self, PyObject *args);
