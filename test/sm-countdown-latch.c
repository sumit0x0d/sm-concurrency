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

int main(void)
{
   SM_Thread threads[THREAD_COUNT];
   SM_Unsigned_32 index;

   assert(sm_countdown_latch_create(&latch, THREAD_COUNT) == SM_BOOLEAN_TRUE);
   assert(sm_countdown_latch_count_down(&latch, THREAD_COUNT + 1) == SM_BOOLEAN_FALSE);
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_thread_create(&threads[index], wait_at_latch, NULL) == SM_BOOLEAN_TRUE);
   }
   assert(sm_countdown_latch_count_down(&latch, 1) == SM_BOOLEAN_TRUE);
   assert(sm_countdown_latch_count_down(&latch, 1) == SM_BOOLEAN_TRUE);
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_thread_join(&threads[index], NULL) == SM_BOOLEAN_TRUE);
   }
   assert(sm_countdown_latch_wait(&latch) == SM_BOOLEAN_TRUE);
   assert(sm_countdown_latch_destroy(&latch) == SM_BOOLEAN_TRUE);

   return 0;
}
