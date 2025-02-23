cmake_minimum_required(VERSION 3.28)
project(Spark)
set(CMAKE_CXX_STANDARD 23)

set(ROOT_DIR ../Spark)
include(${ROOT_DIR}/CMake/Spark.cmake)
include(${ROOT_DIR}/CMake/ExternalTools.cmake)

###### Includes ######
include_directories(src)

###### Generate Unity Files #######
execute_process(COMMAND ${PYTHON_EXE} UnityBatcher.py ../../app/unity.conf ${PLATFORM}
        WORKING_DIRECTORY ${ROOT_DIR}/Build/)

###### Source ######
file(GLOB SOURCE ./unity_generated/*.cpp)

###### Output ######
add_executable(TestProject ${SOURCE})

setup_spark_target(TestProject ${USE_EDITOR})

#target_compile_options(TestProject PUBLIC -fsanitize=address)
#target_link_options(TestProject PUBLIC -fsanitize=address)

#enable parallel std::for_each
if (${PLATFORM} MATCHES Linux)
    find_package(TBB REQUIRED COMPONENTS tbb)
    target_link_libraries(TestProject tbb)
endif()

###### Add non Unity files for visualisation in VS and Xcode ######
file(GLOB_RECURSE NON_UNITY_SOURCE src/*.cpp src/*.h)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${NON_UNITY_SOURCE})
add_custom_target("App_Source_Files" SOURCES ${NON_UNITY_SOURCE})