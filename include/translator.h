#pragma once

#include <memory>
#include <string>
#include "parser.h"
#include "render.h"

namespace ts {
std::shared_ptr<Parser> make_parser(std::string what);
std::shared_ptr<IRender> make_render(std::string what);
}