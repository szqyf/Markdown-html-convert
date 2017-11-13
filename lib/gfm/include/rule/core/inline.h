#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class inline_ : public ts::IParserRule {
   public:
    // bool matched(bool beginl, const ts::Token &in) const = 0;
    // bool parse(ts::Token &in, const ts::AstNode &p,
    //             ts::AstNode &node) const = 0;
};
}  // namespace rule
}  // namespace gfm