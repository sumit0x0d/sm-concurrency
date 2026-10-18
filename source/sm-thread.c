#ifndef _WIN32
#include <errno.h>
#include <sched.h>
#include <time.h>
#else
#include <stdlib.h>
#endif /* !_WIN32 */

#include <sm-thread.h>

#define SM_THREAD_MILLISECOND_PER_SECOND 1000U
#define SM_THREAD_NANOSECOND_PER_MILLISECOND 1000000L

#ifdef _WIN32
typedef struct SM_Thread_Context {
   HANDLE handle;
   SM_Callback_Thread *callback_thread;
   SM_Boolean detached;
   struct SM_Thread_Context *next;
} SM_Thread_Context;

static SRWLOCK sm_thread_context_lock = SRWLOCK_INIT;
static SM_Thread_Context *sm_thread_contexts;

static void sm_thread_context_insert(SM_Thread_Context *context)
{
   AcquireSRWLockExclusive(&sm_thread_context_lock);
   context->next = sm_thread_contexts;
   sm_thread_contexts = context;
   ReleaseSRWLockExclusive(&sm_thread_context_lock);
}

static SM_Thread_Context *sm_thread_context_remove(HANDLE handle)
{
   SM_Thread_Context **context_link;
   SM_Thread_Context *context;

   context = NULL;
   AcquireSRWLockExclusive(&sm_thread_context_lock);
   context_link = &sm_thread_contexts;
   while (*context_link != NULL) {
      if ((*context_link)->handle == handle) {
         context = *context_link;
         *context_link = context->next;
         break;
      }
      context_link = &(*context_link)->next;
   }
   ReleaseSRWLockExclusive(&sm_thread_context_lock);

   return context;
}

static DWORD WINAPI sm_thread_entry(LPVOID argument)
{
   SM_Callback_Thread *callback_thread;

   callback_thread = (SM_Callback_Thread *)argument;
   callback_thread->result = callback_thread->function(callback_thread->argument);

   return 0;
}
#else
static void *sm_thread_entry(void *argument)
{
   SM_Callback_Thread *callback_thread;

   callback_thread = (SM_Callback_Thread *)argument;
   callback_thread->result = callback_thread->function(callback_thread->argument);

   return callback_thread->result;
}
#endif /* _WIN32 */

SM_Boolean sm_thread_initialize(SM_Thread *this, SM_Callback_Thread *callback_thread)
{
#ifdef _WIN32
   SM_Thread_Context *context;
#endif /* _WIN32 */

   callback_thread->result = NULL;

#ifdef _WIN32
   context = (SM_Thread_Context *)malloc(sizeof(*context));
   if (context == NULL) {
      return SM_BOOLEAN_FALSE;
   }

   context->callback_thread = callback_thread;
   context->detached = SM_BOOLEAN_FALSE;
   context->next = NULL;
   context->handle = CreateThread(NULL, 0, sm_thread_entry, callback_thread, 0, NULL);
   if (context->handle == NULL) {
      free(context);
      return SM_BOOLEAN_FALSE;
   }

   sm_thread_context_insert(context);

   *this = context->handle;
#else
   if (pthread_create(this, NULL, sm_thread_entry, callback_thread)) {
      return SM_BOOLEAN_FALSE;
   }
#endif /* _WIN32 */

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_thread_join(SM_Thread *this, void **result)
{
#ifdef _WIN32
   SM_Thread_Context *context;
   HANDLE handle;
#endif /* _WIN32 */

   if (this == NULL) {
      return SM_BOOLEAN_FALSE;
   }

#ifdef _WIN32
   handle = *this;
   if (handle == NULL) {
      return SM_BOOLEAN_FALSE;
   }

   if (WaitForSingleObject(handle, INFINITE) != WAIT_OBJECT_0) {
      return SM_BOOLEAN_FALSE;
   }

   context = sm_thread_context_remove(handle);
   if (context == NULL) {
      return SM_BOOLEAN_FALSE;
   }

   if (context->detached) {
      free(context);
      return SM_BOOLEAN_FALSE;
   }

   if (!CloseHandle(handle)) {
      sm_thread_context_insert(context);
      return SM_BOOLEAN_FALSE;
   }

   if (result != NULL) {
      *result = context->callback_thread->result;
   }

   *this = NULL;
   free(context);
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
   SM_Thread_Context *context;
   HANDLE handle;
#endif /* _WIN32 */

   if (this == NULL) {
      return SM_BOOLEAN_FALSE;
   }

#ifdef _WIN32
   handle = *this;
   if (handle == NULL) {
      return SM_BOOLEAN_FALSE;
   }

   context = sm_thread_context_remove(handle);
   if (context == NULL) {
      return SM_BOOLEAN_FALSE;
   }

   context->detached = SM_BOOLEAN_TRUE;

   if (!CloseHandle(handle)) {
      context->detached = SM_BOOLEAN_FALSE;
      sm_thread_context_insert(context);
      return SM_BOOLEAN_FALSE;
   }

   *this = NULL;
   free(context);
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