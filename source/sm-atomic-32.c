#include <sm-atomic-32.h>

void sm_atomic_32_create(SM_Atomic_32 *this, SM_Signed_32 initial_value)
{
#ifdef _WIN32
   InterlockedExchange(this, (LONG)initial_value);
#else
   __atomic_store_n(this, initial_value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_32_load(SM_Atomic_32 *this, SM_Signed_32 *value)
{
#ifdef _WIN32
   *value = (SM_Signed_32)InterlockedCompareExchange(this, 0, 0);
#else
   *value = __atomic_load_n(this, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_32_store(SM_Atomic_32 *this, SM_Signed_32 value)
{
#ifdef _WIN32
   InterlockedExchange(this, (LONG)value);
#else
   __atomic_store_n(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_32_exchange(SM_Atomic_32 *this, SM_Signed_32 value, SM_Signed_32 *previous_value)
{
#ifdef _WIN32
   *previous_value = (SM_Signed_32)InterlockedExchange(this, (LONG)value);
#else
   *previous_value = __atomic_exchange_n(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

SM_Boolean sm_atomic_32_compare_exchange(SM_Atomic_32 *this, SM_Signed_32 *expected_value, SM_Signed_32 desired_value)
{
#ifdef _WIN32
   LONG observed_value;

   observed_value = InterlockedCompareExchange(this, (LONG)desired_value, (LONG)*expected_value);
   if (observed_value != (LONG)*expected_value) {
      *expected_value = (SM_Signed_32)observed_value;
      return SM_BOOLEAN_FALSE;
   }
#else
   if (!__atomic_compare_exchange_n(this, expected_value, desired_value, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

void sm_atomic_32_fetch_add(SM_Atomic_32 *this, SM_Signed_32 value, SM_Signed_32 *previous_value)
{
#ifdef _WIN32
   *previous_value = (SM_Signed_32)InterlockedExchangeAdd(this, (LONG)value);
#else
   *previous_value = __atomic_fetch_add(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}
