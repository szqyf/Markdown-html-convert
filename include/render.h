#pragma once

#include <memory>
#include <string>
#include "ast.h"

namespace ts {
class IRender {
   public:
    virtual std::string render(const AstNode &root) = 0;

   public:
    virtual ~IRender() {}
};
}