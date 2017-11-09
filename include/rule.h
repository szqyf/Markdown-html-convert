#pragma once

#include <istream>
#include <string>
#include "ast.h"
#include "token.h"

namespace ts {
class IRule {
   public:
    virtual const std::string tag() const = 0;
    virtual const bool matched(bool beginl, std::string buf) const = 0;
    virtual const bool to_ast(Token &in, ts::p_ast_t &parent) const = 0;
    virtual const std::string from_ast(ts::p_ast_t &p) const = 0;

   public:
    virtual ~IRule() = default;
};
}