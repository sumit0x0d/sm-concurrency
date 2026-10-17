#ifndef SM_THREAD_LOCAL_H
#define SM_THREAD_LOCAL_H

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
typedef DWORD SM_Thread_Local;
#else
typedef pthread_key_t SM_Thread_Local;
#endif /* _WIN32 */

SM_API SM_Boolean sm_thread_local_initialize(SM_Thread_Local *this);

SM_API SM_Boolean sm_thread_local_deinitialize(SM_Thread_Local *this);

SM_API SM_Boolean sm_thread_local_set(SM_Thread_Local *this, void *value);

SM_API void *sm_thread_local_get(SM_Thread_Local *this);

#endif /* SM_THREAD_LOCAL_H */
