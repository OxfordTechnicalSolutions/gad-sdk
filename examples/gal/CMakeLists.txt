cmake_minimum_required(VERSION 3.1)

# C++ Standard version. Minimum supported is C++11.
set(CMAKE_CXX_STANDARD 11)
# Explicitly set policy for _DIR behaviour
cmake_policy(SET CMP0074 NEW)

project(oxts-sdk-examples-gal VERSION 0.1.0)

if(NOT OXTS_SDK_DISABLE_BOOST)
    # Example 1 - My First GAD
    set(OXTS_SDK_EXAMPLES_GAL_STATIC my-first-gad-example)
    add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC} ./my-first-gad.cpp)
    target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC} 
        PUBLIC 
            oxts-sdk-gal-cpp
    )
    # Example 2 - Static Aiding
    set(OXTS_SDK_EXAMPLES_GAL_STATIC static-aiding-example)
    add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC} ./static-aiding.cpp)
    target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC} 
        PUBLIC 
            oxts-sdk-gal-cpp
    )
endif()
    
# Example 3 - Static Aiding No Boost
set(OXTS_SDK_EXAMPLES_GAL_STATIC_NO_BOOST static-aiding-no-boost-example)
add_executable(${OXTS_SDK_EXAMPLES_GAL_STATIC_NO_BOOST} ./static-aiding-no-boost.cpp)
target_link_libraries(${OXTS_SDK_EXAMPLES_GAL_STATIC_NO_BOOST} 
    PUBLIC 
        oxts-sdk-gal-cpp
)
