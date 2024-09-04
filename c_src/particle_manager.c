#include <Python.h>

#include "include/partsy.h"
#include "object.h"

/*
    PARTICLE MANAGER METHODS/RELATED FUNCTIONS
*/
static void
ParticleManager_dealloc(ParticleManager *self);

static void
ParticleManager_dealloc(ParticleManager *self) {
    ParticleNode* current = self->head; // borrow
    for (Py_ssize_t i = 0; i < self->length; i++) {
        ParticleNode* next = (ParticleNode*)current->nextNode; // borrow
        Py_XDECREF(current); // deletion of the Node or if the node is owned somewhere else just a decrese of a refrence
        current = next; // borrow
    }
    PS_DEALLOC_SELF(self);
}
