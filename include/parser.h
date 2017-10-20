#pragma once

#include "syntax.h"
#include "token.h"
#include <istream>
#include <memory>
#include <string>
#include <vector>

namespace md {
class Parser {
  public:
    std::vector<std::shared_ptr<Token>> read(std::string text);
    std::vector<std::shared_ptr<Token>> read(const std::istream &stream);
};
}