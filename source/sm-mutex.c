#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif
#include <sm-typedef.h>

#include "sm-mutex.h"

#include <errno.h>

SM_Mutex *sm_mutex_create(void)
{
    SM_Mutex *lock = malloc(sizeof(SM_Mutex));
    if (lock == NULL) {
        return NULL;
    }

#ifdef _WIN32
    if (!InitializeCriticalSectionAndSpinCount(&lock->native_lock, 0)) {
        DWORD error = GetLastError();
        free(lock);
        return error != ERROR_SUCCESS ? (int)error : EINVAL;
    }
    return lock;
#else
    pthread_mutexattr_t attributes;
    int result = pthread_mutexattr_init(&attributes);
    if (result != 0) {
        free(lock);
        return NULL;
    }

    result = pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_RECURSIVE);
    if (result == 0) {
        result = pthread_mutex_init(&lock->native_lock, &attributes);
    }

    int destroy_result = pthread_mutexattr_destroy(&attributes);
    if (result != 0) {
        free(lock);
        return NULL;
    }
    if (destroy_result != 0) {
        pthread_mutex_destroy(&lock->native_lock);
        free(lock);
        return destroy_result;
    }
    return lock;
#endif
}

int sm_mutex_destroy(SM_Mutex *lock)
{
    SM_Signed_32 result = 0;
    if (lock == NULL) {
        return EINVAL;
    }

#ifdef _WIN32
    DeleteCriticalSection(&lock->native_lock);
    return 0;
#else
    return pthread_mutex_destroy(&lock->native_lock);
#endif

    return 0;
}

int sm_mutex_lock(SM_Mutex *lock)
{
    if (lock == NULL) {
        return EINVAL;
    }

#ifdef _WIN32
    EnterCriticalSection(&lock->native_lock);
    return 0;
#else
    return pthread_mutex_lock(&lock->native_lock);
#endif
}

int sm_mutex_try_lock(SM_Mutex *lock)
{
    if (lock == NULL) {
        return EINVAL;
    }

#ifdef _WIN32
    return TryEnterCriticalSection(&lock->native_lock) ? 0 : EBUSY;
#else
    return pthread_mutex_trylock(&lock->native_lock);
#endif
}

int sm_mutex_unlock(SM_Mutex *lock)
{
    if (lock == NULL) {
        return EINVAL;
    }

#ifdef _WIN32
    LeaveCriticalSection(&lock->native_lock);
    return 0;
#else
    return pthread_mutex_unlock(&lock->native_lock);
#endif
}