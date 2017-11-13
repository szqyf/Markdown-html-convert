#pragma once

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
    virtual bool matched(bool beginl, const Token &in) const = 0;
    virtual bool parse(Token &in, const ts::AstNode &parent,
                       ts::AstNode &node) const = 0;

   public:
    virtual ~IParserRule() = default;
};

class IRenderRule : virtual public IRule {
   public:
    virtual std::string render(const AstNode &p) const = 0;

   public:
    virtual ~IRenderRule() = default;
};
}  // namespace ts