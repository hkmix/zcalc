cmake_minimum_required(VERSION 3.6)

project(zcalc)

set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

include_directories(include)
add_subdirectory(src)
