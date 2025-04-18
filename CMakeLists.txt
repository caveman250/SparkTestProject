cmake_minimum_required(VERSION 3.28)

if (UNIX AND APPLE)
    project(Spark LANGUAGES C CXX OBJC OBJCXX)
else ()
    project(Spark LANGUAGES C CXX)
endif()

option(USE_EDITOR "" OFF)

add_compile_definitions(APP_DIR="../../app")
add_compile_definitions(ENGINE_DIR="../../Spark/Engine")

add_subdirectory(Spark/Engine)
add_subdirectory(Spark/Editor)
add_subdirectory(Spark/Tools)

add_subdirectory(app)