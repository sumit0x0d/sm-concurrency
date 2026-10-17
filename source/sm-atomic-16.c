#include <sm-atomic-16.h>

void sm_atomic_16_create(SM_Atomic_16 *this, SM_Signed_16 initial_value)
{
#ifdef _WIN32
   InterlockedExchange16(this, (SHORT)initial_value);
#else
   __atomic_store_n(this, initial_value, __ATOMIC_SEQ_CST);
#endif
}

void sm_atomic_16_load(SM_Atomic_16 *this, SM_Signed_16 *value)
{
#ifdef _WIN32
   *value = (SM_Signed_16)InterlockedCompareExchange16(this, 0, 0);
#else
   *value = __atomic_load_n(this, __ATOMIC_SEQ_CST);
#endif
}

void sm_atomic_16_store(SM_Atomic_16 *this, SM_Signed_16 value)
{
#ifdef _WIN32
   InterlockedExchange16(this, (SHORT)value);
#else
   __atomic_store_n(this, value, __ATOMIC_SEQ_CST);
#endif
}

void sm_atomic_16_exchange(SM_Atomic_16 *this, SM_Signed_16 value, SM_Signed_16 *previous_value)
{
#ifdef _WIN32
   *previous_value = (SM_Signed_16)InterlockedExchange16(this, (SHORT)value);
#else
   *previous_value = __atomic_exchange_n(this, value, __ATOMIC_SEQ_CST);
#endif
}

SM_Boolean sm_atomic_16_compare_exchange(SM_Atomic_16 *this, SM_Signed_16 *expected_value, SM_Signed_16 desired_value)
{
#ifdef _WIN32
   SHORT observed_value;

   observed_value = InterlockedCompareExchange16(this, (SHORT)desired_value, (SHORT)*expected_value);
   if (observed_value != (SHORT)*expected_value) {
      *expected_value = (SM_Signed_16)observed_value;
      return SM_BOOLEAN_FALSE;
   }
#else
   if (!__atomic_compare_exchange_n(this, expected_value, desired_value, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

void sm_atomic_16_fetch_add(SM_Atomic_16 *this, SM_Signed_16 value, SM_Signed_16 *previous_value)
{
#ifdef _WIN32
   *previous_value = (SM_Signed_16)InterlockedExchangeAdd16(this, (SHORT)value);
#else
   *previous_value = __atomic_fetch_add(this, value, __ATOMIC_SEQ_CST);
#endif
}
