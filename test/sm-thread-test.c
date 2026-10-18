#include <sm-thread.h>
#include <sm-atomic-32.h>

#include <assert.h>

static SM_Atomic_32 detached_thread_done;

static void *return_argument(void *argument)
{
   return argument;
}

static void *mark_detached_thread_done(void *argument)
{
   (void)argument;
   sm_atomic_32_store(&detached_thread_done, 1);
   return NULL;
}

int main(void)
{
   SM_Thread thread;
   SM_Callback_Thread callback;
   void *argument;
   void *result;
   SM_Signed_32 done;

   argument = &thread;
   result = NULL;
   callback.function = return_argument;
   callback.argument = argument;
   assert(sm_thread_initialize(&thread, &callback) == SM_BOOLEAN_TRUE);
   assert(sm_thread_join(&thread, &result) == SM_BOOLEAN_TRUE);
   assert(result == argument);

   sm_atomic_32_initialize(&detached_thread_done, 0);
   callback.function = mark_detached_thread_done;
   callback.argument = NULL;
   assert(sm_thread_initialize(&thread, &callback) == SM_BOOLEAN_TRUE);
   assert(sm_thread_detach(&thread) == SM_BOOLEAN_TRUE);
   do {
      sm_atomic_32_load(&detached_thread_done, &done);
      if (!done) {
         assert(sm_thread_sleep(1) == SM_BOOLEAN_TRUE);
         sm_thread_yield();
      }
   } while (!done);

   assert(sm_thread_sleep(0) == SM_BOOLEAN_TRUE);
   sm_thread_yield();

   return 0;
}
