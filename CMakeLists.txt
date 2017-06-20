#  :copyright: (c) 2015-2017 The Regents of the University of California.
#  :license: MIT, see LICENSE.md for more details.

cmake_minimum_required(VERSION 2.8)
project(lexi CXX)
enable_testing()

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
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /O0 /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Ox /Zi /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
        set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT /Zi /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
        set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
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
    src/detail/string.cpp
    src/detail/strtod.cpp
    src/bool.cpp
    src/char.cpp
    src/null.cpp
    src/float.cpp
    src/int.cpp
)

if(BUILD_STATIC)
    add_library(lexi STATIC ${SOURCE_FILES})
else()
    add_library(lexi SHARED ${SOURCE_FILES})
endif()
set(LEXI_LIBRARIES lexi)

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
    test/char.cpp
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
    include_directories(googletest/googletest/include)

    add_executable(lexi_tests ${TEST_FILES})
    target_link_libraries(lexi_tests
        gtest
        gtest_main
        ${LEXI_LIBRARIES}
    )
    # Need to specify proper exception handling for Windows.
    if(MSVC)
        set_target_properties(lexi_tests PROPERTIES
            COMPILE_OPTIONS "/EHsc"
        )
    endif()

    add_test(NAME lexi_tests
        COMMAND lexi_tests
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
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
