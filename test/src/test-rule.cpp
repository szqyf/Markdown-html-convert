#include <rules.h>
#include <catch.hpp>

using namespace gfm;

TEST_CASE("AtxHeading", "[rules]") { REQUIRE(rules[0]->tag() == "h"); }