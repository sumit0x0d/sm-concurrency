#ifndef SM_THREAD_LOCAL_H
#define SM_THREAD_LOCAL_H

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
   #include <windows.h>
   typedef DWORD SM_Thread_Local;
#else
   #include <pthread.h>
   typedef pthread_key_t SM_Thread_Local;
#endif

SM_API SM_Boolean sm_thread_local_create(SM_Thread_Local *this);

SM_API SM_Boolean sm_thread_local_destroy(SM_Thread_Local *this);

SM_API SM_Boolean sm_thread_local_set(SM_Thread_Local *this, void *value);

SM_API void *sm_thread_local_get(SM_Thread_Local *this);

#endif
