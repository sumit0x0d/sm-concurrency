#ifndef SM_READ_WRITE_LOCK_H
#define SM_READ_WRITE_LOCK_H

#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
   #include <windows.h>
   typedef SRWLOCK SM_Read_Write_Lock;
#else
   #include <pthread.h>
   typedef pthread_rwlock_t SM_Read_Write_Lock;
#endif

SM_API SM_Boolean sm_read_write_lock_create(SM_Read_Write_Lock *this);
SM_API SM_Boolean sm_read_write_lock_destroy(SM_Read_Write_Lock *this);
SM_API SM_Boolean sm_read_write_lock_read_lock(SM_Read_Write_Lock *this);
SM_API SM_Boolean sm_read_write_lock_try_read_lock(SM_Read_Write_Lock *this);
SM_API SM_Boolean sm_read_write_lock_read_unlock(SM_Read_Write_Lock *this);
SM_API SM_Boolean sm_read_write_lock_write_lock(SM_Read_Write_Lock *this);
SM_API SM_Boolean sm_read_write_lock_try_write_lock(SM_Read_Write_Lock *this);
SM_API SM_Boolean sm_read_write_lock_write_unlock(SM_Read_Write_Lock *this);

#endif