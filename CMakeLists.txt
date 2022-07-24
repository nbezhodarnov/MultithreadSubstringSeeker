cmake_minimum_required(VERSION 3.5)

project(MultithreadSubstringSeeker LANGUAGES CXX)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SUBSTRING_SEEKERS_LIBRARY_SOURCES multithreadqueue.h threadpool.h threadpool.cpp multithreadsubstringseeker.h multithreadsubstringseeker.cpp)

add_library(substringseekers SHARED ${SUBSTRING_SEEKERS_LIBRARY_SOURCES})
target_include_directories(substringseekers PRIVATE "${PROJECT_SOURCE_DIR}")

add_executable(mtfind main.cpp)
target_include_directories(mtfind PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(mtfind substringseekers)

enable_testing()
add_executable(SubstringSeekerTetser tests/substringseekertetser.h tests/substringseekertetser.cpp tests/main.cpp)
target_include_directories(SubstringSeekerTetser PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(SubstringSeekerTetser substringseekers)
add_test(NAME Test1 COMMAND SubstringSeekerTetser test1 "?ad")
add_test(NAME Test2 COMMAND SubstringSeekerTetser test2 "??ed?")
add_test(NAME Test3 COMMAND SubstringSeekerTetser test3 "n??my")
add_test(NAME Test4 COMMAND SubstringSeekerTetser test4 "?ed ")
add_test(NAME Test5 COMMAND SubstringSeekerTetser test5 "d?d")
add_test(NAME Test6 COMMAND SubstringSeekerTetser test6 "l?ls")
add_test(NAME Test7 COMMAND SubstringSeekerTetser test7 "c?mp?re")
