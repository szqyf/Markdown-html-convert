#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class Link : public core {
   public:
    std::string tag() const override { return "a"; }
    paragraph_t paragraph_type() const { return paragraph_t::in_paragraph; }

    bool matched(bool beginl, const ts::Token &in) const override {
        return in.has_puncation("[");
    }

    ts::result_t parse(ts::Token &in, ts::AstNode &parent) const override;
};
}  // namespace rule
}  // namespace gfm