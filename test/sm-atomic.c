#include <sm-atomic.h>

#include <assert.h>

int main(void)
{
   SM_Atomic_32 atomic32;
   SM_Atomic_64 atomic64;
   SM_Signed_32 value32;
   SM_Signed_32 expected32;
   SM_Signed_32 previous32;
   SM_Atomic_64_Value value64;
   SM_Atomic_64_Value expected64;
   SM_Atomic_64_Value previous64;

   assert(sm_atomic_32_create(&atomic32, 10) == SM_BOOLEAN_TRUE);
   assert(sm_atomic_32_load(&atomic32, &value32) == SM_BOOLEAN_TRUE);
   assert(value32 == 10);
   assert(sm_atomic_32_store(&atomic32, 20) == SM_BOOLEAN_TRUE);
   assert(sm_atomic_32_exchange(&atomic32, 30, &previous32) == SM_BOOLEAN_TRUE);
   assert(previous32 == 20);
   expected32 = 30;
   assert(sm_atomic_32_compare_exchange(&atomic32, &expected32, 40) == SM_BOOLEAN_TRUE);
   assert(sm_atomic_32_load(&atomic32, &value32) == SM_BOOLEAN_TRUE);
   assert(value32 == 40);
   expected32 = 30;
   assert(sm_atomic_32_compare_exchange(&atomic32, &expected32, 50) == SM_BOOLEAN_FALSE);
   assert(expected32 == 40);
   assert(sm_atomic_32_fetch_add(&atomic32, 2, &previous32) == SM_BOOLEAN_TRUE);
   assert(previous32 == 40);
   assert(sm_atomic_32_load(&atomic32, &value32) == SM_BOOLEAN_TRUE);
   assert(value32 == 42);

   assert(sm_atomic_64_create(&atomic64, 100) == SM_BOOLEAN_TRUE);
   assert(sm_atomic_64_load(&atomic64, &value64) == SM_BOOLEAN_TRUE);
   assert(value64 == 100);
   assert(sm_atomic_64_store(&atomic64, 200) == SM_BOOLEAN_TRUE);
   assert(sm_atomic_64_exchange(&atomic64, 300, &previous64) == SM_BOOLEAN_TRUE);
   assert(previous64 == 200);
   expected64 = 300;
   assert(sm_atomic_64_compare_exchange(&atomic64, &expected64, 400) == SM_BOOLEAN_TRUE);
   assert(sm_atomic_64_load(&atomic64, &value64) == SM_BOOLEAN_TRUE);
   assert(value64 == 400);
   expected64 = 300;
   assert(sm_atomic_64_compare_exchange(&atomic64, &expected64, 500) == SM_BOOLEAN_FALSE);
   assert(expected64 == 400);
   assert(sm_atomic_64_fetch_add(&atomic64, 2, &previous64) == SM_BOOLEAN_TRUE);
   assert(previous64 == 400);
   assert(sm_atomic_64_load(&atomic64, &value64) == SM_BOOLEAN_TRUE);
   assert(value64 == 402);

   return 0;
}
