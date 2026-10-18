#ifndef SM_EVENT_H
#define SM_EVENT_H

#include <sm-api.h>
#include <sm-condition-variable.h>
#include <sm-mutex.h>
#include <sm-typedef.h>

typedef struct SM_Event {
   SM_Mutex mutex;
   SM_Condition_Variable condition;
   SM_Boolean signaled;
   SM_Unsigned_32 active_waiter_count;
   SM_Boolean active;
} SM_Event;

SM_API SM_Boolean sm_event_initialize(SM_Event *this, SM_Boolean initially_signaled);

SM_API SM_Boolean sm_event_deinitialize(SM_Event *this);

SM_API SM_Boolean sm_event_set(SM_Event *this);

SM_API SM_Boolean sm_event_reset(SM_Event *this);

SM_API SM_Boolean sm_event_wait(SM_Event *this);

#endif /* SM_EVENT_H */
