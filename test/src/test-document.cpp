#include <document.h>
#include <token.h>
#include <catch.hpp>
#include <sstream>
#include <tuple>

using namespace std;
using namespace ts;

TEST_CASE("token class", "[document]") {
    stringstream ss{"http://来测试下！   \t\n1."};
    Token token{ss};

    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "http");

    token.read();
    REQUIRE(token.token() == token_t::punctation);
    REQUIRE(token.str() == ":");

    token.push_env();
    token.read();
    REQUIRE(token.token() == token_t::punctation);
    REQUIRE(token.str() == "//");

    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "来测试下！");

    token.pop_env();
    token.read();
    REQUIRE(token.token() == token_t::punctation);
    REQUIRE(token.str() == "//");

    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "来测试下！");

    token.read();
    REQUIRE(token.token() == token_t::blank);
    REQUIRE(token.str() == "   \t");

    token.read();
    REQUIRE(token.token() == token_t::endl);
    REQUIRE(token.str() == "\n");

    token.push_env();
    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "1");

    token.pop_env();
    REQUIRE(token.token() == token_t::endl);
    REQUIRE(token.str() == "\n");

    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "1");

    token.read();
    REQUIRE(token.token() == token_t::punctation);
    REQUIRE(token.str() == ".");

    token.read();
    REQUIRE(token.token() == token_t::end);
    REQUIRE(token.str().empty());
}

TEST_CASE("document linktext", "[document]") {
    gfm::Document document;
    stringstream ss {"http://www.sz.js.cn link"};
    auto p = document.from(ss);

    REQUIRE (p.children()->size() == 1);
    REQUIRE (p.children(0).tag() == "p");
    REQUIRE (p.children(0).children()->size() == 3);
}

TEST_CASE("document text", "[document]") {
    gfm::Document document;

    stringstream ss {"link\\ \\[]\\\n"};
    auto p = document.from(ss);

    REQUIRE(p.children()->size() == 1);
    REQUIRE(p.children()->at(0).children()->size() == 7);

    p = p.children()->at(0);
    REQUIRE(p.children(0).extends("text") == "link");
    REQUIRE(p.children(1).extends("text") == "\\");
    REQUIRE(p.children(2).extends("text") == " ");
    REQUIRE(p.children(3).extends("text") == "[");
    REQUIRE(p.children(4).extends("text") == "]");
    REQUIRE(p.children(5).extends("text") == "\\");
    REQUIRE(p.children(6).extends("text") == "\n");    
}