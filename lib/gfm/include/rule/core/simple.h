#pragma once
#include <rule.h>
#include <string>

namespace gfm {
namespace rule {
class simple : public ts::IRule {
   protected:
    std::string start_of_line_, end_of_line_;
    bool start_at_beginl_, stop_at_endl_;
    virtual bool start(std::string str) const { return str == start_of_line_; }
    virtual bool end(std::string str) const { return str == end_of_line_; }

   public:
    const bool matched(bool beginl, std::string buf) const override {
        return (start_at_beginl_ && !beginl) || start(buf);
    }

    const bool to_ast(ts::Token &in, ts::p_ast_t &parent) const override {
        while (in.read()) {
            
        }

        return true;
    }

    const std::string from_ast(ts::p_ast_t &parent) const override { return ""; }
};
}
}