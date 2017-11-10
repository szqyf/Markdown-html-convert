#pragma once
#include <rule.h>
#include <string>

namespace gfm {
namespace rule {
class simple : public ts::IRule {
   protected:
    std::string start_of_line_, end_of_line_;
    bool start_at_beginl_, stop_at_endl_;
    bool start_add_;

   protected:
    virtual bool start(const ts::Token& token) const {
        return token.str() == start_of_line_;
    }
    virtual bool end(const ts::Token& token) const {
        return token.str() == end_of_line_;
    }
    virtual void post_to_ast(ts::AstNode& node) const {}
    virtual void post_from_ast(std::string& str) const {}

   public:
    const bool matched(bool beginl, const ts::Token& token) const override {
        return (start_at_beginl_ && !beginl) || start(token);
    }

    const bool to_ast(ts::Token& in, ts::p_ast_t& parent) const override {
        ts::AstNode node{tag()};
        std::string b;

        if (start_add_) b = in.str();

        while (in.read()) {
            if ((stop_at_endl_ && in.token() == ts::token_t::endl) || end(in))
                break;

            b += in.str();
        }

        node.extends("value", b);
        post_to_ast(node);
        parent->add(node);
        return true;
    }

    const std::string from_ast(ts::p_ast_t& parent) const override {
        return "";
    }

   public:
    simple() {
        start_add_ = false;
        start_at_beginl_ = true;
        stop_at_endl_ = true;
    }
};
}  // namespace rule
}  // namespace gfm