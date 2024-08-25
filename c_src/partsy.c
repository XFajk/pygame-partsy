#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "include/partsy.h"

static PyObject*
partsy_init(PyObject* self, PyObject* args) {

    printf("PartSy 0.0.1v is initialized\n");

    Py_RETURN_NONE;
}

static PyMethodDef partsy_methods[] = {
    {"init", (PyCFunction)partsy_init, METH_VARARGS, "a simple function to check if the module is working"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef patsy_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "partsy",
    "this C extension for python brings a blazingly fast and customizable particle system to pygame developers",
    -1,
    partsy_methods
};

PyMODINIT_FUNC
PyInit_partsy(void) {
    PyObject *m;
    if (PyType_Ready(&ParticleType) < 0) {
        return NULL;
    }

    m = PyModule_Create(&patsy_module);
    if (m == NULL)
        return NULL;

    if (PyModule_AddObjectRef(m, "Particle", (PyObject *) &ParticleType) < 0) {
         Py_DECREF(m);
         return NULL;
     }

    return m;
}
