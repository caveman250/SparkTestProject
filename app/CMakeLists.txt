cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)

set(ROOT_DIR ../Spark)
include(include/Spark)

###### Includes ######
include_directories(src)

setup_spark_target(TestProject false ${CMAKE_CURRENT_SOURCE_DIR}/unity.conf)

#target_compile_options(TestProject PUBLIC -fsanitize=address)
#target_link_options(TestProject PUBLIC -fsanitize=address)