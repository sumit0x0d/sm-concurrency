#ifndef SM_ONCE_H
#define SM_ONCE_H

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
#include <windows.h>
typedef INIT_ONCE SM_Once;
#define SM_ONCE_INIT INIT_ONCE_STATIC_INIT
#else
#include <pthread.h>
typedef pthread_once_t SM_Once;
#define SM_ONCE_INIT PTHREAD_ONCE_INIT
#endif

typedef void (*SM_Once_Function)(void);

SM_API SM_Boolean sm_once(SM_Once *this, SM_Once_Function function);

#endif
