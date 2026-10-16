cmake_minimum_required(VERSION 3.22.1)

project(sm-concurrency-primitives
   VERSION 1.0.0
   DESCRIPTION "Concurrency Primitives (libsm-x)"
   LANGUAGES C
)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
   add_compile_options(/W4 /WX)
else()
   set(CMAKE_C_VISIBILITY_PRESET hidden)
   add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

find_package(Threads REQUIRED)
find_path(SM_CORE_INCLUDE_DIR
   NAMES sm-api.h
   HINTS "${CMAKE_CURRENT_SOURCE_DIR}/../sm-core/include")

if(NOT SM_CORE_INCLUDE_DIR OR NOT EXISTS "${SM_CORE_INCLUDE_DIR}/sm-typedef.h")
   message(FATAL_ERROR "Could not find sm-api.h and sm-typedef.h. Set SM_CORE_INCLUDE_DIR to the sm-core include directory.")
endif()

add_library(sm-concurrency-primitives
   SHARED
      "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-atomic.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-barrier.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-condition-variable.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-mutex.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-read-write-lock.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-semaphore.c"
      "${CMAKE_CURRENT_SOURCE_DIR}/source/sm-spinlock.c")
target_include_directories(sm-concurrency-primitives
   PUBLIC
      include
      "${SM_CORE_INCLUDE_DIR}")
target_link_libraries(sm-concurrency-primitives PUBLIC Threads::Threads)

include(GNUInstallDirs)

install(TARGETS sm-concurrency-primitives
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

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

      add_executable(sm-atomic-test test/sm-atomic.c)
      add_test(NAME sm-atomic COMMAND sm-atomic-test)
      target_link_libraries(sm-atomic-test PRIVATE sm-concurrency-primitives)

      add_executable(sm-barrier-test test/sm-barrier.c)
      add_test(NAME sm-barrier COMMAND sm-barrier-test)
      target_link_libraries(sm-barrier-test PRIVATE sm-concurrency-primitives)

      add_executable(sm-condition-variable-test test/sm-condition-variable.c)
      add_test(NAME sm-condition-variable COMMAND sm-condition-variable-test)
      target_link_libraries(sm-condition-variable-test PRIVATE sm-concurrency-primitives)

      add_executable(sm-mutex-test test/sm-mutex.c)
      add_test(NAME sm-mutex COMMAND sm-mutex-test)
      target_link_libraries(sm-mutex-test PRIVATE sm-concurrency-primitives)

      add_executable(sm-read-write-lock-test test/sm-read-write-lock.c)
      add_test(NAME sm-read-write-lock COMMAND sm-read-write-lock-test)
      target_link_libraries(sm-read-write-lock-test PRIVATE sm-concurrency-primitives)

      add_executable(sm-semaphore-test test/sm-semaphore.c)
      add_test(NAME sm-semaphore COMMAND sm-semaphore-test)
      target_link_libraries(sm-semaphore-test PRIVATE sm-concurrency-primitives)

      add_executable(sm-spinlock-test test/sm-spinlock.c)
      add_test(NAME sm-spinlock COMMAND sm-spinlock-test)
      target_link_libraries(sm-spinlock-test PRIVATE sm-concurrency-primitives)
   endif()
endif()
