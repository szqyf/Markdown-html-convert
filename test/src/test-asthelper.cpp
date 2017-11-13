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

    for (auto &c : code) {
        std::cout << c.extends("text") << std::endl;
    }

    REQUIRE(root->size() == 1);
    REQUIRE(code.extends()->size() == 3);
    REQUIRE(code.children()->size() == 3);
    REQUIRE(p.children(0).tag() == "code");

    code.children()->remove(2)->remove(1)->remove(4);
    REQUIRE(code.children()->size() == 1);

    auto cf = code.children()->begin();
    code.children()->remove(*cf);
    REQUIRE(code.children()->empty());
}

TEST_CASE("compare extend", "[ast]") {
    p_ast_t root = std::make_shared<Ast>();

    auto p = root->add("p");
    auto code =
        p.children()->add("code", {{"lang", "c++"}, {"author", "betaest"}});
    code.children()->add({{"text", "hello"}, {"text", ","}, {"text", "world"}});

    REQUIRE(code.extends()->size() == 2);
    REQUIRE(code.extends("lang") == "c++");
    REQUIRE(code.extends("author") == "betaest");
    REQUIRE_THROWS(code.extends("non exists"));

    auto child = code.children()->begin();

    REQUIRE(child->extends()->size() == 1);
    REQUIRE(child->extends("text") == "hello");
}

TEST_CASE("test keys", "[ast]") {
    p_ast_t root = std::make_shared<Ast>();

    auto p = root->add("p");
    auto code = p.children()->add(
        "code",
        {{"aaluna", "betaest"}, {"lang", "c++"}, {"author", "modified"}});
    code.children()->add({{"text", "hello"}, {"text", ","}, {"text", "world"}});
    code.extends("aaluna", "test");
    code.extends("avalue", "hello, test");
    code.extends("_urwrite", "it's good");

    auto extend_keys = keys(code.extends());

    REQUIRE(extend_keys.size() == 5);
    REQUIRE(code.extends("aaluna") == "test");
}