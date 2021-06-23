#include <Python.h>

#include "hmac_sha1.h"
#include "firmware.h"

PyObject *hmac_sha1_py(PyObject *self, PyObject *args)
{
    PyObject *key;
    PyObject *message;
    if (!PyArg_ParseTuple(args, "O!O!:hmac_sha1",
                          &PyBytes_Type, &key,
                          &PyBytes_Type, &message)) {
        return NULL;
    }
    HmacSha1 temp;
    uint8_t code[HMAC_SHA1_CODE_BYTES];
    hmac_sha1(&temp,
              (uint8_t *) PyBytes_AsString(key), PyBytes_Size(key),
              (uint8_t *) PyBytes_AsString(message), PyBytes_Size(message),
              code);
    return PyBytes_FromStringAndSize((const char *) code, sizeof(code));
}
