#ifndef SM_TEST_THREAD_H
#define SM_TEST_THREAD_H

#include <sm-typedef.h>

#ifdef _WIN32
#include <windows.h>

typedef struct {
   HANDLE handle;
   void *(*function)(void *);
   void *argument;
} SM_Test_Thread;

static DWORD WINAPI sm_test_thread_entry(LPVOID argument)
{
   SM_Test_Thread *thread;

   thread = (SM_Test_Thread *)argument;
   thread->function(thread->argument);
   return 0;
}

static SM_Boolean sm_test_thread_create(
   SM_Test_Thread *thread,
   void *(*function)(void *),
   void *argument
)
{
   thread->function = function;
   thread->argument = argument;
   thread->handle = CreateThread(NULL, 0, sm_test_thread_entry, thread, 0, NULL);
   if (thread->handle == NULL) {
      return SM_BOOLEAN_FALSE;
   }
   return SM_BOOLEAN_TRUE;
}

static SM_Boolean sm_test_thread_join(SM_Test_Thread *thread)
{
   if (WaitForSingleObject(thread->handle, INFINITE) != WAIT_OBJECT_0) {
      return SM_BOOLEAN_FALSE;
   }
   if (!CloseHandle(thread->handle)) {
      return SM_BOOLEAN_FALSE;
   }
   return SM_BOOLEAN_TRUE;
}
#else
#include <pthread.h>

typedef pthread_t SM_Test_Thread;

static SM_Boolean sm_test_thread_create(
   SM_Test_Thread *thread,
   void *(*function)(void *),
   void *argument
)
{
   if (pthread_create(thread, NULL, function, argument)) {
      return SM_BOOLEAN_FALSE;
   }
   return SM_BOOLEAN_TRUE;
}

static SM_Boolean sm_test_thread_join(SM_Test_Thread *thread)
{
   if (pthread_join(*thread, NULL)) {
      return SM_BOOLEAN_FALSE;
   }
   return SM_BOOLEAN_TRUE;
}
#endif

#endif
