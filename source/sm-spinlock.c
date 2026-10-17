#include <sm-spinlock.h>

SM_Boolean sm_spinlock_initialize(SM_Spinlock *this)
{
#ifdef _WIN32
   *this = 0;
#else
   if (pthread_spin_init(this, PTHREAD_PROCESS_PRIVATE)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_spinlock_deinitialize(SM_Spinlock *this)
{
#ifdef _WIN32
   (void)this;
#else
   if (pthread_spin_deinitialize(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_spinlock_lock(SM_Spinlock *this)
{
#ifdef _WIN32
   while (InterlockedCompareExchange(this, 1, 0)) {
   }
#else
   if (pthread_spin_lock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_spinlock_try_lock(SM_Spinlock *this)
{
#ifdef _WIN32
   if (InterlockedCompareExchange(this, 1, 0)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_spin_trylock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_spinlock_unlock(SM_Spinlock *this)
{
#ifdef _WIN32
   InterlockedExchange(this, 0);
#else
   if (pthread_spin_unlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}