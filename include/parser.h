#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>
#include "noncopyable.h"
#include "tag.h"

namespace ts {
class Parser : private noncopyable {
   public:
    virtual TagPtr parse(std::string text) = 0;
    virtual TagPtr parse(const std::istream &stream) = 0;

    virtual TagPtr parse_line(std::string text) = 0;
    virtual TagPtr parse_line(const std::istream &stream) = 0;

   public:
    const TagPtr document() const { return root_; }

   protected:
    TagPtr root_;

    // virtual TagPtr parse_word(std::string text) = 0;

   public:
    Parser() : root_(Tag::make_root()) {}
    virtual ~Parser() {}
};
}