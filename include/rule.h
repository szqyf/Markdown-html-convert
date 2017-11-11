#pragma once

#include <functional>
#include <istream>
#include <string>
#include "ast.h"
#include "token.h"

namespace ts {
class IRule {
   public:
    virtual std::string tag() const = 0;

   public:
    ~IRule() = default;
};

class IParserRule : virtual public IRule {
   public:
    virtual bool need_paragrah() const = 0;
    virtual bool matched(bool beginl, const Token &in) const = 0;
    virtual bool to_ast(Token &in, ts::p_ast_t &parent) const = 0;

   public:
    virtual ~IParserRule() = default;
};

class IRenderRule : virtual public IRule {
   public:
    virtual std::string from_ast(p_ast_t &p) const = 0;

   public:
    virtual ~IRenderRule() = default;
};
}  // namespace ts