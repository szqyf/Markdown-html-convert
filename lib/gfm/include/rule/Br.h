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
    ts::result_t parse(ts::Token &in, ts::AstNode &parent) const override {
        auto r = ts::result_t::failure;

        if (parent.tag() == "p") {
            in.read();
            if (in.token() == ts::token_t::endl)
                r = ts::result_t::ok;
            in.unread();
        }
        if (r == ts::result_t::ok) parent.children("br", "");
        return r;
    }
};
}  // namespace rule
}  // namespace gfm