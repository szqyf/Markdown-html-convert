cmake_minimum_required(VERSION 3.0)
project (markdown CXX)

include_directories(include)
aux_source_directory(src markdown_src)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(markdown main.cpp ${markdown_src})