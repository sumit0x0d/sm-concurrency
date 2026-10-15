# Concurrency Primitives (libsm-x)

## Mutex lock

`sm-lock.h` exposes `sm_mutex_t` and the `sm_mutex_init`, `sm_mutex_lock`,
`sm_mutex_try_lock`, `sm_mutex_unlock`, and `sm_mutex_destroy` functions. On
Windows the implementation uses a `CRITICAL_SECTION`; on POSIX systems it
uses a `pthread_mutex_t`.

Initialize a lock before using it and destroy it only after no thread can
access it. The lock is recursive on both platforms, so the owning thread may
acquire it more than once and must unlock it the same number of times. Each
function returns `0` on success and a nonzero error code on failure.
`sm_mutex_try_lock` returns `EBUSY` when another thread holds the lock. POSIX
builds must link with the platform's pthread support (for example, `-pthread`
with GCC or Clang).
