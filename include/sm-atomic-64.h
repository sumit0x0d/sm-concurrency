#ifndef SM_ATOMIC_64_H
#define SM_ATOMIC_64_H

#ifdef _WIN32
#include <windows.h>
#endif /* _WIN32 */

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
typedef LONG64 SM_Atomic_64_Value;
typedef volatile LONG64 SM_Atomic_64;
#else
typedef SM_Signed_64 SM_Atomic_64_Value;
typedef volatile SM_Signed_64 SM_Atomic_64;
#endif /* _WIN32 */

SM_API void sm_atomic_64_create(SM_Atomic_64 *this, SM_Atomic_64_Value initial_value);

SM_API void sm_atomic_64_load(SM_Atomic_64 *this, SM_Atomic_64_Value *value);

SM_API void sm_atomic_64_store(SM_Atomic_64 *this, SM_Atomic_64_Value value);

SM_API void sm_atomic_64_exchange(SM_Atomic_64 *this, SM_Atomic_64_Value value, SM_Atomic_64_Value *previous_value);

SM_API SM_Boolean sm_atomic_64_compare_exchange(SM_Atomic_64 *this, SM_Atomic_64_Value *expected_value, SM_Atomic_64_Value desired_value);

SM_API void sm_atomic_64_fetch_add(SM_Atomic_64 *this, SM_Atomic_64_Value value, SM_Atomic_64_Value *previous_value);

#endif /* SM_ATOMIC_64_H */
