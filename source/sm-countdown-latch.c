#include <sm-countdown-latch.h>

struct SM_Countdown_Latch {
   SM_Mutex mutex;
   SM_Condition_Variable condition;
   SM_Unsigned_32 count;
};

SM_Boolean sm_countdown_latch_create(SM_Countdown_Latch *this, SM_Unsigned_32 count)
{
   if (!sm_mutex_create(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }
   if (!sm_condition_variable_create(&this->condition)) {
      sm_mutex_destroy(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }
   this->count = count;

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_countdown_latch_destroy(SM_Countdown_Latch *this)
{
   if (!sm_condition_variable_destroy(&this->condition)) {
      return SM_BOOLEAN_FALSE;
   }
   if (!sm_mutex_destroy(&this->mutex)) {
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
