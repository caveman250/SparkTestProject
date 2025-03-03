cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)

set(ROOT_DIR ../Spark)
include(${ROOT_DIR}/CMake/include/Spark.cmake)

###### Includes ######
include_directories(src)

setup_spark_target(TestProject false ${USE_EDITOR} ../../app/unity.conf)

#target_compile_options(TestProject PUBLIC -fsanitize=address)
#target_link_options(TestProject PUBLIC -fsanitize=address)