#include <sm-condition-variable.h>

SM_Boolean sm_condition_variable_create(SM_Condition_Variable *this)
{
#ifdef _WIN32
   InitializeConditionVariable(this);
#else
   if (pthread_cond_init(this, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

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
#endif

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
#endif

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
#endif

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
#endif

   return SM_BOOLEAN_TRUE;
}