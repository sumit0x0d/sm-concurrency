#include <sm-condition-variable.h>
#include <sm-event.h>
#include <sm-mutex.h>

struct SM_Event {
   SM_Mutex mutex;
   SM_Condition_Variable condition;
   SM_Boolean signaled;
};

SM_Boolean sm_event_create(SM_Event *this, SM_Boolean initially_signaled)
{
   if (initially_signaled != SM_BOOLEAN_FALSE && initially_signaled != SM_BOOLEAN_TRUE) {
      return SM_BOOLEAN_FALSE;
   }
   
   if (!sm_mutex_create(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   
   if (!sm_condition_variable_create(&this->condition)) {
      sm_mutex_destroy(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }
   
   this->signaled = initially_signaled;

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_event_destroy(SM_Event *this)
{
   if (!sm_condition_variable_destroy(&this->condition)) {
      return SM_BOOLEAN_FALSE;
   }
   
   if (!sm_mutex_destroy(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_event_set(SM_Event *this)
{
   if (!sm_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   
   this->signaled = SM_BOOLEAN_TRUE;
   
   if (!sm_condition_variable_broadcast(&this->condition)) {
      sm_mutex_unlock(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }
   
   if (!sm_mutex_unlock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_event_reset(SM_Event *this)
{
   if (!sm_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   
   this->signaled = SM_BOOLEAN_FALSE;
   
   if (!sm_mutex_unlock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_event_wait(SM_Event *this)
{
   if (!sm_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   
   while (!this->signaled) {
      if (!sm_condition_variable_wait(&this->condition, &this->mutex)) {
         sm_mutex_unlock(&this->mutex);
         return SM_BOOLEAN_FALSE;
      }
   }
   
   if (!sm_mutex_unlock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}
