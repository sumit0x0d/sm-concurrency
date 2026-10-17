#ifndef SM_ATOMIC_16_H
#define SM_ATOMIC_16_H

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
#include <windows.h>
typedef volatile SHORT SM_Atomic_16;
#else
typedef volatile SM_Signed_16 SM_Atomic_16;
#endif

SM_API void sm_atomic_16_create(SM_Atomic_16 *this, SM_Signed_16 initial_value);

SM_API void sm_atomic_16_load(SM_Atomic_16 *this, SM_Signed_16 *value);

SM_API void sm_atomic_16_store(SM_Atomic_16 *this, SM_Signed_16 value);

SM_API void sm_atomic_16_exchange(SM_Atomic_16 *this, SM_Signed_16 value, SM_Signed_16 *previous_value);

SM_API SM_Boolean sm_atomic_16_compare_exchange(SM_Atomic_16 *this, SM_Signed_16 *expected_value, SM_Signed_16 desired_value);

SM_API void sm_atomic_16_fetch_add(SM_Atomic_16 *this, SM_Signed_16 value, SM_Signed_16 *previous_value);

#endif
