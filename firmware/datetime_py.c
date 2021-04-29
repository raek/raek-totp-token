#include <stdint.h>

#include <Python.h>

#include "datetime.h"
#include "firmware.h"

PyObject *datetime_is_valid_py(PyObject *self, PyObject *args)
{
    long int year, month, day, hour, minute, second;
    if (!PyArg_ParseTuple(args, "llllll:datetime_is_valid", &year, &month, &day, &hour, &minute, &second)) {
        return NULL;
    }
    bool ok = datetime_is_valid(year, month, day, hour, minute, second);
    if (ok) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject *datetime_to_unix_time_py(PyObject *self, PyObject *args)
{
    long int year, month, day, hour, minute, second;
    if (!PyArg_ParseTuple(args, "llllll:datetime_to_unix_time", &year, &month, &day, &hour, &minute, &second)) {
        return NULL;
    }
    UnixTime result = 0;
    bool ok = datetime_to_unix_time(&result, year, month, day, hour, minute, second);
    if (ok) {
        return PyLong_FromLong(result);
    } else {
        Py_RETURN_NONE;
    }
}
