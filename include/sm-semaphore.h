#ifndef SM_SEMAPHORE_H
#define SM_SEMAPHORE_H

#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
    #include <windows.h>
    typedef HANDLE SM_Semaphore;
#else
    #include <semaphore.h>
    typedef sem_t SM_Semaphore;
#endif

SM_API SM_Boolean sm_semaphore_create(SM_Semaphore *this, SM_Unsigned_32 initial_value);
SM_API SM_Boolean sm_semaphore_destroy(SM_Semaphore *this);
SM_API SM_Boolean sm_semaphore_wait(SM_Semaphore *this);
SM_API SM_Boolean sm_semaphore_try_wait(SM_Semaphore *this);
SM_API SM_Boolean sm_semaphore_post(SM_Semaphore *this);

#endif
