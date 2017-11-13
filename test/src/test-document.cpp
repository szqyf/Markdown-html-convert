﻿#include <document.h>
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

TEST_CASE("escaped token", "[document]") {
    stringstream ss{"\\ht\\tp:\\//来测试下！ \\  \t\\\n1."};
    Token token{ss};

    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "\\ht");

    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "\\tp");

    token.read();
    REQUIRE(token.token() == token_t::punctation);
    REQUIRE(token.str() == ":");

    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "/");

    token.read();
    REQUIRE(token.token() == token_t::punctation);
    REQUIRE(token.str() == "/");
}

TEST_CASE("document linktext", "[document]") {
    gfm::Document document;
    stringstream ss{"http://www.sz.js.cn link"};
    auto p = document.from(ss);

    REQUIRE(p.children()->size() == 1);
    REQUIRE(p.children(0).tag() == "p");
    REQUIRE(p.children(0).children()->size() == 3);
    REQUIRE(p.children(0).children(0).tag() == "a");
    REQUIRE(p.children(0).children(1).tag() == "text");
    REQUIRE(p.children(0).children(2).tag() == "text");
}

TEST_CASE("document text", "[document]") {
    gfm::Document document;

    stringstream ss{"link\\ \\[]\\\n"};
    auto p = document.from(ss);

    REQUIRE(p.children()->size() == 1);
    REQUIRE(p.children()->at(0).children()->size() == 5);

    p = p.children()->at(0);
    REQUIRE(p.children(0).extends("text") == "link");
    REQUIRE(p.children(1).extends("text") == "\\ ");
    REQUIRE(p.children(2).extends("text") == "[");
    REQUIRE(p.children(3).extends("text") == "]");
    REQUIRE(p.children(4).extends("text") == "\n\n");
}

TEST_CASE("img", "[document]") {
    gfm::Document document;

    stringstream ss{R"(![text\]](icon\ .jpg "Hello world\"list"))"};
    auto p = document.from(ss);

    REQUIRE(p.children()->size() == 1);

    p = p.children()->at(0);

    REQUIRE(p.children()->size() == 1);
    REQUIRE(p.children(0).tag() == "img");
    REQUIRE(p.children(0).extends("alt") == "text]");
    REQUIRE(p.children(0).extends("src") == "icon\\ .jpg");
    REQUIRE(p.children(0).extends("title") == "Hello world\"list");
}

TEST_CASE("img ref", "[document]") {
    gfm::Document document;

    stringstream ss{R"(![text\]][test \]])"};
    auto p = document.from(ss);

    REQUIRE(p.children()->size() == 1);

    p = p.children()->at(0);

    REQUIRE(p.children()->size() == 1);
    REQUIRE(p.children(0).tag() == "img");
    REQUIRE(p.children(0).extends("alt") == "text]");
    REQUIRE(p.children(0).extends("src") == "test ]");
    REQUIRE(p.children(0).extends("is_ref") == "true");
}

TEST_CASE("link", "[document]") {
    gfm::Document document;

    stringstream ss{R"([text\]](icon\ .jpg "Hello world\"list"))"};
    auto p = document.from(ss);

    REQUIRE(p.children()->size() == 1);

    p = p.children()->at(0);

    REQUIRE(p.children()->size() == 1);
    REQUIRE(p.children(0).tag() == "a");
    REQUIRE(p.children(0).extends("href") == "icon\\ .jpg");
    REQUIRE(p.children(0).extends("title") == "Hello world\"list");
    REQUIRE(p.children(0).children()->size() == 1);
    REQUIRE(p.children(0).children(0).extends("text") == "text]");
}

TEST_CASE("link ref", "[document]") {
    gfm::Document document;

    stringstream ss{R"([text\]][test \]])"};
    auto p = document.from(ss);

    REQUIRE(p.children()->size() == 1);

    p = p.children()->at(0);

    REQUIRE(p.children()->size() == 1);
    REQUIRE(p.children(0).tag() == "a");
    REQUIRE(p.children(0).extends("href") == "test ]");
    REQUIRE(p.children(0).extends("is_ref") == "true");
    REQUIRE(p.children(0).children()->size() == 1);
    REQUIRE(p.children(0).children(0).extends("text") == "text]");
}