#pragma once

#include <memory>
#include <string>
#include "token.h"

namespace md {
class Render {
   public:
    std::string render(std::shared_ptr<Token> root);
};
}