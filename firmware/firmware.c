#include <assert.h>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "datetime_py.h"

typedef struct {
    int dummy;
} FirmwareState;

static FirmwareState *firmware_get_state(PyObject *module)
{
    FirmwareState *state = PyModule_GetState(module);
    assert(state != NULL);
    return state;
}

static PyMethodDef firmware_methods[] = {
    {"datetime_is_valid", datetime_is_valid_py, METH_VARARGS, NULL},
    {"datetime_to_unix_time", datetime_to_unix_time_py, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static int firmware_exec(PyObject *module)
{
    FirmwareState *state = firmware_get_state(module);
    state->dummy = 0;
    return 0;
}

static PyModuleDef_Slot firmware_slots[] = {
    {Py_mod_exec, firmware_exec},
    {0, NULL}
};

static PyModuleDef firmware_module_def = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "firmware",
    .m_doc = "Wrapper to run TOTP hardware token firmare C code",
    .m_size = sizeof(FirmwareState),
    .m_methods = firmware_methods,
    .m_slots = firmware_slots,
    .m_traverse = NULL,
    .m_clear = NULL,
    .m_free = NULL,
};

PyMODINIT_FUNC PyInit_firmware(void)
{
    return PyModuleDef_Init(&firmware_module_def);
}
