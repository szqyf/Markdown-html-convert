#pragma once

#include <istream>
#include <memory>
#include "ast.h"

namespace ts {
class IParser {
   public:
    virtual const p_ast_t from(std::istream &in) = 0;

    virtual const p_ast_t parse_line_from(std::istream &in) = 0;

    virtual const p_ast_t document() const = 0;

   public:
    virtual ~IParser() {}
};
}