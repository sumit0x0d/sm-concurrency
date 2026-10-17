#include <sm-barrier.h>

SM_Boolean sm_barrier_initialize(SM_Barrier *this, SM_Unsigned_32 participant_count)
{
   if (this == NULL || participant_count == 0) {
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_mutex_initialize(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_condition_variable_initialize(&this->condition)) {
      sm_mutex_deinitialize(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }

   this->participant_count = participant_count;
   this->waiting_count = 0;
   this->generation = 0;
   this->active = SM_BOOLEAN_TRUE;

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_barrier_deinitialize(SM_Barrier *this)
{
   if (this == NULL) {
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   if (!this->active) {
      sm_mutex_unlock(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }

   this->active = SM_BOOLEAN_FALSE;
   this->waiting_count = 0;
   this->generation++;

   if (!sm_condition_variable_broadcast(&this->condition)) {
      sm_mutex_unlock(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_mutex_unlock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_condition_variable_deinitialize(&this->condition)) {
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_mutex_deinitialize(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_barrier_wait(SM_Barrier *this)
{
   SM_Unsigned_32 generation;

   if (this == NULL || !this->active) {
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_mutex_lock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   if (!this->active) {
      sm_mutex_unlock(&this->mutex);
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

   while (generation == this->generation && this->active) {
      if (!sm_condition_variable_wait(&this->condition, &this->mutex)) {
         sm_mutex_unlock(&this->mutex);
         return SM_BOOLEAN_FALSE;
      }
   }

   if (!this->active) {
      sm_mutex_unlock(&this->mutex);
      return SM_BOOLEAN_FALSE;
   }

   if (!sm_mutex_unlock(&this->mutex)) {
      return SM_BOOLEAN_FALSE;
   }

   return SM_BOOLEAN_TRUE;
}