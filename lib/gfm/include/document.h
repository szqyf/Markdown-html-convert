#pragma once

#include <parser.h>

namespace gfm {
class Document : public ts::Parser {
   public:
    virtual ts::TagPtr parse(std::string text) { return nullptr; }
    virtual ts::TagPtr parse(const std::istream &stream) { return nullptr; }

    virtual ts::TagPtr parse_line(std::string text) { return nullptr; }
    virtual ts::TagPtr parse_line(const std::istream &stream) {
        return nullptr;
    }

   public:
    Document() {}
};
}