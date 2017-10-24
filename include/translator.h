#pragma once

#include <iostream>
#include <memory>
#include <string>
#include "ast.h"
#include "parser.h"
#include "render.h"

namespace ts {
std::shared_ptr<IParser> make_parser(std::string what);
std::shared_ptr<IRender> make_render(std::string what);
void set_default_render(std::shared_ptr<IRender> render);

std::ostream& operator<<(std::ostream& out, AstNode node);
std::istream& operator>>(std::istream& in, std::shared_ptr<IParser> parser);
std::ostream& operator<<(std::ostream& out, std::shared_ptr<IParser> parser);
}