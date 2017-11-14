#pragma once

#include <rule.h>
#include <algorithm>

namespace gfm {
namespace rule {
class linktext : public core {
   public:
    std::string tag() const { return "a"; }
    paragraph_t paragraph_type() const { return paragraph_t::in_paragraph; }
    bool matched(bool beginl, const ts::Token &in) const override {
        auto str = in.str();
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str == "http" || str == "https" || str == "ftp" ||
               str == "mailto";
    }
    bool parse(ts::Token &in, ts::AstNode &parent) const override {
        std::string text;
        do {
            text += in.str();
        } while (in.read() && !in.all_space());

        parent.children(tag(), {{"href", text}}).children("text", text);

        in.unread();

        return true;
    }
};
}  // namespace rule
}  // namespace gfm