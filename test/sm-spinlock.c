#include <sm-spinlock.h>

#include <assert.h>

#include "sm-test-thread.h"

#define THREAD_COUNT 4
#define ITERATION_COUNT 1000

static SM_Spinlock spinlock;
static SM_Signed_32 counter;

static void *increment_counter(void *argument)
{
   SM_Signed_32 index;

   (void)argument;
   for (index = 0; index < ITERATION_COUNT; index++) {
      assert(sm_spinlock_lock(&spinlock) == SM_BOOLEAN_TRUE);
      counter++;
      assert(sm_spinlock_unlock(&spinlock) == SM_BOOLEAN_TRUE);
   }
   return NULL;
}

int main(void)
{
   SM_Test_Thread threads[THREAD_COUNT];
   SM_Signed_32 index;

   counter = 0;
   assert(sm_spinlock_initialize(&spinlock) == SM_BOOLEAN_TRUE);
   assert(sm_spinlock_try_lock(&spinlock) == SM_BOOLEAN_TRUE);
   assert(sm_spinlock_unlock(&spinlock) == SM_BOOLEAN_TRUE);

   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_test_thread_initialize(&threads[index], increment_counter, NULL) == SM_BOOLEAN_TRUE);
   }
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_test_thread_join(&threads[index]) == SM_BOOLEAN_TRUE);
   }

   assert(counter == THREAD_COUNT * ITERATION_COUNT);
   assert(sm_spinlock_deinitialize(&spinlock) == SM_BOOLEAN_TRUE);

   return 0;
}