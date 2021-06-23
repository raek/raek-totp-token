#include <Python.h>

#include "sha1.h"
#include "firmware.h"

typedef struct {
    PyObject_HEAD
    Sha1 sha1;
} Sha1Py;

static int sha1_py_init(PyObject *self, PyObject *args, PyObject *kwds)
{
    Sha1Py *sha1_py = (Sha1Py *) self;
    static char *kwlist[] = {NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, ":Sha1", kwlist)) {
        return -1;
    }
    sha1_init(&sha1_py->sha1);
    return 0;
}

static PyObject *sha1_py_update(PyObject *self, PyObject *args)
{
    Sha1Py *sha1_py = (Sha1Py *) self;
    PyObject *chunk;
    if (!PyArg_ParseTuple(args, "O!:update", &PyBytes_Type, &chunk)) {
        return NULL;
    }
    sha1_update(&sha1_py->sha1, (uint8_t *) PyBytes_AsString(chunk), PyBytes_Size(chunk));
    Py_RETURN_NONE;
}

static PyObject *sha1_py_digest(PyObject *self, PyObject *args)
{
    Sha1Py *sha1_py = (Sha1Py *) self;
    if (!PyArg_ParseTuple(args, ":digest")) {
        return NULL;
    }
    uint8_t buffer[SHA1_DIGEST_BYTES];
    sha1_digest(&sha1_py->sha1, buffer);
    return PyBytes_FromStringAndSize((const char *) buffer, sizeof(buffer));
}

static PyMethodDef sha1_py_methods[] = {
    {"update", sha1_py_update, METH_VARARGS, NULL},
    {"digest", sha1_py_digest, METH_VARARGS, NULL},
    {NULL},
};

static PyType_Slot sha1_py_slots[] = {
    {Py_tp_init, sha1_py_init},
    {Py_tp_methods, sha1_py_methods},
    {0, NULL},
};

PyType_Spec sha1_type_spec = {
    .name = "firmware.Sha1",
    .basicsize = sizeof(Sha1Py),
    .itemsize = 0,
    .flags = Py_TPFLAGS_DEFAULT,
    .slots = sha1_py_slots,
};
