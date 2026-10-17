#include <sm-once.h>

#ifdef _WIN32
typedef struct SM_Once_Context {
   SM_Once_Function function;
} SM_Once_Context;

static BOOL CALLBACK sm_once_entry(PINIT_ONCE once, PVOID parameter, PVOID *context)
{
   SM_Once_Context *once_context;

   (void)once;
   (void)context;
   once_context = (SM_Once_Context *)parameter;
   once_context->function();
   return TRUE;
}
#endif /* _WIN32 */

SM_Boolean sm_once(SM_Once *this, SM_Once_Function function)
{
#ifdef _WIN32
   SM_Once_Context context;

   context.function = function;
   if (!InitOnceExecuteOnce(this, sm_once_entry, &context, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_once(this, function)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}
