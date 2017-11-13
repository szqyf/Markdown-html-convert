#pragma once
#include <ast.h>
#include <token.h>
#include <string>

namespace gfm {
std::string get_text_with_escaped(ts::Token &in);
}  // namespace gfm