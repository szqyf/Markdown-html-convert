#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
/**
 * @brief 行尾空格超过2个时，产生标记<br/>
 *
 */
class Br : public core {
   public:
    std::string tag() const override { return "br"; }
    paragraph_t paragraph_type() const { return paragraph_t::in_paragraph; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return in.token() == ts::token_t::blank && in.str().size() >= 2;
    }
    bool parse(ts::Token &in, ts::AstNode &parent) const override {
        bool r = true;

        if (parent.tag() == "p") {
            in.read();
            r = (in.token() == ts::token_t::endl);
            in.unread();
        }
        return r;
    }
};
}  // namespace rule
}  // namespace gfm