#ifndef SM_THREAD_H
#define SM_THREAD_H

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

typedef struct SM_Callback_Thread {
#ifdef _WIN32
   DWORD (WINAPI *function)(LPVOID);
#else
   void *(*function)(void *);
#endif /* _WIN32 */
   void *argument;
   void *result;
} SM_Callback_Thread;

#ifdef _WIN32
typedef HANDLE SM_Thread;
#else
typedef pthread_t SM_Thread;
#endif /* _WIN32 */

SM_API SM_Boolean sm_thread_initialize(SM_Thread *this, SM_Callback_Thread *callback_thread);

SM_API SM_Boolean sm_thread_join(SM_Thread *this, void **result);

SM_API SM_Boolean sm_thread_detach(SM_Thread *this);

SM_API void sm_thread_yield(void);

SM_API SM_Boolean sm_thread_sleep(SM_Unsigned_32 milliseconds);

#endif /* SM_THREAD_H */
