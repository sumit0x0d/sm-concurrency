#include <sm-atomic-8.h>

#include <assert.h>

int main(void)
{
   SM_Atomic_8 atomic;
   SM_Signed_8 value;
   SM_Signed_8 expected;
   SM_Signed_8 previous;

   sm_atomic_8_initialize(&atomic, 10);
   sm_atomic_8_load(&atomic, &value);
   assert(value == 10);
   sm_atomic_8_store(&atomic, 20);
   sm_atomic_8_exchange(&atomic, 30, &previous);
   assert(previous == 20);
   expected = 30;
   assert(sm_atomic_8_compare_exchange(&atomic, &expected, 40) == SM_BOOLEAN_TRUE);
   expected = 30;
   assert(sm_atomic_8_compare_exchange(&atomic, &expected, 50) == SM_BOOLEAN_FALSE);
   assert(expected == 40);
   sm_atomic_8_fetch_add(&atomic, 2, &previous);
   assert(previous == 40);
   sm_atomic_8_load(&atomic, &value);
   assert(value == 42);

   return 0;
}
