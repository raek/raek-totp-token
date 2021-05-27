#include <stdbool.h>
#include <assert.h>

#include <Python.h>
#include <structmember.h>

#include "inverter.h"
#include "firmware.h"

typedef struct {
    PyObject_HEAD
    PyObject *in_pin;
    PyObject *out_pin;
    Inverter inverter;
} InverterPy;

static PyObject *inverter_py_run(PyObject *self, PyObject *args)
{
    assert(args == NULL);
    InverterPy *inverter_py = (InverterPy *) self;
    inverter_run(&inverter_py->inverter);
    Py_RETURN_NONE;
}

static PyObject *inverter_py_new(PyTypeObject *tp, PyObject *args, PyObject *kwds)
{
    FirmwareState *firmware_state = (FirmwareState *) PyType_GetModuleState(tp);
    PyObject *pin_type = firmware_state->pin_type_object;
    PyObject *in_pin;
    PyObject *out_pin;
    static char *kwlist[] = {"in_pin", "out_pin", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O!O!:Inverter", kwlist,
                                     pin_type, &in_pin, pin_type, &out_pin)) {
        return NULL;
    }
    PyObject *self = tp->tp_alloc(tp, 0);
    if (self == NULL) {
        return NULL;
    }
    InverterPy *inverter_py = (InverterPy *) self;
    inverter_py->in_pin = in_pin;
    Py_INCREF(in_pin);
    inverter_py->out_pin = out_pin;
    Py_INCREF(out_pin);
    inverter_init(&inverter_py->inverter, (Pin *) in_pin, (Pin *) out_pin);
    return self;
};

static void inverter_py_dealloc(PyObject *self)
{
    PyTypeObject *tp = Py_TYPE(self);
    InverterPy *inverter_py = (InverterPy *) self;
    Py_DECREF(inverter_py->in_pin);
    Py_DECREF(inverter_py->out_pin);
    tp->tp_free(self);
    Py_DECREF(tp);
}

static PyMemberDef inverter_py_members[] = {
    {"in_pin", T_OBJECT_EX, offsetof(InverterPy, in_pin), READONLY, NULL},
    {"out_pin", T_OBJECT_EX, offsetof(InverterPy, out_pin), READONLY, NULL},
    {NULL},
};

static PyMethodDef inverter_py_methods[] = {
    {"run", inverter_py_run, METH_NOARGS, NULL},
    {NULL},
};

static PyType_Slot inverter_py_slots[] = {
    {Py_tp_new, inverter_py_new},
    {Py_tp_dealloc, inverter_py_dealloc},
    {Py_tp_members, inverter_py_members},
    {Py_tp_methods, inverter_py_methods},
    {0, NULL},
};

PyType_Spec inverter_type_spec = {
    .name = "firmware.Inverter",
    .basicsize = sizeof(InverterPy),
    .itemsize = 0,
    .flags = Py_TPFLAGS_DEFAULT,
    .slots = inverter_py_slots,
};
