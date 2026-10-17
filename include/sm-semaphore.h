#ifndef SM_SEMAPHORE_H
#define SM_SEMAPHORE_H

#ifdef _WIN32
#include <windows.h>
#else
#include <semaphore.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
typedef HANDLE SM_Semaphore;
#else
typedef sem_t SM_Semaphore;
#endif /* _WIN32 */

SM_API SM_Boolean sm_semaphore_create(SM_Semaphore *this, SM_Unsigned_32 initial_value);

SM_API SM_Boolean sm_semaphore_destroy(SM_Semaphore *this);

SM_API SM_Boolean sm_semaphore_wait(SM_Semaphore *this);

SM_API SM_Boolean sm_semaphore_try_wait(SM_Semaphore *this);

SM_API SM_Boolean sm_semaphore_post(SM_Semaphore *this);

#endif /* SM_SEMAPHORE_H */
