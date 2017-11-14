#pragma once
#include <ast.h>
#include <token.h>
#include <istream>
#include <string>
#include <functional>

namespace gfm {
bool parse(bool beginl, ts::Token &in, ts::AstNode &parent, bool except_p = false);
bool parse_link(ts::Token &in, std::string &alt, std::string &href,
                std::string &title, bool &is_ref);
}  // namespace gfm