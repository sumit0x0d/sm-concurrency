#ifndef _WIN32
#include <errno.h>
#include <sched.h>
#include <time.h>
#endif /* !_WIN32 */

#include <sm-thread.h>

#define SM_THREAD_MILLISECOND_PER_SECOND 1000U
#define SM_THREAD_NANOSECOND_PER_MILLISECOND 1000000L
#define SM_THREAD_REFERENCE_COUNT 2U

#ifdef _WIN32
static DWORD WINAPI sm_thread_entry(LPVOID argument)
{
   SM_Thread *thread;

   thread = (SM_Thread *)argument;
   thread->context.result = thread->context.function(thread->context.argument);
   return 0;
}
#endif /* _WIN32 */

SM_Boolean sm_thread_initialize(SM_Thread *this, SM_Thread_Function function, void *argument)
{
#ifdef _WIN32
   if (this == NULL || function == NULL) {
      return SM_BOOLEAN_FALSE;
   }

   this->context.function = function;
   this->context.argument = argument;
   this->context.result = NULL;
   this->handle = CreateThread(NULL, 0, sm_thread_entry, this, 0, NULL);
   if (this->handle == NULL) {
      this->context.function = NULL;
      this->context.argument = NULL;
      this->context.result = NULL;
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_create(this, NULL, function, argument)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_thread_join(SM_Thread *this, void **result)
{
#ifdef _WIN32
   if (this == NULL || this->handle == NULL) {
      return SM_BOOLEAN_FALSE;
   }
   if (WaitForSingleObject(this->handle, INFINITE) != WAIT_OBJECT_0) {
      return SM_BOOLEAN_FALSE;
   }

   if (result != NULL) {
      *result = this->context.result;
   }

   if (!CloseHandle(this->handle)) {
      return SM_BOOLEAN_FALSE;
   }

   this->handle = NULL;
   this->context.function = NULL;
   this->context.argument = NULL;
   this->context.result = NULL;
#else
   if (pthread_join(*this, result)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_thread_detach(SM_Thread *this)
{
#ifdef _WIN32
   if (this == NULL || this->handle == NULL) {
      return SM_BOOLEAN_FALSE;
   }
   if (!CloseHandle(this->handle)) {
      return SM_BOOLEAN_FALSE;
   }

   this->handle = NULL;
   this->context.function = NULL;
   this->context.argument = NULL;
   this->context.result = NULL;
#else
   if (pthread_detach(*this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

void sm_thread_yield(void)
{
#ifdef _WIN32
   SwitchToThread();
#else
   sched_yield();
#endif /* _WIN32 */
}

SM_Boolean sm_thread_sleep(SM_Unsigned_32 milliseconds)
{
#ifdef _WIN32
   Sleep(milliseconds);
#else
   struct timespec remaining;
   struct timespec request;

   request.tv_sec = (time_t)(milliseconds / SM_THREAD_MILLISECOND_PER_SECOND);
   request.tv_nsec = (long)(milliseconds % SM_THREAD_MILLISECOND_PER_SECOND) * SM_THREAD_NANOSECOND_PER_MILLISECOND;

   while (nanosleep(&request, &remaining)) {
      if (errno != EINTR) {
         return SM_BOOLEAN_FALSE;
      }
      request = remaining;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}
