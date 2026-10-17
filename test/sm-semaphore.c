#include <sm-semaphore.h>

#include <assert.h>

int main(void)
{
   SM_Semaphore semaphore;

   assert(sm_semaphore_initialize(&semaphore, 0) == SM_BOOLEAN_TRUE);
   assert(sm_semaphore_try_wait(&semaphore) == SM_BOOLEAN_FALSE);
   assert(sm_semaphore_post(&semaphore) == SM_BOOLEAN_TRUE);
   assert(sm_semaphore_try_wait(&semaphore) == SM_BOOLEAN_TRUE);
   assert(sm_semaphore_post(&semaphore) == SM_BOOLEAN_TRUE);
   assert(sm_semaphore_wait(&semaphore) == SM_BOOLEAN_TRUE);
   assert(sm_semaphore_deinitialize(&semaphore) == SM_BOOLEAN_TRUE);

   return 0;
}