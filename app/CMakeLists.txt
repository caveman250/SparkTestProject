cmake_minimum_required(VERSION 3.28)
project(Spark)
set(CMAKE_CXX_STANDARD 23)

set(ROOT_DIR ../Spark)
include(${ROOT_DIR}/CMake/Spark.cmake)

###### Includes ######
include_directories(src)

###### Source Code ######
file(GLOB_RECURSE SRC src/*.cpp src/*.h)

###### Output ######
add_executable(TestProject ${SRC})

setup_spark_target(TestProject ${USE_EDITOR})

#target_compile_options(TestProject PUBLIC -fsanitize=address)
#target_link_options(TestProject PUBLIC -fsanitize=address)

#enable parallel std::for_each
if (${PLATFORM} MATCHES Linux)
    find_package(TBB REQUIRED COMPONENTS tbb)
    target_link_libraries(TestProject tbb)
endif()