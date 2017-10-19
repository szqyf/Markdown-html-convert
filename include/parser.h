#pragma once

#include "token.h"
#include <list>
#include <string>

namespace md {
class Parser {
public:
    std::list<Token> read(std::string text);
};
}