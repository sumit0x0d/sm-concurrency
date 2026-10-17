#include <sm-atomic-32.h>

#include <assert.h>

int main(void)
{
   SM_Atomic_32 atomic;
   SM_Signed_32 value;
   SM_Signed_32 expected;
   SM_Signed_32 previous;

   sm_atomic_32_initialize(&atomic, 10);
   sm_atomic_32_load(&atomic, &value);
   assert(value == 10);
   sm_atomic_32_store(&atomic, 20);
   sm_atomic_32_exchange(&atomic, 30, &previous);
   assert(previous == 20);
   expected = 30;
   assert(sm_atomic_32_compare_exchange(&atomic, &expected, 40) == SM_BOOLEAN_TRUE);
   expected = 30;
   assert(sm_atomic_32_compare_exchange(&atomic, &expected, 50) == SM_BOOLEAN_FALSE);
   assert(expected == 40);
   sm_atomic_32_fetch_add(&atomic, 2, &previous);
   assert(previous == 40);
   sm_atomic_32_load(&atomic, &value);
   assert(value == 42);

   return 0;
}
