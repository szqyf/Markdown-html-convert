#include <ast.h>
#include <catch.hpp>
#include <iostream>
#include <memory>

using namespace ts;

TEST_CASE("create ast tree", "[ast]") {
    p_ast_t root = std::make_shared<Ast>();

    auto p = root->add("p");
    auto code = p.children()->add("code");
    code.children()->add("text", "hello");
    code.children()->add("text", ",");
    code.children()->add("text", "world");
    code.extends()->emplace("lang", "c++");
    code.extends()->emplace("author", "test");
    code.extends()->emplace("modify-date", "123123");

    for (auto &c : code.children_r()) {
        std::cout << c.text() << std::endl;
    }

    REQUIRE(root->size() == 1);
    REQUIRE(code.extends()->size() == 3);
    REQUIRE(code.children()->size() == 3);
    REQUIRE(p.children()->at(0).tag() == "code");

    p.children()->remove(code);
    REQUIRE(p.children()->empty());
}