#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
/**
 * @brief 行尾空格超过2个时，产生标记<br/>
 *
 */
class Br : public ts::IParserRule {
   public:
    std::string tag() const override { return "br"; }
    bool need_paragrah() const override { return false; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return in.token() == ts::token_t::blank && in.str().size() >= 2;
    }
    bool parse(ts::Token &in, const ts::AstNode &parent,
               ts::AstNode &node) const override {
        in.read();
        bool r = (in.token() == ts::token_t::endl);
        return r;
    }
};
}  // namespace rule
}  // namespace gfm