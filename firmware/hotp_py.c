#include <Python.h>

#include "hotp.h"
#include "firmware.h"

PyObject *hotp_py(PyObject *self, PyObject *args)
{
    PyObject *secret;
    unsigned long long counter;
    if (!PyArg_ParseTuple(args, "O!K:hotp", &PyBytes_Type, &secret, &counter)) {
        return NULL;
    }
    Hotp scratchpad;
    char digits[HOTP_DIGITS];
    hotp(&scratchpad,
         (uint8_t *) PyBytes_AsString(secret), PyBytes_Size(secret),
         counter, digits);
    return PyUnicode_FromStringAndSize(digits, sizeof(digits));
}
