set(project_name gfm)
project(${project_name})

aux_source_directory(src gfm_src)

add_library(${project_name} STATIC ${gfm_src})
target_include_directories(${project_name} PRIVATE ../../include)
target_include_directories(${project_name} PRIVATE include)