#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif

#include <sm-thread.h>

#ifdef _WIN32
typedef struct SM_Thread_Context {
   SM_Thread_Function function;
   void *argument;
   void *result;
   volatile LONG references;
} SM_Thread_Context;

static void sm_thread_context_release(SM_Thread_Context *context)
{
   if (InterlockedDecrement(&context->references) == 0) {
      HeapFree(GetProcessHeap(), 0, context);
   }
}

static DWORD WINAPI sm_thread_entry(LPVOID argument)
{
   SM_Thread_Context *context;

   context = (SM_Thread_Context *)argument;
   context->result = context->function(context->argument);
   sm_thread_context_release(context);
   return 0;
}
#else
#include <errno.h>
#include <sched.h>
#include <time.h>
#endif

SM_Boolean sm_thread_create(SM_Thread *this, SM_Thread_Function function, void *argument)
{
#ifdef _WIN32
   SM_Thread_Context *context;

   context = (SM_Thread_Context *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(SM_Thread_Context));
   if (context == NULL) {
      return SM_BOOLEAN_FALSE;
   }
   context->function = function;
   context->argument = argument;
   context->references = 2;
   this->context = context;
   this->handle = CreateThread(NULL, 0, sm_thread_entry, context, 0, NULL);
   if (this->handle == NULL) {
      HeapFree(GetProcessHeap(), 0, context);
      this->context = NULL;
      return SM_BOOLEAN_FALSE;
   }
#else
   if (pthread_create(this, NULL, function, argument)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_thread_join(SM_Thread *this, void **result)
{
#ifdef _WIN32
   SM_Thread_Context *context;

   if (WaitForSingleObject(this->handle, INFINITE) != WAIT_OBJECT_0) {
      return SM_BOOLEAN_FALSE;
   }
   context = (SM_Thread_Context *)this->context;
   if (result != NULL) {
      *result = context->result;
   }
   if (!CloseHandle(this->handle)) {
      return SM_BOOLEAN_FALSE;
   }
   sm_thread_context_release(context);
   this->handle = NULL;
   this->context = NULL;
#else
   if (pthread_join(*this, result)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

SM_Boolean sm_thread_detach(SM_Thread *this)
{
#ifdef _WIN32
   SM_Thread_Context *context;

   if (!CloseHandle(this->handle)) {
      return SM_BOOLEAN_FALSE;
   }
   context = (SM_Thread_Context *)this->context;
   sm_thread_context_release(context);
   this->handle = NULL;
   this->context = NULL;
#else
   if (pthread_detach(*this)) {
      return SM_BOOLEAN_FALSE;
   }
#endif

   return SM_BOOLEAN_TRUE;
}

void sm_thread_yield(void)
{
#ifdef _WIN32
   SwitchToThread();
#else
   sched_yield();
#endif
}

SM_Boolean sm_thread_sleep(SM_Unsigned_32 milliseconds)
{
#ifdef _WIN32
   Sleep(milliseconds);
#else
   struct timespec remaining;
   struct timespec request;

   request.tv_sec = (time_t)(milliseconds / 1000);
   request.tv_nsec = (long)(milliseconds % 1000) * 1000000L;
   while (nanosleep(&request, &remaining)) {
      if (errno != EINTR) {
         return SM_BOOLEAN_FALSE;
      }
      request = remaining;
   }
#endif

   return SM_BOOLEAN_TRUE;
}
