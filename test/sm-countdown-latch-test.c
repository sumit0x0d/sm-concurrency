#include <sm-countdown-latch.h>
#include <sm-thread.h>

#include <assert.h>

#define THREAD_COUNT 2

static SM_Countdown_Latch latch;

static void *wait_at_latch(void *argument)
{
   (void)argument;
   assert(sm_countdown_latch_wait(&latch) == SM_BOOLEAN_TRUE);
   return NULL;
}

static void *wait_until_latch_is_closed(void *argument)
{
   (void)argument;
   assert(sm_countdown_latch_wait(&latch) == SM_BOOLEAN_FALSE);
   return NULL;
}

int main(void)
{
   SM_Thread threads[THREAD_COUNT];
   SM_Callback_Thread callback;
   SM_Unsigned_32 index;
   SM_Boolean waiter_started;

   assert(sm_countdown_latch_initialize(&latch, THREAD_COUNT) == SM_BOOLEAN_TRUE);
   assert(sm_countdown_latch_count_down(&latch, THREAD_COUNT + 1) == SM_BOOLEAN_FALSE);
   callback.function = wait_at_latch;
   callback.argument = NULL;
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_thread_initialize(&threads[index], &callback) == SM_BOOLEAN_TRUE);
   }
   assert(sm_countdown_latch_count_down(&latch, 1) == SM_BOOLEAN_TRUE);
   assert(sm_countdown_latch_count_down(&latch, 1) == SM_BOOLEAN_TRUE);
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_thread_join(&threads[index], NULL) == SM_BOOLEAN_TRUE);
   }
   assert(sm_countdown_latch_wait(&latch) == SM_BOOLEAN_TRUE);
   assert(sm_countdown_latch_deinitialize(&latch) == SM_BOOLEAN_TRUE);

   assert(sm_countdown_latch_initialize(&latch, 1) == SM_BOOLEAN_TRUE);
   callback.function = wait_until_latch_is_closed;
   assert(sm_thread_initialize(&threads[0], &callback) == SM_BOOLEAN_TRUE);
   do {
      assert(sm_mutex_lock(&latch.mutex) == SM_BOOLEAN_TRUE);
      waiter_started = (latch.active_waiter_count != 0);
      assert(sm_mutex_unlock(&latch.mutex) == SM_BOOLEAN_TRUE);
      if (!waiter_started) {
         assert(sm_thread_sleep(1) == SM_BOOLEAN_TRUE);
      }
   } while (!waiter_started);
   assert(sm_countdown_latch_deinitialize(&latch) == SM_BOOLEAN_TRUE);
   assert(sm_thread_join(&threads[0], NULL) == SM_BOOLEAN_TRUE);

   return 0;
}
