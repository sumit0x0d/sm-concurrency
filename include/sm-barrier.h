#ifndef SM_BARRIER_H
#define SM_BARRIER_H

#include <sm-api.h>
#include <sm-typedef.h>
#include <sm-condition-variable.h>
#include <sm-mutex.h>

typedef struct {
   SM_Mutex mutex;
   SM_Condition_Variable condition;
   SM_Unsigned_32 participant_count;
   SM_Unsigned_32 waiting_count;
   SM_Unsigned_32 generation;
} SM_Barrier;

SM_API SM_Boolean sm_barrier_create(SM_Barrier *this, SM_Unsigned_32 participant_count);

SM_API SM_Boolean sm_barrier_destroy(SM_Barrier *this);

SM_API SM_Boolean sm_barrier_wait(SM_Barrier *this);

#endif