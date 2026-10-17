#ifndef SM_CONDITION_VARIABLE_H
#define SM_CONDITION_VARIABLE_H

#include <sm-api.h>
#include <sm-typedef.h>
#include <sm-mutex.h>

#ifdef _WIN32
   #include <windows.h>
   typedef CONDITION_VARIABLE SM_Condition_Variable;
#else
   #include <pthread.h>
   typedef pthread_cond_t SM_Condition_Variable;
#endif

SM_API SM_Boolean sm_condition_variable_create(SM_Condition_Variable *this);

SM_API SM_Boolean sm_condition_variable_destroy(SM_Condition_Variable *this);

SM_API SM_Boolean sm_condition_variable_signal(SM_Condition_Variable *this);

SM_API SM_Boolean sm_condition_variable_broadcast(SM_Condition_Variable *this);

SM_API SM_Boolean sm_condition_variable_wait(SM_Condition_Variable *this, SM_Mutex *mutex);

#endif