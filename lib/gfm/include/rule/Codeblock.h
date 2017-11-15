#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class Codeblock : public core {
   public:
    std::string tag() const override { return "code"; }
    paragraph_t paragraph_type() const { return paragraph_t::out_paragraph; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return beginl && in.token() == ts::token_t::punctation &&
               in.str().front() == '`' && in.str().size() >= 3;
    }
    ts::result_t parse(ts::Token &in, ts::AstNode &parent) const override;
};
}  // namespace rule
}  // namespace gfm