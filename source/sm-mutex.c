#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include <sm-mutex.h>

SM_Boolean sm_mutex_create(SM_Mutex *this)
{
#ifndef _WIN32
   pthread_mutexattr_t attribute;
#endif

#ifdef _WIN32
   if (!InitializeCriticalSectionAndSpinCount(this, 0)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_mutexattr_init(&attribute)) {
      return SM_BOOLEAN_FALSE;
   }

   if (pthread_mutexattr_settype(&attribute, PTHREAD_MUTEX_RECURSIVE)) {
      pthread_mutexattr_destroy(&attribute);
      return SM_BOOLEAN_FALSE;
   }

   if (pthread_mutex_init(this, &attribute)) {
      pthread_mutexattr_destroy(&attribute);
      return SM_BOOLEAN_FALSE;
   }

   if (pthread_mutexattr_destroy(&attribute)) {
      pthread_mutex_destroy(this);
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_mutex_destroy(SM_Mutex *this)
{
#ifdef _WIN32
   DeleteCriticalSection(this);
#else
   if (pthread_mutex_destroy(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_mutex_lock(SM_Mutex *this)
{
#ifdef _WIN32
   EnterCriticalSection(this);
#else
   if (pthread_mutex_lock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_mutex_try_lock(SM_Mutex *this)
{
#ifdef _WIN32
   if (!TryEnterCriticalSection(this)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_mutex_trylock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_mutex_unlock(SM_Mutex *this)
{
#ifdef _WIN32
   LeaveCriticalSection(this);
#else
   if (pthread_mutex_unlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}
