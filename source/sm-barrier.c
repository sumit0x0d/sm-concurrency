#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include <sm-barrier.h>

SM_Boolean sm_barrier_create(SM_Barrier *this, SM_Unsigned_32 participant_count)
{
   if (participant_count == 0) {
      return SM_BOOLEAN_FALSE;
   }

#ifdef _WIN32
   if (!InitializeCriticalSectionAndSpinCount(&this->mutex, 0)) {
      return SM_BOOLEAN_FALSE;
   }
   InitializeConditionVariable(&this->condition);
#else
   if (pthread_mutex_init(&this->mutex, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
   if (pthread_cond_init(&this->condition, NULL)) {
      pthread_mutex_destroy(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }
#endif

   this->participant_count = participant_count;
   this->waiting_count = 0;
   this->generation = 0;

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_barrier_destroy(SM_Barrier *this)
{
#ifdef _WIN32
   DeleteCriticalSection(&this->mutex);
#else
   if (pthread_cond_destroy(&this->condition)) {
      return SM_BOOLEAN_FALSE;
   }
   if (pthread_mutex_destroy(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_barrier_wait(SM_Barrier *this)
{
   SM_Unsigned_32 generation;

#ifdef _WIN32
   EnterCriticalSection(&this->mutex);
#else
   if (pthread_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   generation = this->generation;
   this->waiting_count++;

   if (this->waiting_count == this->participant_count) {
      this->waiting_count = 0;
      this->generation++;
#ifdef _WIN32
      WakeAllConditionVariable(&this->condition);
      LeaveCriticalSection(&this->mutex);
#else
      if (pthread_cond_broadcast(&this->condition)) {
         pthread_mutex_unlock(&this->mutex);
         return SM_BOOLEAN_FALSE;
      }
      if (pthread_mutex_unlock(&this->mutex)) {
         return SM_BOOLEAN_FALSE;
      }
#endif
      return SM_BOOLEAN_TRUE;
   }

#ifdef _WIN32
   while (generation == this->generation) {
      if (!SleepConditionVariableCS(&this->condition, &this->mutex, INFINITE)) {
         LeaveCriticalSection(&this->mutex);
         return SM_BOOLEAN_FALSE;
      }
   }
   LeaveCriticalSection(&this->mutex);
#else
   while (generation == this->generation) {
      if (pthread_cond_wait(&this->condition, &this->mutex)) {
         pthread_mutex_unlock(&this->mutex);
         return SM_BOOLEAN_FALSE;
      }
   }
   if (pthread_mutex_unlock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}