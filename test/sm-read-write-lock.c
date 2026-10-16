#include <sm-read-write-lock.h>

#include <assert.h>

int main(void)
{
   SM_Read_Write_Lock lock;

   assert(sm_read_write_lock_create(&lock) == SM_BOOLEAN_TRUE);

   assert(sm_read_write_lock_read_lock(&lock) == SM_BOOLEAN_TRUE);
   assert(sm_read_write_lock_try_write_lock(&lock) == SM_BOOLEAN_FALSE);
   assert(sm_read_write_lock_read_unlock(&lock) == SM_BOOLEAN_TRUE);

   assert(sm_read_write_lock_try_write_lock(&lock) == SM_BOOLEAN_TRUE);
   assert(sm_read_write_lock_try_read_lock(&lock) == SM_BOOLEAN_FALSE);
   assert(sm_read_write_lock_write_unlock(&lock) == SM_BOOLEAN_TRUE);

   assert(sm_read_write_lock_write_lock(&lock) == SM_BOOLEAN_TRUE);
   assert(sm_read_write_lock_write_unlock(&lock) == SM_BOOLEAN_TRUE);
   assert(sm_read_write_lock_read_lock(&lock) == SM_BOOLEAN_TRUE);
   assert(sm_read_write_lock_read_unlock(&lock) == SM_BOOLEAN_TRUE);
   assert(sm_read_write_lock_destroy(&lock) == SM_BOOLEAN_TRUE);

   return 0;
}