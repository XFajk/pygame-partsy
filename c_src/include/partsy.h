#ifndef PARTICLE_H
#define PARTICLE_H

#include <Python.h>
#include <stdbool.h>
#include <stddef.h>

#define DEALLOC_SELF(self) Py_TYPE(self)->tp_dealloc((PyObject*)self)
#define BASIC_ALLOC_SELF(type, alloc_type) (alloc_type)type->tp_alloc(type, 0)

typedef struct {
    PyObject_HEAD

    PyObject* position;
    PyObject* velocity;
    PyObject* acceleration;
    PyObject* scale;

    float rotationalVelocity;
    float rotationalAcceleration;

    bool upForDeletion;
} Particle;

PyTypeObject ParticleType;

typedef struct {
    PyObject_HEAD
    Particle* particle;
    PyObject* nextNode;
    PyObject* lastNode;
} ParticleNode;

PyTypeObject ParticleNodeType;

typedef struct {
    PyObject_HEAD
    ParticleNode* head;
    ParticleNode* tail;
    Py_ssize_t length;
} ParticleManager;

PyTypeObject ParticleManagerType;

#endif // PARTICLE_H
