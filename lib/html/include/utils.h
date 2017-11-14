#pragma once
#include <ast.h>
#include <token.h>
#include <istream>
#include <string>

namespace html {
bool parse_link(ts::Token &in, std::string &alt, std::string &href,
                std::string &title, bool &is_ref);
}  // namespace gfm