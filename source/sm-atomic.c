#include <sm-atomic.h>

SM_Boolean sm_atomic_32_create(SM_Atomic_32 *this, SM_Signed_32 initial_value)
{
#ifdef _WIN32
   InterlockedExchange(this, (LONG)initial_value);
#else
   __atomic_store_n(this, initial_value, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_32_load(SM_Atomic_32 *this, SM_Signed_32 *value)
{
#ifdef _WIN32
   *value = (SM_Signed_32)InterlockedCompareExchange(this, 0, 0);
#else
   *value = __atomic_load_n(this, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_32_store(SM_Atomic_32 *this, SM_Signed_32 value)
{
#ifdef _WIN32
   InterlockedExchange(this, (LONG)value);
#else
   __atomic_store_n(this, value, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_32_exchange(SM_Atomic_32 *this, SM_Signed_32 value, SM_Signed_32 *previous_value)
{
#ifdef _WIN32
   *previous_value = (SM_Signed_32)InterlockedExchange(this, (LONG)value);
#else
   *previous_value = __atomic_exchange_n(this, value, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_32_compare_exchange(SM_Atomic_32 *this, SM_Signed_32 *expected_value, SM_Signed_32 desired_value)
{
#ifdef _WIN32
   LONG observed_value;

   observed_value = InterlockedCompareExchange(this, (LONG)desired_value, (LONG)*expected_value);
   if (observed_value == (LONG)*expected_value) {
      return SM_BOOLEAN_TRUE;
   }
   *expected_value = (SM_Signed_32)observed_value;
#else
   if (__atomic_compare_exchange_n(this, expected_value, desired_value, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
      return SM_BOOLEAN_TRUE;
   }
#endif

   return SM_BOOLEAN_FALSE;
}

SM_Boolean sm_atomic_32_fetch_add(SM_Atomic_32 *this, SM_Signed_32 value, SM_Signed_32 *previous_value)
{
#ifdef _WIN32
   *previous_value = (SM_Signed_32)InterlockedExchangeAdd(this, (LONG)value);
#else
   *previous_value = __atomic_fetch_add(this, value, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_64_create(SM_Atomic_64 *this, SM_Atomic_64_Value initial_value)
{
#ifdef _WIN32
   InterlockedExchange64(this, initial_value);
#else
   __atomic_store_n(this, initial_value, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_64_load(SM_Atomic_64 *this, SM_Atomic_64_Value *value)
{
#ifdef _WIN32
   *value = InterlockedCompareExchange64(this, 0, 0);
#else
   *value = __atomic_load_n(this, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_64_store(SM_Atomic_64 *this, SM_Atomic_64_Value value)
{
#ifdef _WIN32
   InterlockedExchange64(this, value);
#else
   __atomic_store_n(this, value, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_64_exchange(SM_Atomic_64 *this, SM_Atomic_64_Value value, SM_Atomic_64_Value *previous_value)
{
#ifdef _WIN32
   *previous_value = InterlockedExchange64(this, value);
#else
   *previous_value = __atomic_exchange_n(this, value, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_atomic_64_compare_exchange(SM_Atomic_64 *this, SM_Atomic_64_Value *expected_value, SM_Atomic_64_Value desired_value)
{
#ifdef _WIN32
   SM_Atomic_64_Value observed_value;

   observed_value = InterlockedCompareExchange64(this, desired_value, *expected_value);
   if (observed_value == *expected_value) {
      return SM_BOOLEAN_TRUE;
   }
   *expected_value = observed_value;
#else
   if (__atomic_compare_exchange_n(this, expected_value, desired_value, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
      return SM_BOOLEAN_TRUE;
   }
#endif

   return SM_BOOLEAN_FALSE;
}

SM_Boolean sm_atomic_64_fetch_add(SM_Atomic_64 *this, SM_Atomic_64_Value value, SM_Atomic_64_Value *previous_value)
{
#ifdef _WIN32
   *previous_value = InterlockedExchangeAdd64(this, value);
#else
   *previous_value = __atomic_fetch_add(this, value, __ATOMIC_SEQ_CST);
#endif

   return SM_BOOLEAN_TRUE;
}