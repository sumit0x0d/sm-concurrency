#include <sm-atomic-64.h>

void sm_atomic_64_initialize(SM_Atomic_64 *this, SM_Atomic_64_Value initial_value)
{
#ifdef _WIN32
   InterlockedExchange64(this, initial_value);
#else
   __atomic_store_n(this, initial_value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_64_load(SM_Atomic_64 *this, SM_Atomic_64_Value *value)
{
#ifdef _WIN32
   *value = InterlockedCompareExchange64(this, 0, 0);
#else
   *value = __atomic_load_n(this, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_64_store(SM_Atomic_64 *this, SM_Atomic_64_Value value)
{
#ifdef _WIN32
   InterlockedExchange64(this, value);
#else
   __atomic_store_n(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_64_exchange(SM_Atomic_64 *this, SM_Atomic_64_Value value, SM_Atomic_64_Value *previous_value)
{
#ifdef _WIN32
   *previous_value = InterlockedExchange64(this, value);
#else
   *previous_value = __atomic_exchange_n(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

SM_Boolean sm_atomic_64_compare_exchange(SM_Atomic_64 *this, SM_Atomic_64_Value *expected_value, SM_Atomic_64_Value desired_value)
{
#ifdef _WIN32
   SM_Atomic_64_Value observed_value;

   observed_value = InterlockedCompareExchange64(this, desired_value, *expected_value);
   if (observed_value != *expected_value) {
      *expected_value = observed_value;
      return SM_BOOLEAN_FALSE;
   }
#else
   if (!__atomic_compare_exchange_n(this, expected_value, desired_value, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

void sm_atomic_64_fetch_add(SM_Atomic_64 *this, SM_Atomic_64_Value value, SM_Atomic_64_Value *previous_value)
{
#ifdef _WIN32
   *previous_value = InterlockedExchangeAdd64(this, value);
#else
   *previous_value = __atomic_fetch_add(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}
