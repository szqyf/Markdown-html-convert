#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>
#include "noncopyable.h"
#include "ast.h"

namespace ts {
class Parser : private noncopyable {
   public:
    virtual AstNode parse() = 0;

    virtual AstNode parse_line() = 0;

   public:
    const AstNode document() const { return root_; }

   protected:
    AstNode root_;
    const std::istream &in_;

    // virtual AstNode parse_word(std::string text) = 0;

   public:
    Parser(const std::istream &in) : root_(Ast::make_root()), in_(in) {}
    virtual ~Parser() {}
};
}