#include <sm-barrier.h>

#include <assert.h>

#include "sm-test-thread.h"

#define THREAD_COUNT 4
#define ROUND_COUNT 10

static SM_Barrier barrier;
static SM_Signed_32 completed_rounds[THREAD_COUNT];

static void *wait_at_barrier(void *argument)
{
   SM_Unsigned_32 index;

   index = (SM_Unsigned_32)(size_t)argument;
   while (completed_rounds[index] < ROUND_COUNT) {
      completed_rounds[index]++;
      assert(sm_barrier_wait(&barrier) == SM_BOOLEAN_TRUE);
   }

   return NULL;
}

int main(void)
{
   SM_Test_Thread threads[THREAD_COUNT];
   SM_Unsigned_32 index;

   assert(sm_barrier_create(&barrier, 0) == SM_BOOLEAN_FALSE);
   assert(sm_barrier_create(&barrier, THREAD_COUNT) == SM_BOOLEAN_TRUE);

   for (index = 0; index < THREAD_COUNT; index++) {
      completed_rounds[index] = 0;
      assert(sm_test_thread_create(&threads[index], wait_at_barrier, (void *)(size_t)index) == SM_BOOLEAN_TRUE);
   }
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_test_thread_join(&threads[index]) == SM_BOOLEAN_TRUE);
      assert(completed_rounds[index] == ROUND_COUNT);
   }

   assert(sm_barrier_destroy(&barrier) == SM_BOOLEAN_TRUE);

   return 0;
}