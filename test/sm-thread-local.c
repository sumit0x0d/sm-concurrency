#include <sm-thread-local.h>
#include <sm-thread.h>

#include <assert.h>

static SM_Thread_Local thread_local;

static void *set_thread_local_value(void *argument)
{
   SM_Signed_32 *value;

   value = (SM_Signed_32 *)argument;
   assert(sm_thread_local_set(&thread_local, value) == SM_BOOLEAN_TRUE);
   assert(sm_thread_local_get(&thread_local) == value);
   return NULL;
}

int main(void)
{
   SM_Signed_32 main_value;
   SM_Thread thread;

   main_value = 42;
   assert(sm_thread_local_create(&thread_local) == SM_BOOLEAN_TRUE);
   assert(sm_thread_local_get(&thread_local) == NULL);

   assert(sm_thread_create(&thread, set_thread_local_value, &main_value) == SM_BOOLEAN_TRUE);
   assert(sm_thread_join(&thread, NULL) == SM_BOOLEAN_TRUE);

   assert(sm_thread_local_get(&thread_local) == NULL);
   assert(sm_thread_local_set(&thread_local, &main_value) == SM_BOOLEAN_TRUE);
   assert(sm_thread_local_get(&thread_local) == &main_value);

   assert(sm_thread_local_destroy(&thread_local) == SM_BOOLEAN_TRUE);
   return 0;
}
