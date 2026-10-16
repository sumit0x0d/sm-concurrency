#include <sm-barrier.h>

SM_Boolean sm_barrier_create(SM_Barrier *this, SM_Unsigned_32 participant_count)
{
   if (participant_count == 0) {
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_mutex_create(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_condition_variable_create(&this->condition)) {
      sm_mutex_destroy(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }

   this->participant_count = participant_count;
   this->waiting_count = 0;
   this->generation = 0;

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_barrier_destroy(SM_Barrier *this)
{
   if (!sm_condition_variable_destroy(&this->condition)) {
      return SM_BOOLEAN_FALSE;
   }
   if (!sm_mutex_destroy(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_barrier_wait(SM_Barrier *this)
{
   SM_Unsigned_32 generation;

   if (!sm_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   generation = this->generation;
   this->waiting_count++;

   if (this->waiting_count == this->participant_count) {
      this->waiting_count = 0;
      this->generation++;
      if (!sm_condition_variable_broadcast(&this->condition)) {
         sm_mutex_unlock(&this->mutex);
         return SM_BOOLEAN_FALSE;
      }
      if (!sm_mutex_unlock(&this->mutex)) {
         return SM_BOOLEAN_FALSE;
      }
      return SM_BOOLEAN_TRUE;
   }

   while (generation == this->generation) {
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