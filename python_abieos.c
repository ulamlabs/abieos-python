#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "external/abieos/src/abieos.h"

static abieos_context* _get_context(PyObject* self)
{
    PyObject *capsule = PyObject_GetAttr(self, Py_BuildValue("s", "context"));
    return PyCapsule_GetPointer(capsule, "abieos_context");
}

static PyObject* create(PyObject* self, PyObject *args)
{
    PyObject_SetAttr(
        self,
        Py_BuildValue("s", "context"),
        PyCapsule_New((void*)abieos_create(), "abieos_context", NULL)
    );
    return Py_None;
}

static PyObject* destroy(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);
    abieos_destroy(c);
    PyObject_SetAttr(self, Py_BuildValue("s", "context"), NULL);
    return Py_None;
}

static PyObject* get_error(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);
    return Py_BuildValue("s", abieos_get_error(c));
}

static PyObject* get_bin_size(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);
    return Py_BuildValue("i", abieos_get_bin_size(c));
}

static PyObject* get_bin_data(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);
    const char* bin = abieos_get_bin_data(c);
    PyObject* obj = PyBytes_FromStringAndSize(bin, abieos_get_bin_size(c));
    return Py_BuildValue("S", obj);
}

static PyObject* get_bin_hex(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);
    return Py_BuildValue("s", abieos_get_bin_hex(c));
}

static PyObject* string_to_name(PyObject *self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    const char *str;
    if (!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    return Py_BuildValue("K", abieos_string_to_name(c, str));
}

static PyObject* name_to_string(PyObject *self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t name;
    if (!PyArg_ParseTuple(args, "K", &name))
        return NULL;

    return Py_BuildValue("s", abieos_name_to_string(c, name));
}

static PyObject* set_abi(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    const char *abi;
    if (!PyArg_ParseTuple(args, "Ks", &contract, &abi))
        return NULL;

    abieos_bool result = abieos_set_abi(c, contract, abi);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* set_abi_bin(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    PyObject *abi_buffer;
    size_t size;
    if (!PyArg_ParseTuple(args, "KSn", &contract, &abi_buffer, &size))
        return NULL;

    const char *abi = PyBytes_AsString(abi_buffer);
    abieos_bool result = abieos_set_abi_bin(c, contract, abi, size);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* set_abi_hex(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    const char *abi;
    if (!PyArg_ParseTuple(args, "Ks", &contract, &abi))
        return NULL;

    abieos_bool result = abieos_set_abi_hex(c, contract, abi);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* get_type_for_action(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    uint64_t action;
    if (!PyArg_ParseTuple(args, "KK", &contract, &action))
        return NULL;

    return Py_BuildValue("s", abieos_get_type_for_action(c, contract, action));
}

static PyObject* get_type_for_table(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    uint64_t table;
    if (!PyArg_ParseTuple(args, "KK", &contract, &table))
        return NULL;

    return Py_BuildValue("s", abieos_get_type_for_table(c, contract, table));
}

static PyObject* json_to_bin(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    const char* type;
    const char* json;
    if (!PyArg_ParseTuple(args, "Kss", &contract, &type, &json))
        return NULL;

    abieos_bool result = abieos_json_to_bin(c, contract, type, json);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* json_to_bin_reorderable(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    const char* type;
    const char* json;
    if (!PyArg_ParseTuple(args, "Kss", &contract, &type, &json))
        return NULL;

    abieos_bool result = abieos_json_to_bin_reorderable(c, contract, type, json);
    return result == 1 ? Py_True : Py_False;
}

static PyObject* bin_to_json(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    const char* type;
    PyObject *abi_buffer;
    size_t size;
    if (!PyArg_ParseTuple(args, "KsSn", &contract, &type, &abi_buffer, &size))
        return NULL;

    const char *abi = PyBytes_AsString(abi_buffer);
    return Py_BuildValue("s", abieos_bin_to_json(c, contract, type, abi, size));
}

static PyObject* hex_to_json(PyObject* self, PyObject *args)
{
    abieos_context* c = _get_context(self);

    uint64_t contract;
    const char* type;
    const char* hex;
    if (!PyArg_ParseTuple(args, "Kss", &contract, &type, &hex))
        return NULL;

    return Py_BuildValue("s", abieos_hex_to_json(c, contract, type, hex));
}