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