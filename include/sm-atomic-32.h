#ifndef SM_ATOMIC_32_H
#define SM_ATOMIC_32_H

#ifdef _WIN32
#include <windows.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
typedef volatile LONG SM_Atomic_32;
#else
typedef volatile SM_Signed_32 SM_Atomic_32;
#endif /* _WIN32 */

SM_API void sm_atomic_32_initialize(SM_Atomic_32 *this, SM_Signed_32 initial_value);

SM_API void sm_atomic_32_load(SM_Atomic_32 *this, SM_Signed_32 *value);

SM_API void sm_atomic_32_store(SM_Atomic_32 *this, SM_Signed_32 value);

SM_API void sm_atomic_32_exchange(SM_Atomic_32 *this, SM_Signed_32 value, SM_Signed_32 *previous_value);

SM_API SM_Boolean sm_atomic_32_compare_exchange(SM_Atomic_32 *this, SM_Signed_32 *expected_value, SM_Signed_32 desired_value);

SM_API void sm_atomic_32_fetch_add(SM_Atomic_32 *this, SM_Signed_32 value, SM_Signed_32 *previous_value);

#endif /* SM_ATOMIC_32_H */
