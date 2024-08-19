#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject*
partsy_init(PyObject* self, PyObject* args) {

    printf("PartSy 0.0.1v is initialized\n");

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef partsy_methods[] = {
    {"init", partsy_init, METH_VARARGS, "a simple function to check if the module is working"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef patsy_module = {
    PyModuleDef_HEAD_INIT,
    "partsy",
    NULL,
    -1,
    partsy_methods
};

PyMODINIT_FUNC
PyInit_partsy(void) {
    return PyModule_Create(&patsy_module);
}
