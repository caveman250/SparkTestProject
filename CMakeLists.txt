cmake_minimum_required(VERSION 3.28)

if (UNIX AND APPLE)
    project(Spark LANGUAGES C CXX OBJC OBJCXX)
else ()
    project(Spark LANGUAGES C CXX)
endif()

option(USE_EDITOR "" OFF)
option(DIST_BUILD "" OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Spark/build/cmake/")

include(MultiTarget)

function(message)
    if (NOT MESSAGE_QUIET)
        _message(${ARGN})
    endif()
endfunction()

add_compile_definitions(APP_DIR="${CMAKE_CURRENT_SOURCE_DIR}/app")
add_compile_definitions(ENGINE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Spark/engine")

include(ExternalTools)

#this breaks the build in VS and Xcode.
if(NOT CMAKE_CONFIGURATION_TYPES)
    set(REGEN_CMAKE_TARGET RegenCmake)
    add_custom_target(RegenCmake COMMAND echo Generating Project Files... & ${CMAKE_COMMAND} .
                                 WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

get_filename_component(ENGINE_ABSOLUTE_PATH Spark/engine/src ABSOLUTE)
get_filename_component(EDITOR_ABSOLUTE_PATH Spark/editor/src ABSOLUTE)
get_filename_component(APP_ABSOLUTE_PATH app/src ABSOLUTE)
execute_process(COMMAND ${PYTHON_EXE} SparkHeaderTool.py "${ENGINE_ABSOLUTE_PATH}:${EDITOR_ABSOLUTE_PATH}:${APP_ABSOLUTE_PATH}"
        RESULT_VARIABLE header_tool_result
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Spark/build/SparkHeaderTool)

if(NOT ${header_tool_result} EQUAL 0)
    message(FATAL_ERROR "Spark Header Tool failed with error code: ${header_tool_result}.")
endif()

add_subdirectory(Spark/engine)
add_subdirectory(Spark/editor)
add_subdirectory(Spark/Tools)

add_subdirectory(app)