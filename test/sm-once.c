#include <sm-once.h>
#include <sm-thread.h>

#include <assert.h>

#define THREAD_COUNT 4

static SM_Once once = SM_ONCE_INIT;
static SM_Signed_32 call_count;

static void initialize_once(void)
{
   call_count++;
}

static void *call_once(void *argument)
{
   (void)argument;
   assert(sm_once(&once, initialize_once) == SM_BOOLEAN_TRUE);
   return NULL;
}

int main(void)
{
   SM_Thread threads[THREAD_COUNT];
   SM_Unsigned_32 index;

   call_count = 0;
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_thread_create(&threads[index], call_once, NULL) == SM_BOOLEAN_TRUE);
   }
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(sm_thread_join(&threads[index], NULL) == SM_BOOLEAN_TRUE);
   }
   assert(call_count == 1);

   return 0;
}
