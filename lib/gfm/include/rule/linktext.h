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

   public:
    linktext() { start_at_beginl_ = false; }
};
}
}