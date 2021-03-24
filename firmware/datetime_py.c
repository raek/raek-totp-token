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
    long int result = datetime_to_unix_time(year, month, day, hour, minute, second);
    return PyLong_FromLong(result);
}
