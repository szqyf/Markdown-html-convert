#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class Img : public ts::IParserRule {
   public:
    std::string tag() const override { return "img"; }

    bool need_paragrah() const override { return true; }

    bool matched(bool beginl, const ts::Token &in) const override {
        return in.str() == "!";
    }

    bool parse(ts::Token &in, const ts::AstNode &p, ts::AstNode &node) const override {
        return true;
    }
};
}  // namespace rule
}  // namespace gfm