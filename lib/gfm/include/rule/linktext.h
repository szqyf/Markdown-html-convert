#pragma once

#include <rule.h>
#include <algorithm>

namespace gfm {
namespace rule {
class linktext : public simple {
   protected:
    bool start(const ts::Token& token) const override {
        auto str = token.str();
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str == "http" || str == "https" || str == "ftp" ||
               str == "mailto";
    }
    bool end(const ts::Token& token) const override {
        return token.token() == ts::token_t::blank;
    }
    void post_to_ast(ts::AstNode& node) const override {
        node.extends("url", node.extends("value"));
    }

   public:
    const std::string tag() const override { return "a"; }

   public:
    linktext() {
        start_at_beginl_ = false;
        stop_at_endl_ = true;
        add_start_ = true;
    }
};
}  // namespace rule
}  // namespace gfm