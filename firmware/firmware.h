#pragma once

#include <Python.h>

typedef struct {
    int dummy;
} FirmwareState;

PyObject *datetime_is_valid_py(PyObject *self, PyObject *args);
PyObject *datetime_to_unix_time_py(PyObject *self, PyObject *args);
