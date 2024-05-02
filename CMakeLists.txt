cmake_minimum_required(VERSION 3.28)
project(Spark)

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE) #make third party libs using old cmake versions shut up.

option(USE_EDITOR "" OFF)

add_compile_definitions(APP_DIR="../../app")
add_compile_definitions(ENGINE_DIR="../../Spark/Engine")

add_subdirectory(Spark/Engine)
add_subdirectory(Spark/Editor)
add_subdirectory(Spark/Tools)

add_subdirectory(app)