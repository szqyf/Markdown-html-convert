set(project_name html)
project(${project_name})

set(rules_h include/rules.h)
set(rules_c src/rules.cpp)
file(GLOB h_files RELATIVE ${PROJECT_SOURCE_DIR}/include include/rule/*.h)
file(GLOB core_files RELATIVE ${PROJECT_SOURCE_DIR}/include include/rule/core/*.h)

file(WRITE ${rules_h} "#pragma once\n")
file(WRITE ${rules_h} "//该文件为自动生成，请勿自行修改\n")
file(APPEND ${rules_h} "#include <rule.h>\n")
file(APPEND ${rules_h} "#include <vector>\n")
file(APPEND ${rules_h} "#include <memory>\n")

file(APPEND ${rules_h} "\nnamespace ${project_name} { extern std::vector<std::shared_ptr<ts::IRule>> rules; }")

file(WRITE ${rules_c} "//该文件为自动生成，请勿自行修改\n")
file(WRITE ${rules_c} "#include <rules.h>\n")

foreach (name ${core_files})
    file(APPEND ${rules_c} "#include <${name}>\n")
endforeach ()

foreach (name ${h_files})
    file(APPEND ${rules_c} "#include <${name}>\n")
endforeach ()

file(APPEND ${rules_c} "\nnamespace ${project_name} { \n\tstd::vector<std::shared_ptr<ts::IRule>> rules {")


foreach (name ${h_files})
    get_filename_component(name ${name} NAME_WE)
    file(APPEND ${rules_c} "\n\t\tstd::make_shared<rule::${name}>(),")
endforeach ()

file(APPEND ${rules_c} "\n\t};\n}")

aux_source_directory(src html_src)

add_library(${project_name} STATIC ${html_src})
target_include_directories(${project_name} PRIVATE ../../include)
target_include_directories(${project_name} PRIVATE include)