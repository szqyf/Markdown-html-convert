#include <parser.h>
#include <catch.hpp>
#include <iostream>
#include <memory>

using namespace ts;

class TestAstHelper : public IParser {
   public:
    const AstNode &from(std::istream &in) override { return helper_.current(); }

    const AstNode parse_line_from(std::istream &in) override { return helper_.current(); }

    const AstNode document() const override { return helper_.current(); }

   private:
    IParser::AstHelper helper_;

   public:
    TestAstHelper() {
        helper_.push_leaf("P");

        auto ast = helper_.current()->children();

        REQUIRE ( ast[0]->tag() == "P" );
    }
};

TEST_CASE("create AstHelper", "[AstHelper]") {
    TestAstHelper helper;
    helper.from(std::cin);
}