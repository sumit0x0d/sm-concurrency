#ifndef SM_SPINLOCK_H
#define SM_SPINLOCK_H

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
typedef volatile LONG SM_Spinlock;
#else
typedef pthread_spinlock_t SM_Spinlock;
#endif /* _WIN32 */

SM_API SM_Boolean sm_spinlock_initialize(SM_Spinlock *this);

SM_API SM_Boolean sm_spinlock_deinitialize(SM_Spinlock *this);

SM_API SM_Boolean sm_spinlock_lock(SM_Spinlock *this);

SM_API SM_Boolean sm_spinlock_try_lock(SM_Spinlock *this);

SM_API SM_Boolean sm_spinlock_unlock(SM_Spinlock *this);

#endif /* SM_SPINLOCK_H */
