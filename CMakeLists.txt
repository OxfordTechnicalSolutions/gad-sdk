cmake_minimum_required(VERSION 3.10)



project(oxts-sdk VERSION 2.0.1 LANGUAGES CXX C)

# Building and installation options
option(OXTS_SDK_BUILD_DOCS "Build SDK documentation." OFF)
option(OXTS_SDK_BUILD_TESTS "Enable unit test targets." OFF) 
option(OXTS_SDK_BUILD_EXAMPLES "Enable examples targets." ON) 
option(OXTS_SDK_BUILD_PYTHON "Build SDK Python wrapper." OFF) 

# Used for cpp linting by clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

get_filename_component(OXTS_SDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

include(sdk-management)

add_sdks()

if (OXTS_SDK_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (OXTS_SDK_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (OXTS_SDK_BUILD_PYTHON)
    add_subdirectory(oxts-sdk-py)
endif()
