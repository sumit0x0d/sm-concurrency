#ifndef SM_COUNTDOWN_LATCH_H
#define SM_COUNTDOWN_LATCH_H

#include <sm-api.h>
#include <sm-typedef.h>
#include <sm-condition-variable.h>
#include <sm-mutex.h>

typedef struct SM_Countdown_Latch SM_Countdown_Latch;

SM_API SM_Boolean sm_countdown_latch_create(SM_Countdown_Latch *this, SM_Unsigned_32 count);

SM_API SM_Boolean sm_countdown_latch_destroy(SM_Countdown_Latch *this);

SM_API SM_Boolean sm_countdown_latch_count_down(SM_Countdown_Latch *this, SM_Unsigned_32 count);

SM_API SM_Boolean sm_countdown_latch_wait(SM_Countdown_Latch *this);

#endif
