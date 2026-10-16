#include <sm-mutex.h>

#include <assert.h>
#include <pthread.h>

#define THREAD_COUNT 4
#define ITERATION_COUNT 1000

static SM_Mutex mutex;
static SM_Signed_32 counter;

static void *increment_counter(void *argument)
{
   SM_Signed_32 index;

   (void)argument;
   for (index = 0; index < ITERATION_COUNT; index++) {
      assert(sm_mutex_lock(&mutex) == SM_BOOLEAN_TRUE);
      counter++;
      assert(sm_mutex_unlock(&mutex) == SM_BOOLEAN_TRUE);
   }
   return NULL;
}

int main(void)
{
   pthread_t threads[THREAD_COUNT];
   SM_Signed_32 index;

   counter = 0;
   assert(sm_mutex_create(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_mutex_try_lock(&mutex) == SM_BOOLEAN_TRUE);
   assert(sm_mutex_unlock(&mutex) == SM_BOOLEAN_TRUE);

   for (index = 0; index < THREAD_COUNT; index++) {
      assert(pthread_create(&threads[index], NULL, increment_counter, NULL) == 0);
   }
   for (index = 0; index < THREAD_COUNT; index++) {
      assert(pthread_join(threads[index], NULL) == 0);
   }

   assert(counter == THREAD_COUNT * ITERATION_COUNT);
   assert(sm_mutex_destroy(&mutex) == SM_BOOLEAN_TRUE);

   return 0;
}
