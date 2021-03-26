#include <stdint.h>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "datetime.h"
#include "datetime_py.h"

PyObject *datetime_to_unix_time_py(PyObject *self, PyObject *args)
{
    long int year, month, day, hour, minute, second;
    if (!PyArg_ParseTuple(args, "llllll", &year, &month, &day, &hour, &minute, &second)) {
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
