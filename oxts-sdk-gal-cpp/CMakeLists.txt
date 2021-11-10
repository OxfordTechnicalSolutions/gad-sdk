cmake_minimum_required(VERSION 3.1)

cmake_policy(SET CMP0074 NEW)


# define library version 
set(OXTS_SDK_GAL_VERSION_MAJOR 0 CACHE STRING "major version" FORCE)
set(OXTS_SDK_GAL_VERSION_MINOR 1 CACHE STRING "minor version" FORCE)
set(OXTS_SDK_GAL_VERSION_PATCH 0 CACHE STRING "patch version" FORCE)
set(OXTS_SDK_GAL_VERSION 
${OXTS_SDK_GAL_VERSION_MAJOR}.${OXTS_SDK_GAL_VERSION_MINOR}.${OXTS_SDK_GAL_VERSION_PATCH} 
CACHE STRING "version" FORCE
)

project(oxts-sdk-gal-cpp VERSION ${OXTS_SDK_GAL_VERSION})
set(DESCRIPTION "Generic Aiding library for the OxTS SDK in C++.")

# If Boost isn't disabled, find it. If it can't be found, disable it.
if(NOT OXTS_SDK_DISABLE_BOOST)
    find_package(Boost COMPONENTS system thread regex)
    if(NOT Boost_FOUND)
        message(STATUS "Boost Library not found. Defaulting to build without Boost. UDP Socket functionality will not be built.")
        set(OXTS_SDK_DISABLE_BOOST ON)
    endif()
else()
    message(STATUS "Boost disabled.")
endif()

set(OXTS_GAL_CPP_HEADERS
    ./include/oxts/gal-cpp/gad.hpp
    ./include/oxts/gal-cpp/gad_encoders/gad_encoder.hpp
    ./include/oxts/gal-cpp/gad_encoders/gad_encoder_bin.hpp
    ./include/oxts/gal-cpp/gad_encoders/gad_encoder_csv.hpp
    ./include/oxts/gal-cpp/gad_output/gad_output.hpp
    ./include/oxts/gal-cpp/gad_output/gad_output_file.hpp
    ./include/oxts/gal-cpp/gad_output/gad_output_udp.hpp
    ./include/oxts/gal-cpp/gad_handler.hpp
    ./include/oxts/gal-cpp/udp_server_client.hpp
)

set(OXTS_GAL_CPP_SOURCES
    ./src/gal-cpp/gad.cpp
    ./src/gal-cpp/gad_handler.cpp
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/oxts/gal-cpp/config.h.in 
               ${CMAKE_CURRENT_BINARY_DIR}/include/oxts/gal-cpp/config.h @ONLY
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)
if(NOT OXTS_SDK_DISABLE_BOOST)
include_directories(${Boost_INCLUDE_DIR})
endif()



####
# Create targets
add_library(${PROJECT_NAME} #STATIC
    ${OXTS_GAL_CPP_HEADERS}
    ${OXTS_GAL_CPP_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${oxts-sdk-gal-c_INCLUDE_DIRS}
)
if(OXTS_SDK_DISABLE_BOOST)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            oxts-sdk-gal-c
    )
else()
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
            oxts-sdk-gal-c
            ${Boost_LIBRARIES}
    )
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE GAL_CPP_LIBRARY
)

# install (FILES ${OXTS_GAL_CPP_HEADERS} DESTINATION ${INCLUDE_DIRECTORY}/oxts/gal-cpp)
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/oxts/gal-cpp 
         DESTINATION ${INCLUDE_DIRECTORY}/oxts
)
# It's possible that this can be done more elegantly
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/include/oxts/gal-cpp/config.h 
         DESTINATION ${INCLUDE_DIRECTORY}/oxts/gal-cpp
)
message(STATUS "install prefix: ${CMAKE_INSTALL_PREFIX}")
export_config()

# TODO: Add testing
# if(OXTS_SDK_ENABLE_TESTING)
#     add_subdirectory(tests)
# endif()