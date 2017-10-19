#pragma once

#include "token.h"
#include <list>
#include <string>

namespace md {
class Render {
public:
    std::string render(std::list<Token> tokens);
}
}