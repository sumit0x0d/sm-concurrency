#include <sm-barrier.h>
#include <sm-thread.h>

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

static void *wait_until_barrier_is_closed(void *argument)
{
   (void)argument;
   assert(sm_barrier_wait(&barrier) == SM_BOOLEAN_FALSE);
   return NULL;
}

int main(void)
{
   SM_Test_Thread threads[THREAD_COUNT];
   SM_Unsigned_32 index;
   SM_Boolean waiter_started;

   assert(sm_barrier_initialize(&barrier, 0) == SM_BOOLEAN_FALSE);
   assert(sm_barrier_initialize(&barrier, THREAD_COUNT) == SM_BOOLEAN_TRUE);

   for (index = 0; index < THREAD_COUNT; index++) {
      completed_rounds[index] = 0;
      assert(sm_test_thread_initialize(&threads[index], wait_at_barrier, (void *)(size_t)index) == SM_BOOLEAN_TRUE);
   }
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_test_thread_join(&threads[index]) == SM_BOOLEAN_TRUE);
      assert(completed_rounds[index] == ROUND_COUNT);
   }

   assert(sm_barrier_deinitialize(&barrier) == SM_BOOLEAN_TRUE);

   assert(sm_barrier_initialize(&barrier, 2) == SM_BOOLEAN_TRUE);
   assert(sm_test_thread_initialize(&threads[0], wait_until_barrier_is_closed, NULL) == SM_BOOLEAN_TRUE);
   do {
      assert(sm_mutex_lock(&barrier.mutex) == SM_BOOLEAN_TRUE);
      waiter_started = (barrier.waiting_count != 0);
      assert(sm_mutex_unlock(&barrier.mutex) == SM_BOOLEAN_TRUE);
      if (!waiter_started) {
         assert(sm_thread_sleep(1) == SM_BOOLEAN_TRUE);
      }
   } while (!waiter_started);
   assert(sm_barrier_deinitialize(&barrier) == SM_BOOLEAN_TRUE);
   assert(sm_test_thread_join(&threads[0]) == SM_BOOLEAN_TRUE);

   return 0;
}