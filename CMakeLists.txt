cmake_minimum_required(VERSION 3.28)

if (UNIX AND APPLE)
    project(Spark LANGUAGES C CXX OBJC OBJCXX)
else ()
    project(Spark LANGUAGES C CXX)
endif()

option(USE_EDITOR "" OFF)

add_compile_definitions(APP_DIR="../../app")
add_compile_definitions(ENGINE_DIR="../../Spark/Engine")

include(./Spark/Cmake/ExternalTools.cmake)

# fake target used to generate additional code
set(SHT_TARGET SparkHeaderTool)
get_filename_component(ENGINE_ABSOLUTE_PATH Spark/Engine/src ABSOLUTE)
get_filename_component(EDITOR_ABSOLUTE_PATH Spark/Editor/src ABSOLUTE)
get_filename_component(APP_ABSOLUTE_PATH app/src ABSOLUTE)
add_custom_target(SparkHeaderTool
        COMMAND ${PYTHON_EXE} SparkHeaderTool.py "${ENGINE_ABSOLUTE_PATH}:${EDITOR_ABSOLUTE_PATH}:${APP_ABSOLUTE_PATH}"
        WORKING_DIRECTORY ../Spark/Build)

# Initial Generated file pass (so that you do not need to build once to get rid of errors)
execute_process(COMMAND ${PYTHON_EXE} SparkHeaderTool.py "${ENGINE_ABSOLUTE_PATH}:${EDITOR_ABSOLUTE_PATH}:${APP_ABSOLUTE_PATH}"
        WORKING_DIRECTORY ../Spark/Build)

add_subdirectory(Spark/Engine)
add_subdirectory(Spark/Editor)
add_subdirectory(Spark/Tools)

add_subdirectory(app)