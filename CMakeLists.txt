cmake_minimum_required(VERSION 3.0)
set (project_name translator)
project (${project_name} CXX)

enable_testing(true)

aux_source_directory(src markdown_src)

option (CMAKE_BUILD_TYPE "Debug" on)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED on)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/lib)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(${project_name} ${markdown_src})
target_include_directories(${project_name} PRIVATE include)
target_link_libraries(${project_name} gfm)
