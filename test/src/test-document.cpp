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

    token.push();
    token.read();
    REQUIRE(token.token() == token_t::punctation);
    REQUIRE(token.str() == "//");

    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "来测试下！");

    token.pop();
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

    token.push();
    token.read();
    REQUIRE(token.token() == token_t::word);
    REQUIRE(token.str() == "1");

    token.pop();
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
