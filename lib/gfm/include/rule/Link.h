#pragma once
#include <rule.h>
#include <utils.h>

namespace gfm {
namespace rule {
class Link : public ts::IParserRule {
   public:
    std::string tag() const override { return "a"; }

    bool need_paragrah() const override { return true; }

    bool matched(bool beginl, const ts::Token &in) const override {
        return in.has_puncation("[");
    }

    bool parse(ts::Token &in, const ts::AstNode &p,
               ts::AstNode &node) const override {
        std::string alt, href, title;
        bool is_ref;

        if (!parse_link(in, alt, href, title, is_ref)) return false;

        node.extends("href", href);
        node.extends("title", title);
        node.children()->add("text", alt);
        node.extends("is_ref", is_ref ? "true" : "false");

        return true;
    }
};
}  // namespace rule
}  // namespace gfm