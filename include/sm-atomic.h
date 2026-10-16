#ifndef SM_ATOMIC_H
#define SM_ATOMIC_H

#include <sm-api.h>
#include <sm-typedef.h>

#ifdef _WIN32
#include <windows.h>
   typedef volatile LONG SM_Atomic_32;
   typedef LONG64 SM_Atomic_64_Value;
   typedef volatile LONG64 SM_Atomic_64;
#else
   typedef volatile SM_Signed_32 SM_Atomic_32;
   typedef SM_Signed_64 SM_Atomic_64_Value;
   typedef volatile SM_Signed_64 SM_Atomic_64;
#endif

SM_API SM_Boolean sm_atomic_32_create(SM_Atomic_32 *this, SM_Signed_32 initial_value);
SM_API SM_Boolean sm_atomic_32_load(SM_Atomic_32 *this, SM_Signed_32 *value);
SM_API SM_Boolean sm_atomic_32_store(SM_Atomic_32 *this, SM_Signed_32 value);
SM_API SM_Boolean sm_atomic_32_exchange(SM_Atomic_32 *this, SM_Signed_32 value, SM_Signed_32 *previous_value);
SM_API SM_Boolean sm_atomic_32_compare_exchange(SM_Atomic_32 *this, SM_Signed_32 *expected_value, SM_Signed_32 desired_value);
SM_API SM_Boolean sm_atomic_32_fetch_add(SM_Atomic_32 *this, SM_Signed_32 value, SM_Signed_32 *previous_value);

SM_API SM_Boolean sm_atomic_64_create(SM_Atomic_64 *this, SM_Atomic_64_Value initial_value);
SM_API SM_Boolean sm_atomic_64_load(SM_Atomic_64 *this, SM_Atomic_64_Value *value);
SM_API SM_Boolean sm_atomic_64_store(SM_Atomic_64 *this, SM_Atomic_64_Value value);
SM_API SM_Boolean sm_atomic_64_exchange(SM_Atomic_64 *this, SM_Atomic_64_Value value, SM_Atomic_64_Value *previous_value);
SM_API SM_Boolean sm_atomic_64_compare_exchange(SM_Atomic_64 *this, SM_Atomic_64_Value *expected_value, SM_Atomic_64_Value desired_value);
SM_API SM_Boolean sm_atomic_64_fetch_add(SM_Atomic_64 *this, SM_Atomic_64_Value value, SM_Atomic_64_Value *previous_value);

#endif