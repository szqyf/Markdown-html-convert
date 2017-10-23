#pragma once

#include <parser.h>

namespace gfm {
class Document : public ts::Parser {
   public:
    virtual ts::AstNode parse() { return root_; }

    virtual ts::AstNode parse_line() { return nullptr; }

   public:
    Document(const std::istream &in) : ts::Parser(in) {}
};
}