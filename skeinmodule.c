#include <Python.h>

//#include "skeinhash.h"

static PyObject *skein_gethash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    skein_hash((const char *)PyBytes_AsString((PyObject*) input), 
                (size_t)PyBytes_Size((PyObject*) input), output);
#else
    skein_hash((const char *)PyString_AsString((PyObject*) input), 
                (size_t)PyString_Size((PyObject*) input), output);
#endif

    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef SkeinMethods[] = {
    { "getPoWHash", skein_gethash, METH_VARARGS, "Returns a proof of work hash using skein and sha256" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef SkeinModule = {
    PyModuleDef_HEAD_INIT,
    "py_bca_skein",
    "...",
    -1,
    SkeinMethods
};

PyMODINIT_FUNC PyInit_py_bca_skein(void) {
    return PyModule_Create(&SkeinModule);
}

#else

PyMODINIT_FUNC initskeinhash(void) {
    (void) Py_InitModule("skeinhash", SkeinMethods);
}
#endif