set(project_name gfm)
project(${project_name})

set(rules_h include/rules.h)
set(rules_c src/rules.cpp)
file(GLOB h_files RELATIVE ${PROJECT_SOURCE_DIR}/include include/rule/*.h)
file(GLOB core_files RELATIVE ${PROJECT_SOURCE_DIR}/include include/rule/core/*.h)

file(WRITE ${rules_h} "//该文件为自动生成，请勿自行修改\n")
file(APPEND ${rules_h} "#pragma once\n")
file(APPEND ${rules_h} "#include <rule.h>\n")
file(APPEND ${rules_h} "#include <vector>\n")
file(APPEND ${rules_h} "#include <memory>\n")
foreach (name ${core_files})
    file(APPEND ${rules_h} "#include <${name}>\n")
endforeach ()

file(APPEND ${rules_h} "\nnamespace ${project_name} { extern std::vector<std::shared_ptr<rule::core>> rules; }")
# file(APPEND ${rules_h} "\nnamespace ${project_name} {\nclass Rules {\n\tpublic:\n\t\tvoid for_each(ts::iterator_t iterator);\n}; }")


file(WRITE ${rules_c} "//该文件为自动生成，请勿自行修改\n")
file(APPEND ${rules_c} "#include <rules.h>\n")

foreach (name ${h_files})
    file(APPEND ${rules_c} "#include <${name}>\n")
endforeach () 

file(APPEND ${rules_c} "\nnamespace ${project_name} { \n\tstd::vector<std::shared_ptr<rule::core>> rules {")


foreach (name ${h_files})
    get_filename_component(name ${name} NAME_WE)
    file(APPEND ${rules_c} "\n\t\tstd::make_shared<rule::${name}>(),")
endforeach ()

file(APPEND ${rules_c} "\n\t};\n}")

aux_source_directory(src gfm_src)

add_library(${project_name} STATIC ${gfm_src})
target_include_directories(${project_name} PRIVATE ../../include)
target_include_directories(${project_name} PRIVATE include)