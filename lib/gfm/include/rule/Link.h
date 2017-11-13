#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class Link : public core {
   public:
    std::string tag() const override { return "a"; }

    paragraph_t paragraph_type() const override { return paragraph_t::paragraph; }

    bool matched(bool beginl, const ts::Token &in) const override {
        return in.has_puncation("[");
    }

    bool parse(ts::Token &in, const ts::AstNode &p,
               ts::AstNode &node) const override;
};
}  // namespace rule
}  // namespace gfm