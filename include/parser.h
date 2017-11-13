#pragma once

#include <istream>
#include <memory>
#include "ast.h"

namespace ts {
class IParser {
   public:
    virtual const AstNode &from(std::istream &in) = 0;

    virtual const AstNode &parse_line_from(std::istream &in) = 0;

    virtual const AstNode &document() const = 0;

   public:
    virtual ~IParser() {}
};
}