#include <sm-event.h>

SM_Boolean sm_event_initialize(SM_Event *this, SM_Boolean initially_signaled)
{
   if (initially_signaled != SM_BOOLEAN_FALSE && initially_signaled != SM_BOOLEAN_TRUE) {
      return SM_BOOLEAN_FALSE;
   }
   
   if (!sm_mutex_initialize(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   
   if (!sm_condition_variable_initialize(&this->condition)) {
      sm_mutex_deinitialize(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }
   
   this->signaled = initially_signaled;

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_event_deinitialize(SM_Event *this)
{
   if (!sm_condition_variable_deinitialize(&this->condition)) {
      return SM_BOOLEAN_FALSE;
   }
   
   if (!sm_mutex_deinitialize(&this->mutex)) {
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
