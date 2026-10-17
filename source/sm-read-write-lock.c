#include <sm-read-write-lock.h>

SM_Boolean sm_read_write_lock_initialize(SM_Read_Write_Lock *this)
{
#ifdef _WIN32
   InitializeSRWLock(this);
#else
   if (pthread_rwlock_init(this, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_read_write_lock_deinitialize(SM_Read_Write_Lock *this)
{
#ifdef _WIN32
   (void)this;
#else
   if (pthread_rwlock_deinitialize(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_read_write_lock_read_lock(SM_Read_Write_Lock *this)
{
#ifdef _WIN32
   AcquireSRWLockShared(this);
#else
   if (pthread_rwlock_rdlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_read_write_lock_try_read_lock(SM_Read_Write_Lock *this)
{
#ifdef _WIN32
   if (!TryAcquireSRWLockShared(this)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_rwlock_tryrdlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_read_write_lock_read_unlock(SM_Read_Write_Lock *this)
{
#ifdef _WIN32
   ReleaseSRWLockShared(this);
#else
   if (pthread_rwlock_unlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_read_write_lock_write_lock(SM_Read_Write_Lock *this)
{
#ifdef _WIN32
   AcquireSRWLockExclusive(this);
#else
   if (pthread_rwlock_wrlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_read_write_lock_try_write_lock(SM_Read_Write_Lock *this)
{
#ifdef _WIN32
   if (!TryAcquireSRWLockExclusive(this)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_rwlock_trywrlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_read_write_lock_write_unlock(SM_Read_Write_Lock *this)
{
#ifdef _WIN32
   ReleaseSRWLockExclusive(this);
#else
   if (pthread_rwlock_unlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}