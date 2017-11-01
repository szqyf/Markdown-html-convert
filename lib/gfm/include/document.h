#pragma once

#include <parser.h>

namespace gfm {
class Document : public ts::IParser {
   public:
    const ts::p_ast_t from(std::istream &in) override;

    const ts::p_ast_t parse_line_from(std::istream &in) override;

    const ts::p_ast_t document() const override;

   private:
    ts::p_ast_t document_;

   public:
    Document();
};
}