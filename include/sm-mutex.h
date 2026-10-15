#ifndef SM_MUTEX_H
#define SM_MUTEX_H

#include <sm-api.h>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#include <pthread.h>
#endif

typedef struct {
#ifdef _WIN32
    CRITICAL_SECTION native_lock;
#else
    pthread_mutex_t native_lock;
#endif
} SM_Mutex;

SM_API SM_Mutex *sm_mutex_create(void);
SM_API int sm_mutex_destroy(SM_Mutex *this);
SM_API int sm_mutex_lock(SM_Mutex *this);
SM_API int sm_mutex_try_lock(SM_Mutex *this);
SM_API int sm_mutex_unlock(SM_Mutex *this);

#endif