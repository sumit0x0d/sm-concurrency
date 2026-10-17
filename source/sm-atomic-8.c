#include <sm-atomic-8.h>

void sm_atomic_8_initialize(SM_Atomic_8 *this, SM_Signed_8 initial_value)
{
#ifdef _WIN32
   InterlockedExchange8(this, (CHAR)initial_value);
#else
   __atomic_store_n(this, initial_value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_8_load(SM_Atomic_8 *this, SM_Signed_8 *value)
{
#ifdef _WIN32
   *value = (SM_Signed_8)InterlockedCompareExchange8(this, 0, 0);
#else
   *value = __atomic_load_n(this, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_8_store(SM_Atomic_8 *this, SM_Signed_8 value)
{
#ifdef _WIN32
   InterlockedExchange8(this, (CHAR)value);
#else
   __atomic_store_n(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

void sm_atomic_8_exchange(SM_Atomic_8 *this, SM_Signed_8 value, SM_Signed_8 *previous_value)
{
#ifdef _WIN32
   *previous_value = (SM_Signed_8)InterlockedExchange8(this, (CHAR)value);
#else
   *previous_value = __atomic_exchange_n(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}

SM_Boolean sm_atomic_8_compare_exchange(SM_Atomic_8 *this, SM_Signed_8 *expected_value, SM_Signed_8 desired_value)
{
#ifdef _WIN32
   CHAR observed_value;

   observed_value = InterlockedCompareExchange8(this, (CHAR)desired_value, (CHAR)*expected_value);
   if (observed_value != (CHAR)*expected_value) {
      *expected_value = (SM_Signed_8)observed_value;
      return SM_BOOLEAN_FALSE;
   }
#else
   if (!__atomic_compare_exchange_n(this, expected_value, desired_value, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

void sm_atomic_8_fetch_add(SM_Atomic_8 *this, SM_Signed_8 value, SM_Signed_8 *previous_value)
{
#ifdef _WIN32
   *previous_value = (SM_Signed_8)InterlockedExchangeAdd8(this, (CHAR)value);
#else
   *previous_value = __atomic_fetch_add(this, value, __ATOMIC_SEQ_CST);
#endif /* _WIN32 */
}
