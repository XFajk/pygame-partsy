#ifndef PARTSY_H
#define PARTSY_H

#include "pytypedefs.h"
#include <Python.h>
#include <stdbool.h>
#include <stddef.h>

#define PS_DEALLOC_SELF(self) Py_TYPE(self)->tp_free((PyObject*)self)
#define PS_BASIC_ALLOC_SELF(type, alloc_type) (alloc_type)type->tp_alloc(type, 0)

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

extern PyTypeObject ParticleType;

#define Particle_Check(ob) PyObject_TypeCheck(ob, &ParticleType)

// Particle C API functions implementataio in particle.c file
int
_particle_set_position(Particle* self, PyObject* new_position);
int
_particle_set_scale(Particle* self, PyObject* new_scale);
int
_particle_set_velocity(Particle* self, PyObject* new_velocity);
int
_particle_set_acceleration(Particle* self, PyObject* new_acceleration);

typedef struct {
    PyObject_HEAD
    Particle* particle;
    PyObject* nextNode;
    PyObject* lastNode;
} ParticleNode;

extern PyTypeObject ParticleNodeType;

#define ParticleNode_Check(ob) PyObject_TypeCheck(ob, &ParticleNodeType)

// ParticleNode C API functions inplementation in particle_node.c file
int
_particle_node_set_particle(ParticleNode *self, Particle *new_particle);
int
_particle_node_set_next_node(ParticleNode *self, ParticleNode *new_next_node);
int
_particle_node_set_last_node(ParticleNode *self, ParticleNode *new_last_node);

typedef struct {
    PyObject_HEAD
    ParticleNode* head;
    ParticleNode* tail;
    Py_ssize_t length;
} ParticleManager;

extern PyTypeObject ParticleManagerType;

#define ParticleManager_Check(ob) PyObject_TypeCheck(ob, &ParticleManagerType)

#endif // PARTSY_H
