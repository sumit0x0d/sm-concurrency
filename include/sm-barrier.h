#ifndef SM_BARRIER_H
#define SM_BARRIER_H

#include <sm-api.h>
#include <sm-condition-variable.h>
#include <sm-mutex.h>
#include <sm-typedef.h>

typedef struct SM_Barrier {
   SM_Mutex mutex;
   SM_Condition_Variable condition;
   SM_Unsigned_32 participant_count;
   SM_Unsigned_32 waiting_count;
   SM_Unsigned_32 generation;
   SM_Boolean active;
} SM_Barrier;

SM_API SM_Boolean sm_barrier_initialize(SM_Barrier *this, SM_Unsigned_32 participant_count);

SM_API SM_Boolean sm_barrier_deinitialize(SM_Barrier *this);

SM_API SM_Boolean sm_barrier_wait(SM_Barrier *this);

#endif /* SM_BARRIER_H */
