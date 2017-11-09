#pragma once

#include <rule.h>
#include <algorithm>

namespace gfm {
namespace rule {
class linktext : public simple {
   protected:
    bool start(std::string str) const override {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);

        return str == "http" || str == "https" || str == "ftp" ||
               str == "mailto";
    }
    bool end(std::string str) const override {
        return str.front() == ' ' || str.front() == '\t';
    }

   public:
    const std::string tag() const override { return "a"; }
    const bool to_ast(ts::Token &in, ts::p_ast_t &p) const override {
        simple::to_ast(in, p);
        auto str = p->back().extends("value");
        p->back().extends("url", str);

        return true;
    }

   public:
    linktext() {
        start_at_beginl_ = false;
        stop_at_endl_ = true;
        start_add_ = true;
    }
};
}
}