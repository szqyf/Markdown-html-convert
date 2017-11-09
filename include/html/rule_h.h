#pragma once

#include <istream>
#include <string>
#include "../ast.h"
#include "../token.h"

namespace ts {
class IRule_h {
   public:
    virtual const std::string from_ast(ts::p_ast_t p) const = 0;

   public:
    virtual ~IRule_h() = default;
};
}