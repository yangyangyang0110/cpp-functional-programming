cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(cpp-functional-programming VERSION 1.0.0 LANGUAGES CXX)

#option(WITH_TESTING "Enable Testing" ON)

message(STATUS "Project name ${PROJECT_NAME} Version ${PROJECT_VERSION}")

string(TIMESTAMP build_time "%Y%m%d %H:%M:%S")
set(BUILD_TIME ${build_time})
set(PROJECT_META "META: Version: ${PROJECT_VERSION} BuildTime: ${BUILD_TIME}")


### Deps Manager.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(boost)
include(folly)

set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CONFIG_ROOT ${SRC_ROOT}/configs)

configure_file(${CONFIG_ROOT}/config.h.in ${CONFIG_ROOT}/config.h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(dynamic_build_execute prefix)
    foreach (example ${ARGN})
        get_filename_component(target ${example} NAME_WLE)
        string(REPLACE "_" "-" target ${target})
        if (NOT ${prefix} STREQUAL "")
            set(target "${prefix}-${target}")
        endif ()
        message(STATUS "build ${example} to ${target}...")
        add_executable(${target} ${example})
        
        target_compile_options(
            ${target}
            PRIVATE
            -Werror -fPIC
            $<$<CONFIG:Debug>:-g -O0>
            $<$<NOT:$<CONFIG:Debug>>:-O2>
            #                -ftemplate-depth=10000000
        )
        
        target_compile_definitions(
            ${target}
            PRIVATE
            $<$<CONFIG:Debug>:MyDebug>
        )
        
        target_link_libraries(
            ${target}
            PRIVATE
            pthread
            # TODO:
            ${Boost_LIBRARIES}
            Folly::folly
        )
    endforeach ()
endfunction()

add_subdirectory(src)
