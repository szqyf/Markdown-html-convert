#pragma once

#include <parser.h>

namespace gfm {
class Document : public ts::IParser {
   public:
    ts::AstNode from(std::istream &in) override;

    ts::AstNode parse_line_from(std::istream &in) override;

    const ts::AstNode document() const override;

   private:
    AstNode document_;

   public:
    Document(ts::AstNode node = nullptr);
};
}