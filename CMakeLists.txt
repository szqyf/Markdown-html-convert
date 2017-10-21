cmake_minimum_required(VERSION 3.0)
set (project_name translator)
project (${project_name} CXX)

include_directories(include)
aux_source_directory(src markdown_src)

option (CMAKE_BUILD_TYPE "Debug" on)

if (WIN32)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED on)
else()
set (CXX_FLAG "-std=c++11 -g -ggdb -Wall")
set (CMAKE_CXX_FLAGS_DEBUG "${CXX_FLAG} -O0 -D_DEBUG")
set (CMAKE_CXX_FLAGS_RELEASE "${CXX_FLAG} -O3 -DNDEBUG")
endif()

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

add_executable(${project_name} main.cpp ${markdown_src})