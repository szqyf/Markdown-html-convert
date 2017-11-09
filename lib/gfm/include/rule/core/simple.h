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
    virtual bool start(std::string str) const { return str == start_of_line_; }
    virtual bool end(std::string str) const { return str == end_of_line_; }

   public:
    const bool matched(bool beginl, std::string buf) const override {
        return (start_at_beginl_ && !beginl) || start(buf);
    }

    const bool to_ast(ts::Token &in, ts::p_ast_t &parent) const override {
        ts::AstNode node{tag()};
        std::string b;

        if (start_add_) b = in.str();

        while (in.read()) {
            if ((stop_at_endl_ && in.token() == ts::token_t::endl) ||
                end(in.str()))
                break;

            b += in.str();
        }

        node.extends("value", b);
        parent->add(node);
        return true;
    }

    const std::string from_ast(ts::p_ast_t &parent) const override {
        return "";
    }

   public:
    simple() {
        start_add_ = false;
        start_at_beginl_ = true;
        stop_at_endl_ = true;
    }
};
}
}