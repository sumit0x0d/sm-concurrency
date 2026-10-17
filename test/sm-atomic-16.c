#include <sm-atomic-16.h>

#include <assert.h>

int main(void)
{
   SM_Atomic_16 atomic;
   SM_Signed_16 value;
   SM_Signed_16 expected;
   SM_Signed_16 previous;

   sm_atomic_16_create(&atomic, 1000);
   sm_atomic_16_load(&atomic, &value);
   assert(value == 1000);
   sm_atomic_16_store(&atomic, 2000);
   sm_atomic_16_exchange(&atomic, 3000, &previous);
   assert(previous == 2000);
   expected = 3000;
   assert(sm_atomic_16_compare_exchange(&atomic, &expected, 4000) == SM_BOOLEAN_TRUE);
   expected = 3000;
   assert(sm_atomic_16_compare_exchange(&atomic, &expected, 5000) == SM_BOOLEAN_FALSE);
   assert(expected == 4000);
   sm_atomic_16_fetch_add(&atomic, 2, &previous);
   assert(previous == 4000);
   sm_atomic_16_load(&atomic, &value);
   assert(value == 4002);

   return 0;
}
