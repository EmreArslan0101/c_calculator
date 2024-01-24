cmake_minimum_required(VERSION 3.5)
project(c_calc C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")

include_directories(${include_dir})

file(GLOB source_files "${source_dir}/Main.c")

# Add the executable
add_executable(c_calc "${source_files}")

