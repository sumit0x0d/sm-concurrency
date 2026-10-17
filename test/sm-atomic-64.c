#include <sm-atomic-64.h>

#include <assert.h>

int main(void)
{
   SM_Atomic_64 atomic;
   SM_Atomic_64_Value value;
   SM_Atomic_64_Value expected;
   SM_Atomic_64_Value previous;

   sm_atomic_64_create(&atomic, 100);
   sm_atomic_64_load(&atomic, &value);
   assert(value == 100);
   sm_atomic_64_store(&atomic, 200);
   sm_atomic_64_exchange(&atomic, 300, &previous);
   assert(previous == 200);
   expected = 300;
   assert(sm_atomic_64_compare_exchange(&atomic, &expected, 400) == SM_BOOLEAN_TRUE);
   expected = 300;
   assert(sm_atomic_64_compare_exchange(&atomic, &expected, 500) == SM_BOOLEAN_FALSE);
   assert(expected == 400);
   sm_atomic_64_fetch_add(&atomic, 2, &previous);
   assert(previous == 400);
   sm_atomic_64_load(&atomic, &value);
   assert(value == 402);

   return 0;
}
