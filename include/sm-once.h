#ifndef SM_ONCE_H
#define SM_ONCE_H

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
typedef INIT_ONCE SM_Once;
#define SM_ONCE_INIT INIT_ONCE_STATIC_INIT
#else
typedef pthread_once_t SM_Once;
#define SM_ONCE_INIT PTHREAD_ONCE_INIT
#endif /* _WIN32 */

typedef void (*SM_Once_Function)(void);

SM_API SM_Boolean sm_once(SM_Once *this, SM_Once_Function function);

#endif /* SM_ONCE_H */
