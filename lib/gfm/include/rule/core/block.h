#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class block : public ts::IParserRule {
   public:
    // bool matched(bool beginl, const ts::Token &in) const = 0;
    // bool parse(parse(ts::Token &in, const ts::AstNode &p,
    //                  ts::AstNode &node)) const = 0;
};
}  // namespace rule
}  // namespace gfm