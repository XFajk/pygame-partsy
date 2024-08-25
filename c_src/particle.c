#include <Python.h>

#include "include/partsy.h"

/*
    PARTICLE METHODS/RELATED FUNCTIONS
*/
static void
Particle_dealloc(Particle *self);
static PyObject*
Particle_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);
static int
Particle_init(Particle *self, PyObject *args, PyObject *kwargs);

static PyObject*
Particle_getPosition(Particle *self, void* _closure);
static int
Particle_setPosition(Particle *self, PyObject* value, void* _closure);
static PyObject*
Particle_getScale(Particle *self, void* _closure);
static int
Particle_setScale(Particle *self, PyObject* value, void* _closure);
static PyObject*
Particle_getVelocity(Particle *self, void* _closure);
static int
Particle_setVelocity(Particle *self, PyObject* value, void* _closure);
static PyObject*
Particle_getAcceleration(Particle *self, void* _closure);
static int
Particle_setAcceleration(Particle *self, PyObject* value, void* _closure);


// C API functions
int
_particle_set_position(Particle* self, PyObject* new_position) {
    if (new_position == NULL) {
        PyErr_SetString(PyExc_ValueError, "there was no value provided for the Particle().position feild");
        return -1;
    }
    if (!PySequence_Check(new_position) || PySequence_Length(new_position) < 2) {
        PyErr_SetString(PyExc_TypeError, "the value provided for the Particle().position feild is not indexable or it's length is smaller then 2");
        return -1;
    }

    PyObject* value_x = PySequence_GetItem(new_position,  0);
    PyObject* value_y = PySequence_GetItem(new_position,  1);

    if (!PyNumber_Check(value_x)) {
        PyErr_SetString(PyExc_TypeError, "the first value of the sequence is not a number");
        return -1;
    }
    if (!PyNumber_Check(value_y)) {
        PyErr_SetString(PyExc_TypeError, "the first second of the sequence is not a number");
        return -1;
    }

    Py_DECREF(value_x);
    Py_DECREF(value_y);

    Py_XDECREF(self->position); // unrefencing the old value so the feild dosent own it anymore
    Py_INCREF(new_position);
    self->position = new_position; // transfer owner ship from the argument
    return 0;
}

int
_particle_set_scale(Particle* self, PyObject* new_scale) {
    if (new_scale == NULL) {
        PyErr_SetString(PyExc_ValueError, "there was no value provided for the Particle().velocity feild");
        return -1;
    }
    if (!PySequence_Check(new_scale) || PySequence_Length(new_scale) < 2) {
        PyErr_SetString(PyExc_TypeError, "the value provided for the Particle().velocity feild is not indexable or it's length is smaller then 2");
        return -1;
    }

    PyObject* value_x = PySequence_GetItem(new_scale,  0);
    PyObject* value_y = PySequence_GetItem(new_scale,  1);

    if (!PyNumber_Check(value_x)) {
        PyErr_SetString(PyExc_TypeError, "the first value of the sequence is not a number");
        return -1;
    }
    if (!PyNumber_Check(value_y)) {
        PyErr_SetString(PyExc_TypeError, "the first second of the sequence is not a number");
        return -1;
    }

    Py_DECREF(value_x);
    Py_DECREF(value_y);

    Py_XDECREF(self->scale); // unrefencing the old value so the feild dosent own it anymore
    Py_INCREF(new_scale);
    self->scale = new_scale; // transfer owner ship from the argument
    return 0;
}

int
_particle_set_velocity(Particle* self, PyObject* new_velocity) {
    if (new_velocity == NULL) {
        PyErr_SetString(PyExc_ValueError, "there was no value provided for the Particle().velocity feild");
        return -1;
    }
    if (!PySequence_Check(new_velocity) || PySequence_Length(new_velocity) < 2) {
        PyErr_SetString(PyExc_TypeError, "the value provided for the Particle().velocity feild is not indexable or it's length is smaller then 2");
        return -1;
    }

    PyObject* value_x = PySequence_GetItem(new_velocity,  0);
    PyObject* value_y = PySequence_GetItem(new_velocity,  1);

    if (!PyNumber_Check(value_x)) {
        PyErr_SetString(PyExc_TypeError, "the first value of the sequence is not a number");
        return -1;
    }
    if (!PyNumber_Check(value_y)) {
        PyErr_SetString(PyExc_TypeError, "the first second of the sequence is not a number");
        return -1;
    }

    Py_DECREF(value_x);
    Py_DECREF(value_y);

    Py_XDECREF(self->velocity); // unrefencing the old value so the feild dosent own it anymore
    Py_INCREF(new_velocity);
    self->velocity = new_velocity; // transfer owner ship from the argument
    return 0;
}

int
_particle_set_acceleration(Particle* self, PyObject* new_acceleration) {
    if (new_acceleration == NULL) {
        PyErr_SetString(PyExc_ValueError, "there was no value provided for the Particle().velocity feild");
        return -1;
    }
    if (!PySequence_Check(new_acceleration) || PySequence_Length(new_acceleration) < 2) {
        PyErr_SetString(PyExc_TypeError, "the value provided for the Particle().velocity feild is not indexable or it's length is smaller then 2");
        return -1;
    }

    PyObject* value_x = PySequence_GetItem(new_acceleration,  0);
    PyObject* value_y = PySequence_GetItem(new_acceleration,  1);

    if (!PyNumber_Check(value_x)) {
        PyErr_SetString(PyExc_TypeError, "the first value of the sequence is not a number");
        return -1;
    }
    if (!PyNumber_Check(value_y)) {
        PyErr_SetString(PyExc_TypeError, "the first second of the sequence is not a number");
        return -1;
    }

    Py_DECREF(value_x);
    Py_DECREF(value_y);

    Py_XDECREF(self->acceleration); // unrefencing the old value so the feild dosent own it anymore
    Py_INCREF(new_acceleration);
    self->acceleration = new_acceleration; // transfer owner ship from the argument
    return 0;
}


// Python API functions
static void
Particle_dealloc(Particle *self) {

    Py_XDECREF(self->position);
    Py_XDECREF(self->scale);
    Py_XDECREF(self->velocity);
    Py_XDECREF(self->acceleration);

    PS_DEALLOC_SELF(self);
}

static PyObject*
Particle_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {

    Particle* self = PS_BASIC_ALLOC_SELF(type, Particle*);

    if (self != NULL) {
        self->position = Py_BuildValue("(ff)", 0.f, 0.f);
        self->velocity = Py_BuildValue("(ff)", 0.f, 0.f);
        self->acceleration = Py_BuildValue("(ff)", 0.f, 0.f);
        self->scale = Py_BuildValue("(ff)", 1.f, 1.f);

        self->upForDeletion = false;
    }

    return (PyObject*)self;
}

static int
Particle_init(Particle *self, PyObject* args, PyObject* kwargs) {
    static char* kwlist[] = {
        "position",
        "scale",
        "velocity",
        "acceleration",
        "rotational_velocity",
        "rotational_acceleration",
        NULL // sentinel
    };

    PyObject *scale = NULL, *position = NULL, *velocity = NULL, *acceleration = NULL;
    if (!PyArg_ParseTupleAndKeywords(
        args, kwargs, "O|OOOff", kwlist,
        &position,
        &scale,
        &velocity,
        &acceleration,
        &self->rotationalVelocity,
        &self->rotationalAcceleration
    )) {
        return -1;
    }

    _particle_set_position(self, position);
    _particle_set_scale(self, scale);
    _particle_set_velocity(self, velocity);
    _particle_set_acceleration(self, acceleration);

    return 0;
}

static PyObject*
Particle_getPosition(Particle *self, void* _closure) {
    Py_INCREF(self->position);
    return self->position;
}

static int
Particle_setPosition(Particle *self, PyObject *value, void* _closure) {
    return _particle_set_position(self, value);
}

static PyObject*
Particle_getScale(Particle *self, void* _closure) {
    Py_INCREF(self->scale);
    return self->scale;
}

static int
Particle_setScale(Particle *self, PyObject *value, void* _closure) {
    return _particle_set_scale(self, value);
}

static PyObject*
Particle_getVelocity(Particle *self, void* _closure) {
    Py_INCREF(self->velocity);
    return self->velocity;
}

static int
Particle_setVelocity(Particle *self, PyObject* value, void* _closure) {
    return _particle_set_velocity(self, value);
}

static PyObject*
Particle_getAcceleration(Particle *self, void* _closure) {
    Py_INCREF(self->acceleration);
    return self->acceleration;
}

static int
Particle_setAcceleration(Particle *self, PyObject *value, void* _closure) {
    return _particle_set_acceleration(self, value);
}


static PyGetSetDef Particle_getsetters[] = {
    {"position", (getter)Particle_getPosition, (setter)Particle_setPosition, "position of the particle", NULL},
    {"scale", (getter)Particle_getScale, (setter)Particle_setScale, "scale of the Particle from 0 - 1+", NULL},
    {"velocity", (getter)Particle_getVelocity, (setter)Particle_setVelocity, "velocity of the particle descripes how does the particle move", NULL},
    {"acceleration", (getter)Particle_getAcceleration, (setter)Particle_setAcceleration, "acceleration of the particle determines how does the velocity change over time", NULL},
    {NULL}
};

static PyMemberDef Particle_members[] = {
    {"rot_velocity", Py_T_FLOAT, offsetof(Particle, rotationalVelocity), 0, "rotational velocity of the particle describes how does the particel rotate"},
    {"rot_acceleration", Py_T_FLOAT, offsetof(Particle, rotationalAcceleration), 0, "rotational acceleration of the particle describes how does the particle velocity change"},
    {"delete", Py_T_FLOAT, offsetof(Particle, upForDeletion), 0, "this bool determines if the Particle is going to be deleted or not"},
    {NULL}
};


PyTypeObject ParticleType = {
    .ob_base =PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "partsy.Particle",
    .tp_basicsize = sizeof(Particle),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = "partsy.Particle is a class that repsents a particle it holds everything that a particle should",
    .tp_new = Particle_new,
    .tp_init = (initproc)Particle_init,
    .tp_dealloc = (destructor)Particle_dealloc,
    .tp_members = Particle_members,
    .tp_getset = Particle_getsetters,
};
