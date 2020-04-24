#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <abieos.h>

static PyObject* create(PyObject* self, PyObject *args)
{
    return PyCapsule_New((void*)abieos_create(), "abieos_context", NULL);
}

static PyObject* destroy(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    if (!PyArg_ParseTuple(args, "O", &context_capsule))
        return NULL;

    abieos_destroy(PyCapsule_GetPointer(context_capsule, "abieos_context"));
    return Py_None;
}

static PyObject* get_error(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    if (!PyArg_ParseTuple(args, "O", &context_capsule))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    return Py_BuildValue("s", abieos_get_error(c));
}

static PyObject* get_bin_size(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    if (!PyArg_ParseTuple(args, "O", &context_capsule))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    return Py_BuildValue("i", abieos_get_bin_size(c));
}

static PyObject* get_bin_data(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    if (!PyArg_ParseTuple(args, "O", &context_capsule))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    const char* bin = abieos_get_bin_data(c);
    PyObject* obj = PyBytes_FromStringAndSize(bin, abieos_get_bin_size(c));
    return Py_BuildValue("S", obj);
}

static PyObject* get_bin_hex(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    if (!PyArg_ParseTuple(args, "O", &context_capsule))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    return Py_BuildValue("s", abieos_get_bin_hex(c));
}

static PyObject* string_to_name(PyObject *self, PyObject *args)
{
    PyObject* context_capsule;
    const char *str;
    if (!PyArg_ParseTuple(args, "Os", &context_capsule, &str))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    return Py_BuildValue("K", abieos_string_to_name(c, str));
}

static PyObject* name_to_string(PyObject *self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t name;
    if (!PyArg_ParseTuple(args, "OK", &context_capsule, &name))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    return Py_BuildValue("s", abieos_name_to_string(c, name));
}

static PyObject* set_abi(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    const char *abi;
    if (!PyArg_ParseTuple(args, "OKs", &context_capsule, &contract, &abi))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    abieos_bool result = abieos_set_abi(c, contract, abi);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* set_abi_bin(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    PyObject *abi_buffer;
    size_t size;
    if (!PyArg_ParseTuple(args, "OKSn", &context_capsule, &contract, &abi_buffer, &size))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    const char *abi = PyBytes_AsString(abi_buffer);
    abieos_bool result = abieos_set_abi_bin(c, contract, abi, size);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* set_abi_hex(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    const char *abi;
    if (!PyArg_ParseTuple(args, "OKs", &context_capsule, &contract, &abi))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    abieos_bool result = abieos_set_abi_hex(c, contract, abi);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* get_type_for_action(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    uint64_t action;
    if (!PyArg_ParseTuple(args, "OKK", &context_capsule, &contract, &action))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    return Py_BuildValue("s", abieos_get_type_for_action(c, contract, action));
}

static PyObject* get_type_for_table(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    uint64_t table;
    if (!PyArg_ParseTuple(args, "OKK", &context_capsule, &contract, &table))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    return Py_BuildValue("s", abieos_get_type_for_table(c, contract, table));
}

static PyObject* json_to_bin(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    const char* type;
    const char* json;
    if (!PyArg_ParseTuple(args, "OKss", &context_capsule, &contract, &type, &json))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    abieos_bool result = abieos_json_to_bin(c, contract, type, json);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* json_to_bin_reorderable(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    const char* type;
    const char* json;
    if (!PyArg_ParseTuple(args, "OKss", &context_capsule, &contract, &type, &json))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    abieos_bool result = abieos_json_to_bin_reorderable(c, contract, type, json);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* bin_to_json(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    const char* type;
    PyObject *abi_buffer;
    size_t size;
    if (!PyArg_ParseTuple(args, "OKsSn", &context_capsule, &contract, &type, &abi_buffer, &size))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    const char *abi = PyBytes_AsString(abi_buffer);
    return Py_BuildValue("s", abieos_bin_to_json(c, contract, type, abi, size));
}

static PyObject* hex_to_json(PyObject* self, PyObject *args)
{
    PyObject* context_capsule;
    uint64_t contract;
    const char* type;
    const char* hex;
    if (!PyArg_ParseTuple(args, "OKss", &context_capsule, &contract, &type, &hex))
        return NULL;

    abieos_context* c = PyCapsule_GetPointer(context_capsule, "abieos_context");
    return Py_BuildValue("s", abieos_hex_to_json(c, contract, type, hex));
}

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
