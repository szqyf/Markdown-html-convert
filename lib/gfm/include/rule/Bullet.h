#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class Bullet : public core {
   public:
    std::string tag() const override { return "bullet"; }
    paragraph_t paragraph_type() const { return paragraph_t::out_paragraph; }
    bool matched(bool beginl, const ts::Token &in) const override {
        bool isdigit = false;
        if (in.token() == ts::token_t::word) {
            for (auto &c : in.str()) {
                if (c < '0' || c > '9') break;
                isdigit = true;
            }
        }

        return beginl && (in.has_puncation("-") || in.has_puncation("*") ||
                          in.has_puncation("+") || isdigit);
    }
    ts::result_t parse(ts::Token &in, ts::AstNode &parent) const override {
        return ts::result_t::ok;
    }
};
}  // namespace rule
}  // namespace gfm