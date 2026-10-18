#ifndef SM_COUNTDOWN_LATCH_H
#define SM_COUNTDOWN_LATCH_H

#include <sm-api.h>
#include <sm-condition-variable.h>
#include <sm-mutex.h>
#include <sm-typedef.h>

typedef struct SM_Countdown_Latch {
   SM_Mutex mutex;
   SM_Condition_Variable condition;
   SM_Unsigned_32 count;
   SM_Unsigned_32 active_waiter_count;
   SM_Boolean active;
} SM_Countdown_Latch;

SM_API SM_Boolean sm_countdown_latch_initialize(SM_Countdown_Latch *this, SM_Unsigned_32 count);

SM_API SM_Boolean sm_countdown_latch_deinitialize(SM_Countdown_Latch *this);

SM_API SM_Boolean sm_countdown_latch_count_down(SM_Countdown_Latch *this, SM_Unsigned_32 count);

SM_API SM_Boolean sm_countdown_latch_wait(SM_Countdown_Latch *this);

#endif /* SM_COUNTDOWN_LATCH_H */
