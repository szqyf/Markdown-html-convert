#pragma once
#include <rule.h>
#include <utils.h>

namespace gfm {
namespace rule {
class Img : public ts::IParserRule {
   public:
    std::string tag() const override { return "img"; }

    bool need_paragrah() const override { return true; }

    bool matched(bool beginl, const ts::Token &in) const override {
        return in.str() == "!";
    }

    bool parse(ts::Token &in, const ts::AstNode &p,
               ts::AstNode &node) const override {
        in.read();

        std::string alt, href, title;
        bool is_ref;

        if (!parse_link(in, alt, href, title, is_ref)) return false;

        node.extends("alt", alt);
        node.extends("src", href);
        node.extends("title", title);
        node.extends("is_ref", is_ref ? "true" : "false");

        return true;
    }
};
}  // namespace rule
}  // namespace gfm