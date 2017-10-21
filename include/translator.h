#pragma once

#include <memory>
#include <string>
#include "parser.h"
#include "render.h"
#include "syntax.h"
#include "syntax/complex.h"
#include "token.h"

namespace ts {
std::shared_ptr<Parser> make_parser(std::string what);
std::shared_ptr<Render> make_render(std::string what);
std::shared_ptr<Token> make_root_token();
}