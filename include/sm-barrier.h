#ifndef SM_BARRIER_H
#define SM_BARRIER_H

#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
#include <windows.h>
typedef struct {
   CRITICAL_SECTION mutex;
   CONDITION_VARIABLE condition;
   SM_Unsigned_32 participant_count;
   SM_Unsigned_32 waiting_count;
   SM_Unsigned_32 generation;
} SM_Barrier;
#else
#include <pthread.h>
typedef struct {
   pthread_mutex_t mutex;
   pthread_cond_t condition;
   SM_Unsigned_32 participant_count;
   SM_Unsigned_32 waiting_count;
   SM_Unsigned_32 generation;
} SM_Barrier;
#endif

SM_API SM_Boolean sm_barrier_create(SM_Barrier *this, SM_Unsigned_32 participant_count);
SM_API SM_Boolean sm_barrier_destroy(SM_Barrier *this);
SM_API SM_Boolean sm_barrier_wait(SM_Barrier *this);

#endif