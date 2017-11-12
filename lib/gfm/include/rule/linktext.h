#pragma once

#include <rule.h>
#include <algorithm>

namespace gfm {
namespace rule {
class linktext : public ts::IParserRule {
   public:
    std::string tag() const { return "a"; }
    bool need_paragrah() const override { return true; }
    bool matched(bool beginl, const ts::Token &in) const override {
        auto str = in.str();
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str == "http" || str == "https" || str == "ftp" ||
               str == "mailto";
    }
    bool parse(ts::Token &in, const ts::AstNode &parent,
               ts::AstNode &node) const override {
        auto text = in.str();

        while (in.read()) {
            auto token = in.token();

            if (token == ts::token_t::endl || token == ts::token_t::blank)
                break;

            text += in.str();
        }

        node.children()->add("text", text);
        node.extends("href", text);

        return true;
    }
};
}  // namespace rule
}  // namespace gfm