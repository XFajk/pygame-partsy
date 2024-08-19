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

static PyObject*
Particle_addToVelocity(Particle *self, PyObject *args, PyObject *kwargs);
static PyObject*
Particle_addToAcceleration(Particle *self, PyObject *args, PyObject *kwargs);
static PyObject*
Particle_addToScale(Particle *self, PyObject *args, PyObject *kwargs);

static void
Particle_dealloc(Particle *self) {
    DEALLOC_SELF(self);
}

static PyObject*
Particle_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
    Particle* self = BASIC_ALLOC_SELF(type, Particle*);
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

    PyObject *scale, *position, *velocity, *acceleration;
    float rotationalVelocity = 0.f, rotationalAcceleration = 0.f;

    if (!PyArg_ParseTupleAndKeywords(
        args, kwargs, "O|OOOff", kwlist,
        &position,
        &scale,
        &velocity,
        &acceleration,
        &rotationalVelocity,
        &rotationalAcceleration
    )) return -1;

    if (!PySequence_Check(position) || PySequence_Length(position) < 2) {
        PyErr_SetString(PyExc_TypeError, "the position argument must be indexable and musth have a lenght of 2");
        return -1;
    }
    if ((!PySequence_Check(scale) || PySequence_Length(scale) < 2) && scale != NULL) { // the null check is here because scale is optional
        PyErr_SetString(PyExc_TypeError, "the scale argument must be indexable and musth have a lenght of 2");
        return -1;
    }
    if ((!PySequence_Check(velocity) || PySequence_Length(velocity) < 2) && velocity != NULL) { // the null check is here because scale is optional
        PyErr_SetString(PyExc_TypeError, "the velocity argument must be indexable and musth have a lenght of 2");
        return -1;
    }
    if ((!PySequence_Check(acceleration) || PySequence_Length(acceleration) < 2) && acceleration != NULL) { // the null check is here because scale is optional
        PyErr_SetString(PyExc_TypeError, "the acceleration argument must be indexable and musth have a lenght of 2");
        return -1;
    }

    // deleting the values that where set in the new function
    Py_XDECREF(self->position);
    Py_XDECREF(self->scale);
    Py_XDECREF(self->velocity);
    Py_XDECREF(self->acceleration);

    // transfering ownership from the local temporary variables to the objects feilds
    self->position = position;
    self->scale = scale;
    self->velocity = velocity;
    self->acceleration = acceleration;
    self->rotationalVelocity = rotationalVelocity;
    self->rotationalAcceleration = rotationalAcceleration;

    return 0;
}

static PyObject*
Particle_getPosition(Particle *self, void* _closure) {
    Py_INCREF(self->position);
    return self->position;
}

static int
Particle_setPosition(Particle *self, PyObject *value, void* _closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_ValueError, "there was no value provided for the Particle().position feild");
        return -1;
    }
    if (!PySequence_Check(value) || PySequence_Length(value) < 2) {
        PyErr_SetString(PyExc_TypeError, "the value provided for the Particle().position feild is not indexable or it's length is smaller then 2");
        return -1;
    }

    Py_XDECREF(self->position); // unrefencing the old value so the feild dosent own it anymore
    Py_INCREF(value);
    self->position = value; // transfer owner ship from the argument
    return 0;
}

static PyObject*
Particle_getScale(Particle *self, void* _closure) {
    Py_INCREF(self->scale);
    return self->scale;
}

static int
Particle_setScale(Particle *self, PyObject *value, void* _closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_ValueError, "there was no value provided for the Particle().scael feild");
        return -1;
    }
    if (!PySequence_Check(value) || PySequence_Length(value) < 2) {
        PyErr_SetString(PyExc_TypeError, "the value provided for the Particle().scale feild is not indexable or it's length is smaller then 2");
        return -1;
    }

    Py_XDECREF(self->scale); // unrefencing the old value so the feild dosent own it anymore
    Py_INCREF(value);
    self->scale = value; // transfer owner ship from the argument
    return 0;
}

static PyObject*
Particle_getVelocity(Particle *self, void* _closure) {
    Py_INCREF(self->velocity);
    return self->velocity;
}

static int
Particle_setVelocity(Particle *self, PyObject* value, void* _closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_ValueError, "there was no value provided for the Particle().velocity feild");
        return -1;
    }
    if (!PySequence_Check(value) || PySequence_Length(value) < 2) {
        PyErr_SetString(PyExc_TypeError, "the value provided for the Particle().velocity feild is not indexable or it's length is smaller then 2");
        return -1;
    }

    Py_XDECREF(self->velocity); // unrefencing the old value so the feild dosent own it anymore
    Py_INCREF(value);
    self->velocity = value; // transfer owner ship from the argument
    return 0;
}

static PyObject*
Particle_getAcceleration(Particle *self, void* _closure) {
    Py_INCREF(self->acceleration);
    return self->acceleration;
}

static int
Particle_setAcceleration(Particle *self, PyObject *value, void* _closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_ValueError, "there was no value provided for the Particle().acceleration feild");
        return -1;
    }
    if (!PySequence_Check(value) || PySequence_Length(value) < 2) {
        PyErr_SetString(PyExc_TypeError, "the value provided for the Particle().acceleration feild is not indexable or it's length is smaller then 2");
        return -1;
    }

    Py_XDECREF(self->acceleration); // unrefencing the old value so the feild dosent own it anymore
    Py_INCREF(value);
    self->acceleration = value; // transfer owner ship from the argument
    return 0;
}

// TODO: add more argument configurations like [ff]
static PyObject*
Particle_addToVelocity(Particle* self, PyObject* args, PyObject* kwargs) {
    static char* kwlist[] = {"vec", NULL};
    float x, y;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &x, &y)) return NULL;

    Py_RETURN_NONE;
}


static PyObject*
Particle_addToAcceleration(Particle* self, PyObject* args, PyObject* kwargs) {
    static char* kwlist[] = {"vec", NULL};
    float x, y;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &x, &y)) return NULL;

    Py_RETURN_NONE;
}


static PyObject*
Particle_addToScale(Particle* self, PyObject* args, PyObject* kwargs) {
    static char* kwlist[] = {"vec", NULL};
    PyObject* tmp;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &tmp)) return NULL;

    Py_RETURN_NONE;
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

static PyMethodDef Particle_methods[] = {

};

PyTypeObject ParticleType = {

};
