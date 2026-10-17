#include <sm-thread-local.h>

SM_Boolean sm_thread_local_create(SM_Thread_Local *this)
{
#ifdef _WIN32
   *this = TlsAlloc();
   if (*this == TLS_OUT_OF_INDEXES) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_key_create(this, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_thread_local_destroy(SM_Thread_Local *this)
{
#ifdef _WIN32
   if (!TlsFree(*this)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_key_delete(*this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_thread_local_set(SM_Thread_Local *this, void *value)
{
#ifdef _WIN32
   if (!TlsSetValue(*this, value)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_setspecific(*this, value)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

void *sm_thread_local_get(SM_Thread_Local *this)
{
#ifdef _WIN32
   return TlsGetValue(*this);
#else
   return pthread_getspecific(*this);
#endif
}
