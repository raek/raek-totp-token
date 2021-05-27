#include <assert.h>

#include <Python.h>

#include "firmware.h"

static PyMethodDef firmware_methods[] = {
    {"datetime_is_valid", datetime_is_valid_py, METH_VARARGS, NULL},
    {"datetime_to_unix_time", datetime_to_unix_time_py, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static int firmware_exec(PyObject *module)
{
    FirmwareState *state = PyModule_GetState(module);
    if (state == NULL) {
        return -1;
    }
    memset(state, 0, sizeof(*state));

    state->pin_type_object = PyType_FromModuleAndSpec(module, &pin_type_spec, NULL);
    if (state->pin_type_object == NULL) {
        return -1;
    }
    if (PyModule_AddType(module, (PyTypeObject *) state->pin_type_object) < 0) {
        return -1;
    }

    state->inverter_type_object = PyType_FromModuleAndSpec(module, &inverter_type_spec, NULL);
    if (state->inverter_type_object == NULL) {
        return -1;
    }
    if (PyModule_AddType(module, (PyTypeObject *) state->inverter_type_object) < 0) {
        return -1;
    }

    state->sha1_type_object = PyType_FromModuleAndSpec(module, &sha1_type_spec, NULL);
    if (state->sha1_type_object == NULL) {
        return -1;
    }
    if (PyModule_AddType(module, (PyTypeObject *) state->sha1_type_object) < 0) {
        return -1;
    }

    return 0;
}

static int firmware_traverse(PyObject *module, visitproc visit, void *arg)
{
    FirmwareState *state = PyModule_GetState(module);
    if (state == NULL) {
        return 0;
    }
    Py_VISIT(state->pin_type_object);
    Py_VISIT(state->inverter_type_object);
    Py_VISIT(state->sha1_type_object);
    return 0;
}

static int firmware_clear(PyObject *module)
{
    FirmwareState *state = PyModule_GetState(module);
    if (state == NULL) {
        return 0;
    }
    Py_CLEAR(state->pin_type_object);
    Py_CLEAR(state->inverter_type_object);
    Py_CLEAR(state->sha1_type_object);
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
    .m_traverse = firmware_traverse,
    .m_clear = firmware_clear,
    .m_free = NULL,
};

PyMODINIT_FUNC PyInit_firmware(void)
{
    return PyModuleDef_Init(&firmware_module_def);
}
