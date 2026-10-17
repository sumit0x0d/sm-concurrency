#include <sm-countdown-latch.h>

SM_Boolean sm_countdown_latch_initialize(SM_Countdown_Latch *this, SM_Unsigned_32 count)
{
   if (!sm_mutex_initialize(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   if (!sm_condition_variable_initialize(&this->condition)) {
      sm_mutex_deinitialize(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }
   this->count = count;

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_countdown_latch_deinitialize(SM_Countdown_Latch *this)
{
   if (!sm_condition_variable_deinitialize(&this->condition)) {
      return SM_BOOLEAN_FALSE;
   }
   if (!sm_mutex_deinitialize(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_countdown_latch_count_down(SM_Countdown_Latch *this, SM_Unsigned_32 count)
{
   if (count == 0 || !sm_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   if (count > this->count) {
      sm_mutex_unlock(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }

   this->count -= count;
   if (this->count == 0 && !sm_condition_variable_broadcast(&this->condition)) {
      sm_mutex_unlock(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }
   if (!sm_mutex_unlock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_countdown_latch_wait(SM_Countdown_Latch *this)
{
   if (!sm_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   while (this->count != 0) {
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
