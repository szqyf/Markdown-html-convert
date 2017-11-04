#include <document.h>
#include <utils.h>
#include <catch.hpp>
#include <sstream>
#include <tuple>

using namespace gfm;
using namespace std;

TEST_CASE("test read_token", "[document]") {
    stringstream ss{"http://来测试下！   \t\n1."};

    auto token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::word);
    REQUIRE(get<1>(token) == "http");

    token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::punctation);
    REQUIRE(get<1>(token) == ":");

    token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::punctation);
    REQUIRE(get<1>(token) == "//");

    token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::word);
    REQUIRE(get<1>(token) == "来测试下！");

    token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::blank);
    REQUIRE(get<1>(token) == "   \t");

    token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::endl);
    REQUIRE(get<1>(token) == "\n");

    token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::word);
    REQUIRE(get<1>(token) == "1");

    token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::punctation);
    REQUIRE(get<1>(token) == ".");

    token = read_token(ss);
    REQUIRE(get<0>(token) == token_t::end);
    REQUIRE(get<1>(token).empty());
}
