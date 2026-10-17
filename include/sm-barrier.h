#ifndef SM_BARRIER_H
#define SM_BARRIER_H

#include <sm-api.h>
#include <sm-typedef.h>

typedef struct SM_Barrier SM_Barrier;

SM_API SM_Boolean sm_barrier_create(SM_Barrier *this, SM_Unsigned_32 participant_count);

SM_API SM_Boolean sm_barrier_destroy(SM_Barrier *this);

SM_API SM_Boolean sm_barrier_wait(SM_Barrier *this);

#endif