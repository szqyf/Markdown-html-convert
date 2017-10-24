#pragma once

#include <istream>
#include <memory>
#include "ast.h"
#include "noncopyable.h"

namespace ts {
class IParser : private noncopyable {
   public:
    virtual AstNode from(std::istream &in) = 0;

    virtual AstNode parse_line_from(std::istream &in) = 0;

    virtual const AstNode document() const = 0;

   public:
    virtual ~IParser() {}
};
}