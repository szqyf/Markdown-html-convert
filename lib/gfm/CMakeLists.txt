set(project_name gfm)
project(${project_name})

set(rules_h include/rules.h)
set(rules_c src/rules.cpp)
file(GLOB_RECURSE h_files include/rules/*.h)

file(WRITE ${rules_h} "#pragma once\n")
file(APPEND ${rules_h} "#include <rule.h>\n")
file(APPEND ${rules_h} "#include <vector>\n")
file(APPEND ${rules_h} "#include <memory>\n")

foreach (name ${h_files})
    file(RELATIVE_PATH rname ${PROJECT_SOURCE_DIR}/include ${name})
    file(APPEND ${rules_h} "#include \"${rname}\"\n")
endforeach ()

file(APPEND ${rules_h} "\nnamespace gfm { extern std::vector<std::shared_ptr<IRule>> rules; }")

file(WRITE ${rules_c} "#include <rules.h>\n")
file(APPEND ${rules_c} "\nnamespace gfm { \n\tstd::vector<std::shared_ptr<IRule>> rules {")

foreach (name ${h_files})
    file(RELATIVE_PATH rname ${PROJECT_SOURCE_DIR}/include ${name})
    get_filename_component(rname ${rname} NAME_WE)
    file(APPEND ${rules_c} "std::make_shared<${rname}>(),\n")
endforeach ()

file(APPEND ${rules_c} "\t};\n}")

aux_source_directory(src gfm_src)

add_library(${project_name} STATIC ${gfm_src})
target_include_directories(${project_name} PRIVATE ../../include)
target_include_directories(${project_name} PRIVATE include)