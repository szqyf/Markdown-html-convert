#include <ast.h>
#include <catch.hpp>
#include <iostream>
#include <memory>

using namespace ts;

TEST_CASE("create AstNode", "[AstHelper]") {
    AstNode node = std::make_shared<Ast>();

    auto h = node->add_child("h");
    h->add_extend({"level", "1"});
    h->add_extend({"text", "run here"});

    auto p = node->add_child("p");
    p->add_child("text", "hello");
    auto br = p->add_child("br");

    REQUIRE(!node->empty());
    REQUIRE(node->size() == 2);

    h = node->children()[0];
    auto hext = h->extends();
    REQUIRE(!h->extends().empty());
    REQUIRE(hext["level"] == "1");
    REQUIRE(hext["text"] == "run here");

    h->remove_extend("level");
    REQUIRE(h->extends().size() == 1);

    h->clear_extends();
    REQUIRE(h->extends().empty());

    // REQUIRE(h->extends().at("level") == nullptr);

    p = node->children()[1];
    REQUIRE(p->size() == 2);
    auto pc = p->children();
    REQUIRE(pc[0]->tag() == "text");
    REQUIRE(pc[0]->text() == "hello");
    REQUIRE(pc[1]->tag() == "br");
    REQUIRE(pc[1]->text() == "");

    p->remove_child(br);
    REQUIRE(p->size() == 1);

    p->clear_children();
    REQUIRE(p->empty());
}