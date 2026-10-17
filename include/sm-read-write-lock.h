#ifndef SM_READ_WRITE_LOCK_H
#define SM_READ_WRITE_LOCK_H

#ifdef _WIN32
   #include <windows.h>
#else
   #include <pthread.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
typedef SRWLOCK SM_Read_Write_Lock;
#else
typedef pthread_rwlock_t SM_Read_Write_Lock;
#endif /* _WIN32 */

SM_API SM_Boolean sm_read_write_lock_initialize(SM_Read_Write_Lock *this);

SM_API SM_Boolean sm_read_write_lock_deinitialize(SM_Read_Write_Lock *this);

SM_API SM_Boolean sm_read_write_lock_read_lock(SM_Read_Write_Lock *this);

SM_API SM_Boolean sm_read_write_lock_try_read_lock(SM_Read_Write_Lock *this);

SM_API SM_Boolean sm_read_write_lock_read_unlock(SM_Read_Write_Lock *this);

SM_API SM_Boolean sm_read_write_lock_write_lock(SM_Read_Write_Lock *this);

SM_API SM_Boolean sm_read_write_lock_try_write_lock(SM_Read_Write_Lock *this);

SM_API SM_Boolean sm_read_write_lock_write_unlock(SM_Read_Write_Lock *this);

#endif /* SM_READ_WRITE_LOCK_H */
