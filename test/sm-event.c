#include <sm-event.h>
#include <sm-thread.h>

#include <assert.h>

static SM_Event event;

static void *wait_for_event(void *argument)
{
   (void)argument;
   assert(sm_event_wait(&event) == SM_BOOLEAN_TRUE);
   return NULL;
}

static void *wait_until_event_is_closed(void *argument)
{
   (void)argument;
   assert(sm_event_wait(&event) == SM_BOOLEAN_FALSE);
   return NULL;
}

int main(void)
{
   SM_Thread thread;
   SM_Callback_Thread callback;
   SM_Boolean waiter_started;

   assert(sm_event_initialize(&event, SM_BOOLEAN_FALSE) == SM_BOOLEAN_TRUE);
   callback.function = wait_for_event;
   callback.argument = NULL;
   assert(sm_thread_initialize(&thread, &callback) == SM_BOOLEAN_TRUE);
   assert(sm_event_set(&event) == SM_BOOLEAN_TRUE);
   assert(sm_thread_join(&thread, NULL) == SM_BOOLEAN_TRUE);
   assert(sm_event_wait(&event) == SM_BOOLEAN_TRUE);
   assert(sm_event_reset(&event) == SM_BOOLEAN_TRUE);
   assert(sm_event_deinitialize(&event) == SM_BOOLEAN_TRUE);

   assert(sm_event_initialize(&event, SM_BOOLEAN_FALSE) == SM_BOOLEAN_TRUE);
   callback.function = wait_until_event_is_closed;
   assert(sm_thread_initialize(&thread, &callback) == SM_BOOLEAN_TRUE);
   do {
      assert(sm_mutex_lock(&event.mutex) == SM_BOOLEAN_TRUE);
      waiter_started = (event.active_waiter_count != 0);
      assert(sm_mutex_unlock(&event.mutex) == SM_BOOLEAN_TRUE);
      if (!waiter_started) {
         assert(sm_thread_sleep(1) == SM_BOOLEAN_TRUE);
      }
   } while (!waiter_started);
   assert(sm_event_deinitialize(&event) == SM_BOOLEAN_TRUE);
   assert(sm_thread_join(&thread, NULL) == SM_BOOLEAN_TRUE);

   return 0;
}
