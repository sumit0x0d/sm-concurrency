#ifndef SM_THREAD_H
#define SM_THREAD_H

#include <sm-api.h>
#include <sm-typedef.h>

typedef void *(*SM_Thread_Function)(void *);

#ifdef _WIN32
#include <windows.h>

typedef struct SM_Thread {
   HANDLE handle;
   void *context;
} SM_Thread;
#else
#include <pthread.h>

typedef pthread_t SM_Thread;
#endif

SM_API SM_Boolean sm_thread_create(SM_Thread *this, SM_Thread_Function function, void *argument);

SM_API SM_Boolean sm_thread_join(SM_Thread *this, void **result);

SM_API SM_Boolean sm_thread_detach(SM_Thread *this);

SM_API void sm_thread_yield(void);

SM_API SM_Boolean sm_thread_sleep(SM_Unsigned_32 milliseconds);

#endif
