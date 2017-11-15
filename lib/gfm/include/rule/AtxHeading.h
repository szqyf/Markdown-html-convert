#pragma once
#include <rule.h>
#include "core/core.h"

namespace gfm {
namespace rule {
class AtxHeading : public core {
   public:
    std::string tag() const override { return "h"; }
    paragraph_t paragraph_type() const { return paragraph_t::out_paragraph; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return beginl && in.token() == ts::token_t::punctation &&
               in.str().front() == '#' && in.str().size() <= 6;
    }
    ts::result_t parse(ts::Token &in, ts::AstNode &parent) const override;
};
}  // namespace rule
}  // namespace gfm