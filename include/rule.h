#pragma once

#include <istream>
#include <string>
#include "ast.h"
#include "token.h"

namespace ts {
enum class result_t { ok, failure, jumpout, skip };
class IRule {
   public:
    virtual std::string tag() const = 0;

   public:
    ~IRule() = default;
};

class IParserRule : virtual public IRule {
   public:
    virtual bool matched(bool beginl, const Token &in) const = 0;
    virtual result_t parse(Token &in, ts::AstNode &parent) const = 0;

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