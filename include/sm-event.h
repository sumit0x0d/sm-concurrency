#ifndef SM_EVENT_H
#define SM_EVENT_H

#include <sm-api.h>
#include <sm-typedef.h>

typedef struct SM_Event SM_Event;

SM_API SM_Boolean sm_event_create(SM_Event *this, SM_Boolean initially_signaled);

SM_API SM_Boolean sm_event_destroy(SM_Event *this);

SM_API SM_Boolean sm_event_set(SM_Event *this);

SM_API SM_Boolean sm_event_reset(SM_Event *this);

SM_API SM_Boolean sm_event_wait(SM_Event *this);

#endif
