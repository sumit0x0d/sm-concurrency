#include "sm-lock.h"

#include <assert.h>
#include <errno.h>

int main(void)
{
    SM_Mutex *lock = sm_mutex_create();

    assert(sm_mutex_init(NULL) == EINVAL);
    assert(sm_mutex_lock(NULL) == EINVAL);
    assert(sm_mutex_try_lock(NULL) == EINVAL);
    assert(sm_mutex_unlock(NULL) == EINVAL);
    assert(sm_mutex_destroy(NULL) == EINVAL);

    assert(sm_mutex_init(lock) == 0);
    assert(sm_mutex_try_lock(lock) == 0);
    assert(sm_mutex_try_lock(lock) == 0);
    assert(sm_mutex_unlock(lock) == 0);
    assert(sm_mutex_unlock(lock) == 0);
    assert(sm_mutex_lock(lock) == 0);
    assert(sm_mutex_unlock(lock) == 0);
    assert(sm_mutex_destroy(lock) == 0);

    return 0;
}