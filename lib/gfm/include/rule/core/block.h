#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class block : public ts::IParserRule {
   public:
    bool matched(bool beginl, const ts::Token &in) const = 0;
    bool to_ast(ts::Token &in, ts::p_ast_t &parent) const = 0;
};
}  // namespace rule
}  // namespace gfm