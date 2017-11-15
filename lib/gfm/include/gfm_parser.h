#pragma once

#include <parser.h>

namespace gfm {
class Parser : public ts::IParser {
   public:
    const ts::AstNode &from(std::istream &in) override;

    const ts::AstNode &parse_line_from(std::istream &in) override;

    const ts::AstNode &document() const override;

   private:
    ts::AstNode document_;

   public:
    Parser();
};
}  // namespace gfm