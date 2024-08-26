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


static Particle*
ParticleNode_getParticle(ParticleNode *self, void *_closure);
static int
ParticleNode_setParticle(ParticleNode *self, Particle *value, void *_closure);

static ParticleNode*
ParticleNode_getNextNode(ParticleNode *self, void *_closure);
static int
ParticleNode_setNextNode(ParticleNode *self, ParticleNode *value, void *_closure);

static ParticleNode*
ParticleNode_getLastNode(ParticleNode *self, void *_closure);
static int
ParticleNode_setLastNode(ParticleNode *self, ParticleNode *value, void *_closure);

// C API functions
int
_particle_node_set_particle(ParticleNode *self, Particle* new_particle) {
    if (new_particle == NULL) {
        PyErr_SetString(PyExc_MemoryError, "the value provided to ParticleNode.particle was NULL");
        return -1;
    }
    if (!Particle_Check(new_particle)) {
        PyErr_SetString(PyExc_TypeError, "the value provided to the ParticleNode.particle was not of type Particle");
        return -1;
    }

    Py_XDECREF(self->particle); // removing owner ship of the previouse value
    Py_INCREF(new_particle); // adding owner ship
    self->particle = new_particle;

    return 0;
}

int
_particle_node_set_next_node(ParticleNode *self, ParticleNode *new_next_node) {
    if (new_next_node == NULL) {
        PyErr_SetString(PyExc_MemoryError, "the value provided to ParticleNode.next_node was NULL");
        return -1;
    }
    if (!ParticleNode_Check(new_next_node)) {
        PyErr_SetString(PyExc_TypeError, "the value provided to the ParticleNode.next_node was not of type ParticleNode");
        return -1;
    }

    Py_XDECREF(self->nextNode); // removing owner ship of the previouse value
    Py_INCREF(new_next_node); // adding owner ship
    self->nextNode = (PyObject *)new_next_node;

    return 0;
}

int
_particle_node_set_last_node(ParticleNode *self, ParticleNode *new_last_node) {
    if (new_last_node == NULL) {
        PyErr_SetString(PyExc_MemoryError, "the value provided to ParticleNode.next_node was NULL");
        return -1;
    }
    if (!ParticleNode_Check(new_last_node)) {
        PyErr_SetString(PyExc_TypeError, "the value provided to the ParticleNode.next_node was not of type ParticleNode");
        return -1;
    }

    Py_XDECREF(self->lastNode); // removing owner ship of the previouse value
    Py_INCREF(new_last_node); // adding owner ship
    self->lastNode = (PyObject *)new_last_node;

    return 0;
}

// Python API fun
static void
ParticleNode_dealloc(ParticleNode *self) {
    Py_XDECREF(self->particle);
    Py_XDECREF(self->nextNode);
    Py_XDECREF(self->lastNode);

    PS_DEALLOC_SELF(self);
}

static PyObject*
ParticleNode_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {

    ParticleNode* self = PS_BASIC_ALLOC_SELF(type, ParticleNode*);

    if (self != NULL) {
        Py_INCREF(Py_None);
        self->particle = (Particle*)Py_None;
        Py_INCREF(Py_None);
        self->lastNode = Py_None;
        Py_INCREF(Py_None);
        self->nextNode = Py_None;
    }

    return (PyObject *)self;
}

static int
ParticleNode_init(ParticleNode *self, PyObject *args, PyObject *kwargs) {
    char* kwlist[] = {
        "particle",
        "last_node",
        "next_node",
        NULL
    };

    Particle *particle = NULL;
    ParticleNode *lastNode = NULL, *nextNode = NULL;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|OOO", kwlist, &particle, &lastNode, &nextNode)) {
        PyErr_SetString(PyExc_ValueError, "parsing arguments in the ParticleNode.__init__() function failed");
        return -1;
    }

    // the reason for these NULL check is because the scale velocity and acceleration feilds are
    // optional and if we didnt do this check the _particle_node_set_... functions would thorow and exception
    // becasue you can't pass a NULL value to a setter
    if (particle != NULL) {
        _particle_node_set_particle(self, particle);
    }
    if (nextNode != NULL) {
        _particle_node_set_next_node(self, nextNode);
    }
    if (lastNode != NULL) {
        _particle_node_set_last_node(self, lastNode);
    }

    return 0;
}

static Particle*
ParticleNode_getParticle(ParticleNode *self, void* _closure) {
    Py_INCREF(self->particle);
    return self->particle;
}

static int
ParticleNode_setParticle(ParticleNode *self, Particle* value, void* _closure) {
    return _particle_node_set_particle(self, value);
}

static ParticleNode*
ParticleNode_getNextNode(ParticleNode *self, void *_closure) {
    Py_INCREF(self->nextNode);
    return (ParticleNode *)self->nextNode;
}

static int
ParticleNode_setNextNode(ParticleNode *self, ParticleNode *value, void *_closure) {
    return _particle_node_set_next_node(self, value);
}

static ParticleNode*
ParticleNode_getLastNode(ParticleNode *self, void *_closure) {
    Py_INCREF(self->lastNode);
    return (ParticleNode *)self->lastNode;
}

static int
ParticleNode_setLastNode(ParticleNode *self, ParticleNode *value, void *_closure) {
    return _particle_node_set_last_node(self, value);
}

static PyGetSetDef ParticleNode_getsetters[] = {
    {"particle", (getter)ParticleNode_getParticle, (setter)ParticleNode_setParticle, "particle that this node holds", NULL},
    {"next_node", (getter)ParticleNode_getNextNode, (setter)ParticleNode_setNextNode, "node that goes after this node in the particle system", NULL},
    {"last_node", (getter)ParticleNode_getLastNode, (setter)ParticleNode_setLastNode, "node that was before this node in the particle sysyem", NULL},
    {NULL}
};

PyTypeObject ParticleNodeType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "partsy.ParticleNode",
    .tp_basicsize = sizeof(ParticleNode),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "partsy.ParticleNode is a class that represents a Node in the particle system it self",
    .tp_new = ParticleNode_new,
    .tp_init = (initproc)ParticleNode_init,
    .tp_dealloc = (destructor)ParticleNode_dealloc,
    .tp_getset = ParticleNode_getsetters,
};
