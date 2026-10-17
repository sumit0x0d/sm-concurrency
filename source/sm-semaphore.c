

#include <limits.h>

#include <sm-semaphore.h>

SM_Boolean sm_semaphore_create(SM_Semaphore *this, SM_Unsigned_32 initial_value)
{
#ifdef _WIN32
   if (initial_value > (SM_Unsigned_32)LONG_MAX) {
      return SM_BOOLEAN_FALSE;
   }

   *this = CreateSemaphore(NULL, (LONG)initial_value, LONG_MAX, NULL);
   if (*this == NULL) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (sem_init(this, 0, initial_value)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_semaphore_destroy(SM_Semaphore *this)
{
#ifdef _WIN32
   if (!CloseHandle(*this)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (sem_destroy(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_semaphore_wait(SM_Semaphore *this)
{
#ifdef _WIN32
   if (WaitForSingleObject(*this, INFINITE) != WAIT_OBJECT_0) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (sem_wait(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_semaphore_try_wait(SM_Semaphore *this)
{
#ifdef _WIN32
   if (WaitForSingleObject(*this, 0) != WAIT_OBJECT_0) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (sem_trywait(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_semaphore_post(SM_Semaphore *this)
{
#ifdef _WIN32
   if (!ReleaseSemaphore(*this, 1, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (sem_post(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}