#pragma once

#include <memory>
#include <string>
#include "token.h"

namespace ts {
class Render {
   public:
    std::string render(std::shared_ptr<Token> root);
};
}