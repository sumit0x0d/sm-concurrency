cmake_minimum_required(VERSION 3.22.1)

project(sm-concurrency
   VERSION 1.0.0
   DESCRIPTION "Concurrency (libsm-x)"
   LANGUAGES C
)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

if(MSVC)
   add_compile_options(/W4 /WX)
else()
   set(CMAKE_C_VISIBILITY_PRESET hidden)
   add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

find_package(Threads REQUIRED)

set(SM_CONCURRENCY_INCLUDE_DIRS
   "${CMAKE_CURRENT_SOURCE_DIR}/include"
   "${CMAKE_CURRENT_SOURCE_DIR}/../sm-core/include"
)

add_library(sm-atomic-8 SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-atomic-8.c")
target_include_directories(sm-atomic-8 PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})

add_library(sm-atomic-16 SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-atomic-16.c")
target_include_directories(sm-atomic-16 PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})

add_library(sm-atomic-32 SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-atomic-32.c")
target_include_directories(sm-atomic-32 PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})

add_library(sm-atomic-64 SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-atomic-64.c")
target_include_directories(sm-atomic-64 PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})

add_library(sm-mutex SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-mutex.c")
target_include_directories(sm-mutex PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-mutex PUBLIC ${CMAKE_THREAD_LIBS_INIT})

add_library(sm-mutex-static STATIC "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-mutex.c")
target_include_directories(sm-mutex-static PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-mutex-static PUBLIC ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(sm-mutex-static PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(sm-condition-variable SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-condition-variable.c")
target_include_directories(sm-condition-variable PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-condition-variable PUBLIC ${CMAKE_THREAD_LIBS_INIT})

add_library(sm-condition-variable-static STATIC "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-condition-variable.c")
target_include_directories(sm-condition-variable-static PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-condition-variable-static PUBLIC ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(sm-condition-variable-static PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(sm-barrier SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-barrier.c")
target_include_directories(sm-barrier PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-barrier PRIVATE sm-mutex-static sm-condition-variable-static)

add_library(sm-countdown-latch SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-countdown-latch.c")
target_include_directories(sm-countdown-latch PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-countdown-latch PRIVATE sm-mutex-static sm-condition-variable-static)

add_library(sm-event SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-event.c")
target_include_directories(sm-event PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-event PRIVATE sm-mutex-static sm-condition-variable-static)

add_library(sm-once SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-once.c")
target_include_directories(sm-once PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-once PUBLIC ${CMAKE_THREAD_LIBS_INIT})

add_library(sm-read-write-lock SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-read-write-lock.c")
target_include_directories(sm-read-write-lock PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-read-write-lock PUBLIC ${CMAKE_THREAD_LIBS_INIT})

add_library(sm-semaphore SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-semaphore.c")
target_include_directories(sm-semaphore PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-semaphore PUBLIC ${CMAKE_THREAD_LIBS_INIT})

add_library(sm-spinlock SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-spinlock.c")
target_include_directories(sm-spinlock PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})

add_library(sm-thread SHARED "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-thread.c")
target_include_directories(sm-thread PUBLIC ${SM_CONCURRENCY_INCLUDE_DIRS})
target_link_libraries(sm-thread PUBLIC ${CMAKE_THREAD_LIBS_INIT})

include(GNUInstallDirs)

install(TARGETS
   sm-atomic-8
   sm-atomic-16
   sm-atomic-32
   sm-atomic-64
   sm-barrier
   sm-condition-variable
   sm-countdown-latch
   sm-event
   sm-mutex
   sm-once
   sm-read-write-lock
   sm-semaphore
   sm-spinlock
   sm-thread
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
   DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
   include(CTest)

   if(BUILD_TESTING)
      if(MSVC)
         add_compile_options(/UNDEBUG)
      else()
         add_compile_options(-UNDEBUG)
      endif()

      add_executable(sm-atomic-8-test test/sm-atomic-8.c)
      add_test(NAME sm-atomic-8 COMMAND sm-atomic-8-test)
      target_link_libraries(sm-atomic-8-test PRIVATE sm-atomic-8)

      add_executable(sm-atomic-16-test test/sm-atomic-16.c)
      add_test(NAME sm-atomic-16 COMMAND sm-atomic-16-test)
      target_link_libraries(sm-atomic-16-test PRIVATE sm-atomic-16)

      add_executable(sm-atomic-32-test test/sm-atomic-32.c)
      add_test(NAME sm-atomic-32 COMMAND sm-atomic-32-test)
      target_link_libraries(sm-atomic-32-test PRIVATE sm-atomic-32)

      add_executable(sm-atomic-64-test test/sm-atomic-64.c)
      add_test(NAME sm-atomic-64 COMMAND sm-atomic-64-test)
      target_link_libraries(sm-atomic-64-test PRIVATE sm-atomic-64)

      add_executable(sm-barrier-test test/sm-barrier.c)
      add_test(NAME sm-barrier COMMAND sm-barrier-test)
      target_link_libraries(sm-barrier-test PRIVATE sm-barrier)

      add_executable(sm-condition-variable-test test/sm-condition-variable.c)
      add_test(NAME sm-condition-variable COMMAND sm-condition-variable-test)
      target_link_libraries(sm-condition-variable-test PRIVATE sm-condition-variable sm-mutex sm-thread)

      add_executable(sm-countdown-latch-test test/sm-countdown-latch.c)
      add_test(NAME sm-countdown-latch COMMAND sm-countdown-latch-test)
      target_link_libraries(sm-countdown-latch-test PRIVATE sm-countdown-latch sm-thread)

      add_executable(sm-event-test test/sm-event.c)
      add_test(NAME sm-event COMMAND sm-event-test)
      target_link_libraries(sm-event-test PRIVATE sm-event sm-thread)

      add_executable(sm-mutex-test test/sm-mutex.c)
      add_test(NAME sm-mutex COMMAND sm-mutex-test)
      target_link_libraries(sm-mutex-test PRIVATE sm-mutex)

      add_executable(sm-once-test test/sm-once.c)
      add_test(NAME sm-once COMMAND sm-once-test)
      target_link_libraries(sm-once-test PRIVATE sm-once sm-thread)

      add_executable(sm-read-write-lock-test test/sm-read-write-lock.c)
      add_test(NAME sm-read-write-lock COMMAND sm-read-write-lock-test)
      target_link_libraries(sm-read-write-lock-test PRIVATE sm-read-write-lock)

      add_executable(sm-semaphore-test test/sm-semaphore.c)
      add_test(NAME sm-semaphore COMMAND sm-semaphore-test)
      target_link_libraries(sm-semaphore-test PRIVATE sm-semaphore)

      add_executable(sm-spinlock-test test/sm-spinlock.c)
      add_test(NAME sm-spinlock COMMAND sm-spinlock-test)
      target_link_libraries(sm-spinlock-test PRIVATE sm-spinlock)

      add_executable(sm-thread-test test/sm-thread.c)
      add_test(NAME sm-thread COMMAND sm-thread-test)
      target_link_libraries(sm-thread-test PRIVATE sm-thread sm-atomic-32)
   endif()
endif()
