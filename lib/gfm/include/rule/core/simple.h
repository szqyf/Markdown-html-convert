#pragma once
#include <rule.h>
#include <functional>
#include <string>

namespace gfm {
namespace rule {
using condition_t = std::function<bool(std::string)>;

class simple : public ts::IRule {
   protected:
    condition_t start_, end_;
    std::string start_of_line_, end_of_line_;
    bool start_at_beginl_, stop_at_endl_;

   public:
    const bool matched(bool beginl, std::string buf) const override {
        if (start_at_beginl_ && !beginl) return false;

        bool r = false;

        if (start_ == nullptr && !start_of_line_.empty())
            r = (buf == start_of_line_);
        else if (start_ != nullptr)
            r = start_(buf);

        return r;
    }

    const bool to_ast(ts::Token &in, ts::p_ast_t &parent) const override {
        return true;
    }
};
}
}