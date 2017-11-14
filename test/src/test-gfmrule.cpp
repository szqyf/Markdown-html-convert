#include <ast.h>
#include <rule/core/simple.h>
#include <rule/linktext.h>
#include <rule/text.h>
#include <rules.h>
#include <catch.hpp>
#include <iostream>
#include <sstream>

using namespace ts;
using namespace gfm;

TEST_CASE("linktext rule", "[rules]") {
    gfm::rule::linktext text;
    std::stringstream s{"http://www.sz.js.cn list"};
    Token tk{s};
    AstNode root;

    tk.read();
    REQUIRE(text.matched(false, tk));
    REQUIRE(text.parse(tk, root));

    // REQUIRE(tk.token() == token_t::blank);
    // REQUIRE(tk.str() == " ");
    REQUIRE(root.children()->size() == 1);
    REQUIRE(root.children(0).tag() == "a");
    REQUIRE(root.children(0).extends("href") == "http://www.sz.js.cn");
    REQUIRE(root.children(0).children(0).extends("text") ==
            "http://www.sz.js.cn");
}