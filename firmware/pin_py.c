#include <Python.h>
#include <structmember.h>

#include "pin.h"
#include "firmware.h"

struct Pin {
    PyObject_HEAD
    // These ought to be bools, but T_BOOL attributes require chars
    char dir_is_output;
    char output;
    char input;
};

void pin_set_dir(Pin *pin, bool output)
{
    pin->dir_is_output = (char) output;
}

void pin_write(Pin *pin, bool state)
{
    pin->output = (char) state;
}

bool pin_read(Pin *pin)
{
    return (bool) pin->input;
}

static PyMemberDef pin_type_members[] = {
    {"dir_is_output", T_BOOL, offsetof(Pin, dir_is_output), READONLY, NULL},
    {"output", T_BOOL, offsetof(Pin, output), READONLY, NULL},
    {"input", T_BOOL, offsetof(Pin, input), 0, NULL},
    {NULL},
};

static PyType_Slot pin_type_slots[] = {
    {Py_tp_members, pin_type_members},
    {0, NULL},
};

PyType_Spec pin_type_spec = {
    .name = "firmware.Pin",
    .basicsize = sizeof(Pin),
    .itemsize = 0,
    .flags = Py_TPFLAGS_DEFAULT,
    .slots = pin_type_slots,
};
