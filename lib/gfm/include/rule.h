#pragma once

#include <ast.h>
#include <functional>
#include <istream>
#include <string>

namespace gfm {
using condition_t = std::function<bool(std::string)>;

class IRule {
   public:
    virtual const std::string tag() const = 0;
    virtual const bool matched(bool fol, std::string buf) const = 0;
    virtual void read(std::string buf, std::istream &in,
                      ts::p_ast_t &parent) = 0;

   public:
    virtual ~IRule() = default;
};

class Simple : public IRule {
   protected:
    condition_t start_, end_;
    bool must_fol_;

   public:
    const bool matched(bool fol, std::string buf) const override {
        if (!fol && must_fol_) return false;
        return start_(buf);
    }
};
}