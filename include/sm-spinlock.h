#ifndef SM_SPINLOCK_H
#define SM_SPINLOCK_H

#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
    #include <windows.h>
    typedef volatile LONG SM_Spinlock;
#else
    #include <pthread.h>
    typedef pthread_spinlock_t SM_Spinlock;
#endif

SM_API SM_Boolean sm_spinlock_create(SM_Spinlock *this);

SM_API SM_Boolean sm_spinlock_destroy(SM_Spinlock *this);

SM_API SM_Boolean sm_spinlock_lock(SM_Spinlock *this);

SM_API SM_Boolean sm_spinlock_try_lock(SM_Spinlock *this);

SM_API SM_Boolean sm_spinlock_unlock(SM_Spinlock *this);

#endif