#include <sm-mutex.h>

SM_Boolean sm_mutex_initialize(SM_Mutex *this)
{
#ifdef _WIN32
   if (!InitializeCriticalSectionAndSpinCount(this, 0)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_mutex_init(this, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_mutex_deinitialize(SM_Mutex *this)
{
#ifdef _WIN32
   DeleteCriticalSection(this);
#else
   if (pthread_mutex_destroy(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_mutex_lock(SM_Mutex *this)
{
#ifdef _WIN32
   EnterCriticalSection(this);
#else
   if (pthread_mutex_lock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_mutex_try_lock(SM_Mutex *this)
{
#ifdef _WIN32
   if (!TryEnterCriticalSection(this)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_mutex_trylock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_mutex_unlock(SM_Mutex *this)
{
#ifdef _WIN32
   LeaveCriticalSection(this);
#else
   if (pthread_mutex_unlock(this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}
