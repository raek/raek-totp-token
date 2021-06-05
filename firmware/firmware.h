#pragma once

#include <Python.h>

typedef struct {
    PyObject *pin_type_object;
    PyObject *inverter_type_object;
    PyObject *sha1_type_object;
} FirmwareState;

PyObject *datetime_is_valid_py(PyObject *self, PyObject *args);
PyObject *datetime_to_unix_time_py(PyObject *self, PyObject *args);

extern PyType_Spec pin_type_spec;

extern PyType_Spec inverter_type_spec;

extern PyType_Spec sha1_type_spec;

PyObject *hmac_sha1_py(PyObject *self, PyObject *args);

PyObject *hotp_py(PyObject *self, PyObject *args);
