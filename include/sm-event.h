#ifndef SM_EVENT_H
#define SM_EVENT_H

#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include <sm-api.h>
#include <sm-typedef.h>
#include <sm-condition-variable.h>
#include <sm-mutex.h>

typedef struct SM_Event SM_Event;

SM_API SM_Boolean sm_event_create(SM_Event *this, SM_Boolean initially_signaled);

SM_API SM_Boolean sm_event_destroy(SM_Event *this);

SM_API SM_Boolean sm_event_set(SM_Event *this);

SM_API SM_Boolean sm_event_reset(SM_Event *this);

SM_API SM_Boolean sm_event_wait(SM_Event *this);

#endif
