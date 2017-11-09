#include <ast.h>
#include <rules.h>
#include <catch.hpp>
#include <sstream>
#include <iostream>

using namespace ts;
using namespace gfm;

TEST_CASE("AtxHeading", "[rules]") { REQUIRE(rules[0]->tag() == "h"); }

TEST_CASE("linktext rule", "[rules]") {
    gfm::rule::linktext text;
    std::stringstream s{"http://www.sz.js.cn list"};
    Token tk{s};
    p_ast_t root = Ast::make();

    tk.read();
    REQUIRE(text.matched(false, tk.str()));
    REQUIRE(text.to_ast(tk, root));

    REQUIRE(tk.token() == token_t::blank);
    REQUIRE(tk.str() == " ");

    REQUIRE(root->size() == 1);
    REQUIRE(root->at(0).tag() == "a");
    REQUIRE(root->at(0).extends("value") == "http://www.sz.js.cn");
}