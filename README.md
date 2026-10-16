# Concurrency Primitives (libsm-x)

## Mutex

`sm-mutex.h` exposes `SM_Mutex` and the `sm_mutex_create`, `sm_mutex_lock`,
`sm_mutex_try_lock`, `sm_mutex_unlock`, and `sm_mutex_destroy` functions.
Initialize caller-owned storage before use, and destroy it only after no thread
can access it. The mutex is nonrecursive. Functions return `SM_BOOLEAN_TRUE`
on success and `SM_BOOLEAN_FALSE` on failure.

## Atomics

`sm-atomic.h` provides 32-bit and 64-bit atomic values with create, load,
store, exchange, compare-exchange, and fetch-add operations. Operations return
an `SM_Boolean`; operations that produce a value write it through an output
parameter. Compare-exchange updates its expected-value parameter with the
observed value when the comparison fails. Operations use sequentially
consistent ordering.

## Barrier

`sm-barrier.h` provides a reusable barrier. Initialize it with the number of
participating threads; each thread calls `sm_barrier_wait` once per generation.
Destroy the barrier only after all participating threads have left it.

POSIX builds must link with the platform's pthread support (for example,
`-pthread` with GCC or Clang).
