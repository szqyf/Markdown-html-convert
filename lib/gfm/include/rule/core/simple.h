#pragma once
#include <rule.h>
#include <string>

namespace gfm {
namespace rule {
class simple : virtual public ts::IParserRule {
   protected:
    std::string start_of_, end_of_;
    bool start_at_beginl_, stop_at_endl_;
    bool add_start_;

   protected:
    virtual bool start(const ts::Token& token) const {
        return token.str() == start_of_;
    }
    virtual bool end(const ts::Token& token) const {
        return token.str() == end_of_;
    }
    virtual bool post_to_ast(ts::AstNode& node) const { return true; }
    virtual void post_from_ast(std::string& str) const {}

   public:
    bool matched(bool beginl, const ts::Token& token) const override {
        return (!start_at_beginl_ || beginl) && start(token);
    }

    bool need_paragrah() const { return true; }

    bool parse(ts::Token& in, const ts::AstNode& p,
               ts::AstNode& node) const override {
        std::string b;

        if (add_start_) b = in.str();

        while (in.read()) {
            if ((stop_at_endl_ && in.token() == ts::token_t::endl) || end(in))
                break;

            b += in.str();
        }

        node.extends("value", b);

        if (!post_to_ast(node)) return false;

        return true;
    }

   public:
    simple() {
        add_start_ = false;
        start_at_beginl_ = true;
        stop_at_endl_ = true;
    }
};
}  // namespace rule
}  // namespace gfm