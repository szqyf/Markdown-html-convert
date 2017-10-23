#pragma once

#include <memory>
#include <string>
#include "parser.h"
#include "render.h"

namespace ts {
std::shared_ptr<Parser> make_parser(std::string what, const std::string str);
std::shared_ptr<Parser> make_parser(std::string what, const std::istream &in);
std::shared_ptr<IRender> make_render(std::string what, std::ostream &out);
}