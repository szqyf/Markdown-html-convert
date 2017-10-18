cmake_minimum_required(VERSION 3.0)
set (project_name md2html)
project (${project_name} CXX)

include_directories(include)
aux_source_directory(src markdown_src)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(${project_name} main.cpp ${markdown_src})