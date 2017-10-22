#pragma once

#include <memory>
#include <string>
#include "token.h"

namespace ts {
class Render {
   public:
    std::string render(const std::unique_ptr<Token> &root);
};
}