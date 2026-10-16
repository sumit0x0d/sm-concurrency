#ifndef SM_MUTEX_H
#define SM_MUTEX_H

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
   #include <windows.h>
   typedef CRITICAL_SECTION SM_Mutex;
#else
   #include <pthread.h>
   typedef pthread_mutex_t SM_Mutex;
#endif

SM_API SM_Boolean sm_mutex_create(SM_Mutex *this);
SM_API SM_Boolean sm_mutex_destroy(SM_Mutex *this);
SM_API SM_Boolean sm_mutex_lock(SM_Mutex *this);
SM_API SM_Boolean sm_mutex_try_lock(SM_Mutex *this);
SM_API SM_Boolean sm_mutex_unlock(SM_Mutex *this);

#endif
