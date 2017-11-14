#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class Paragraph : public core {
   public:
    std::string tag() const override { return "p"; }
    paragraph_t paragraph_type() const { return paragraph_t::out_paragraph; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return beginl;
    }
    bool parse(ts::Token &in, ts::AstNode &parent) const override;
};
}  // namespace rule
}  // namespace gfm