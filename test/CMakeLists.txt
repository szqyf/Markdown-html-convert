set (project_name test-trans)
project (${project_name} CXX)

aux_source_directory(src test_src)
find_library(gfm NAMES gfm PATHS ../bin/Debug/lib)

add_executable(${project_name} test-main.cpp ../src/ast.cpp ${test_src})
target_include_directories(${project_name} PRIVATE framework/single_include)
target_include_directories(${project_name} PRIVATE ../include)
target_link_libraries(${project_name} ${gfm})

add_test(NAME ast COMMAND ${project_name} "[ast]")