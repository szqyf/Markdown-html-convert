#pragma once
#include <ast.h>
#include <token.h>
#include <istream>
#include <string>

namespace gfm {
bool parse_until(bool beginl, ts::Token &in, ts::AstNode &parent);
bool parse_link(ts::Token &in, std::string &alt, std::string &href,
                std::string &title, bool &is_ref);
}  // namespace gfm