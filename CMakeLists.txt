#  :copyright: (c) 2015-2017 The Regents of the University of California.
#  :license: MIT, see LICENSE.md for more details.

cmake_minimum_required(VERSION 3.4)
project(Lexi CXX)

# FLAGS
# -----

set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD TRUE)

option(BUILD_STATIC "Build static library" ON)
option(BUILD_TESTS "Build Lexi library tests" OFF)
option(BUILD_FUZZ "Build fuzz testing" OFF)
option(BUILD_EXAMPLES "Build example files" OFF)

if(BUILD_STATIC)
    if(UNIX)
        set(CMAKE_POSITION_INDEPENDENT_CODE ON)
        add_definitions(-fPIC)
    elseif(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
    elseif(MSVC)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MTd /O0")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Ox")
    endif()
endif()

# LIBRARY
# -------

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SOURCE_FILES
    src/detail/bigint.cpp
    src/detail/diyfp.cpp
    src/detail/dtoa.cpp
    src/detail/ieee754.cpp
    src/detail/itoa.cpp
    src/detail/pow.cpp
    src/detail/strtod.cpp
    src/bool.cpp
    src/char.cpp
    src/null.cpp
    src/float.cpp
    src/int.cpp
    src/lexi.cpp
)

if(BUILD_STATIC)
    add_library(Lexi STATIC ${SOURCE_FILES})
else()
    add_library(Lexi SHARED ${SOURCE_FILES})
endif()
set_target_properties(Lexi PROPERTIES OUTPUT_NAME lexi)

# EXAMPLES
# --------

if(BUILD_EXAMPLES)
#    add_executable(JSONSimpleWriter example/simplewriter.cpp)
#    target_link_libraries(JSONSimpleWriter JSON)
endif()

# TESTS
# -----

set(TEST_FILES
    test/main.cpp
    test/bool.cpp
    test/enum.cpp
    test/float.cpp
    test/int.cpp
    test/lexi.cpp
    test/null.cpp
)

if(BUILD_TESTS)
    if(NOT TARGET gtest)
        add_subdirectory(googletest)
    endif()
    add_executable(LexiTests ${TEST_FILES})
    target_link_libraries(LexiTests
        gtest
        gtest_main
        Lexi
    )
    set_target_properties(LexiTests PROPERTIES OUTPUT_NAME test)

     add_custom_target(check_lexi
        COMMAND $<TARGET_FILE:LexiTests>
        DEPENDS LexiTests
    )
endif()


if(BUILD_FUZZ AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=bool -fsanitize-coverage=edge,8bit-counters,trace-cmp")
    if(NOT TARGET LLVMFuzzer)
        add_subdirectory(Fuzzer)
    endif()

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads)

    #add_executable(JSONFuzzReader test/fuzz/reader.cpp)
    #target_link_libraries(JSONFuzzReader LLVMFuzzer JSON Threads::Threads)
endif()
