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
   assert(sm_mutex_create(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_condition_variable_create(&condition) == SM_BOOLEAN_TRUE);
   assert(sm_mutex_lock(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_test_thread_create(&thread, signal_when_ready, NULL) == SM_BOOLEAN_TRUE);
   while (!ready) {
      assert(sm_condition_variable_wait(&condition, &mutex) == SM_BOOLEAN_TRUE);
   }
   assert(sm_mutex_unlock(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_test_thread_join(&thread) == SM_BOOLEAN_TRUE);

   assert(sm_condition_variable_broadcast(&condition) == SM_BOOLEAN_TRUE);
   assert(sm_condition_variable_destroy(&condition) == SM_BOOLEAN_TRUE);
   assert(sm_mutex_destroy(&mutex) == SM_BOOLEAN_TRUE);

   return 0;
}