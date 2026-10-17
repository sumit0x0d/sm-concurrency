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

int main(void)
{
   SM_Thread thread;

   assert(sm_event_initialize(&event, SM_BOOLEAN_FALSE) == SM_BOOLEAN_TRUE);
   assert(sm_thread_initialize(&thread, wait_for_event, NULL) == SM_BOOLEAN_TRUE);
   assert(sm_event_set(&event) == SM_BOOLEAN_TRUE);
   assert(sm_thread_join(&thread, NULL) == SM_BOOLEAN_TRUE);
   assert(sm_event_wait(&event) == SM_BOOLEAN_TRUE);
   assert(sm_event_reset(&event) == SM_BOOLEAN_TRUE);
   assert(sm_event_deinitialize(&event) == SM_BOOLEAN_TRUE);

   return 0;
}
