#ifndef _WIN32
#include <errno.h>
#include <time.h>
#endif /* !_WIN32 */

#include <sm-condition-variable.h>

SM_Boolean sm_condition_variable_create(SM_Condition_Variable *this)
{
#ifdef _WIN32
   InitializeConditionVariable(this);
#else
   if (pthread_cond_init(this, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_condition_variable_destroy(SM_Condition_Variable *this)
{
#ifdef _WIN32
   (void)this;
#else
   if (pthread_cond_destroy(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_condition_variable_signal(SM_Condition_Variable *this)
{
#ifdef _WIN32
   WakeConditionVariable(this);
#else
   if (pthread_cond_signal(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_condition_variable_broadcast(SM_Condition_Variable *this)
{
#ifdef _WIN32
   WakeAllConditionVariable(this);
#else
   if (pthread_cond_broadcast(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_condition_variable_wait(SM_Condition_Variable *this, SM_Mutex *mutex)
{
#ifdef _WIN32
   if (!SleepConditionVariableCS(this, mutex, INFINITE)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_cond_wait(this, mutex)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_condition_variable_timed_wait(SM_Condition_Variable *this, SM_Mutex *mutex, SM_Unsigned_32 millisecond)
{
#ifdef _WIN32
   if (!SleepConditionVariableCS(this, mutex, (DWORD)milliseconds)) {
      if (GetLastError() == ERROR_TIMEOUT) {
         return SM_BOOLEAN_FALSE;
      }
      return SM_BOOLEAN_FALSE;
   }
#else
   struct timespec now;
   struct timespec deadline;

   if (clock_gettime(CLOCK_REALTIME, &now)) {
      return SM_BOOLEAN_FALSE;
   }

   deadline.tv_sec = now.tv_sec + (time_t)(millisecond / 1000);
   deadline.tv_nsec = now.tv_nsec + (long)(millisecond % 1000) * 1000000L;
   if (deadline.tv_nsec >= 1000000000L) {
      deadline.tv_sec += 1;
      deadline.tv_nsec -= 1000000000L;
   }

   if (pthread_cond_timedwait(this, mutex, &deadline)) {
      if (errno == ETIMEDOUT) {
         return SM_BOOLEAN_FALSE;
      }
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}