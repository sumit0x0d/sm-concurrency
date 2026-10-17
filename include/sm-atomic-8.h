#ifndef SM_ATOMIC_8_H
#define SM_ATOMIC_8_H

#ifdef _WIN32
#include <windows.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
typedef volatile CHAR SM_Atomic_8;
#else
typedef volatile SM_Signed_8 SM_Atomic_8;
#endif /* _WIN32 */

SM_API void sm_atomic_8_initialize(SM_Atomic_8 *this, SM_Signed_8 initial_value);

SM_API void sm_atomic_8_load(SM_Atomic_8 *this, SM_Signed_8 *value);

SM_API void sm_atomic_8_store(SM_Atomic_8 *this, SM_Signed_8 value);

SM_API void sm_atomic_8_exchange(SM_Atomic_8 *this, SM_Signed_8 value, SM_Signed_8 *previous_value);

SM_API SM_Boolean sm_atomic_8_compare_exchange(SM_Atomic_8 *this, SM_Signed_8 *expected_value, SM_Signed_8 desired_value);

SM_API void sm_atomic_8_fetch_add(SM_Atomic_8 *this, SM_Signed_8 value, SM_Signed_8 *previous_value);

#endif /* SM_ATOMIC_8_H */
