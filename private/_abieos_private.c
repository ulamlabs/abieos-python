#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "abieos.c"

static PyMethodDef AbieosMethods[] = {
    // create and destroy context
    {"create", create, METH_NOARGS, ""},
    {"destroy", destroy, METH_VARARGS, ""},

    {"get_error", get_error, METH_VARARGS, ""},
    {"get_bin_size", get_bin_size, METH_VARARGS, ""},
    {"get_bin_data", get_bin_data, METH_VARARGS, ""},
    {"get_bin_hex", get_bin_hex, METH_VARARGS, ""},
    {"string_to_name", string_to_name, METH_VARARGS, ""},
    {"name_to_string", name_to_string, METH_VARARGS, ""},
    {"set_abi", set_abi, METH_VARARGS, ""},
    {"set_abi_bin", set_abi_bin, METH_VARARGS, ""},
    {"set_abi_hex", set_abi_hex, METH_VARARGS, ""},
    {"get_type_for_action", get_type_for_action, METH_VARARGS, ""},
    {"get_type_for_table", get_type_for_table, METH_VARARGS, ""},
    {"json_to_bin", json_to_bin, METH_VARARGS, ""},
    {"json_to_bin_reorderable", json_to_bin_reorderable, METH_VARARGS, ""},
    {"bin_to_json", bin_to_json, METH_VARARGS, ""},
    {"hex_to_json", hex_to_json, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef abieos = {
    PyModuleDef_HEAD_INIT,
    "_private",
    NULL,
    -1,
    AbieosMethods
};

PyMODINIT_FUNC
PyInit__private(void)
{
    PyObject *m;

    m = PyModule_Create(&abieos);
    if (m == NULL)
        return NULL;

    return m;
}
