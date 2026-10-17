#include <sm-condition-variable.h>

#include <assert.h>

#include "sm-test-thread.h"

static SM_Mutex mutex;
static SM_Condition_Variable condition;
static SM_Signed_32 ready;

static void *signal_when_ready(void *argument)
{
   (void)argument;
   assert(sm_mutex_lock(&mutex) == SM_BOOLEAN_TRUE);
   ready = 1;
   assert(sm_condition_variable_signal(&condition) == SM_BOOLEAN_TRUE);
   assert(sm_mutex_unlock(&mutex) == SM_BOOLEAN_TRUE);
   return NULL;
}

int main(void)
{
   SM_Test_Thread thread;

   ready = 0;
   assert(sm_mutex_initialize(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_condition_variable_initialize(&condition) == SM_BOOLEAN_TRUE);
   assert(sm_mutex_lock(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_test_thread_initialize(&thread, signal_when_ready, NULL) == SM_BOOLEAN_TRUE);
   while (!ready) {
      assert(sm_condition_variable_wait(&condition, &mutex) == SM_BOOLEAN_TRUE);
   }
   assert(sm_mutex_unlock(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_test_thread_join(&thread) == SM_BOOLEAN_TRUE);

   assert(sm_mutex_lock(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_condition_variable_timed_wait(&condition, &mutex, 1) == SM_BOOLEAN_FALSE);
   assert(sm_mutex_unlock(&mutex) == SM_BOOLEAN_TRUE);

   assert(sm_condition_variable_broadcast(&condition) == SM_BOOLEAN_TRUE);
   assert(sm_condition_variable_deinitialize(&condition) == SM_BOOLEAN_TRUE);
   assert(sm_mutex_deinitialize(&mutex) == SM_BOOLEAN_TRUE);

   return 0;
}