#include <Python.h>

#include "include/partsy.h"

/*
    PARTICLE NODE METHODS/RELATED FUNCTIONS
*/
static void
ParticleNode_dealloc(ParticleNode *self);
static PyObject*
ParticleNode_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
static int
ParticleNode_init(ParticleNode *self, PyObject *args, PyObject *kwargs);


static void
ParticleNode_dealloc(ParticleNode *self) {
    Py_XDECREF(self->particle);
    DEALLOC_SELF(self);
}
