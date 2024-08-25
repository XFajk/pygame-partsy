#ifndef PARTICLE_H
#define PARTICLE_H

#include "pytypedefs.h"
#include <Python.h>
#include <stdbool.h>
#include <stddef.h>

inline void D_LOG(const char* msg) {
    #ifdef PS_DEBUG

    printf("-> ");
    printf("%s", msg);

    #endif
}

inline void D_PY_OBJECT_LOG(const char* msg, PyObject* o) {
    #ifdef PS_DEBUG

    printf("-> ");
    printf("%s", msg);
    if (o != NULL) {
        PyObject_Print(o, stdout, Py_PRINT_RAW);
    } else {
        printf("NULL");
    }
    printf("\n");

    #endif
}

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

// Particle C API functions implementataio in particle.c file
int
_particle_set_position(Particle* self, PyObject* new_position);
int
_particle_set_scale(Particle* self, PyObject* new_scale);
int
_particle_set_velocity(Particle* self, PyObject* new_velocity);
int
_particle_set_acceleration(Particle* self, PyObject* new_acceleration);

// TODO: create a C API to use this object so someone working with an instacne of this object doesnt have to call its methods

extern PyTypeObject ParticleType;

typedef struct {
    PyObject_HEAD
    Particle* particle;
    PyObject* nextNode;
    PyObject* lastNode;
} ParticleNode;

extern PyTypeObject ParticleNodeType;

typedef struct {
    PyObject_HEAD
    ParticleNode* head;
    ParticleNode* tail;
    Py_ssize_t length;
} ParticleManager;

extern PyTypeObject ParticleManagerType;

#endif // PARTICLE_H
