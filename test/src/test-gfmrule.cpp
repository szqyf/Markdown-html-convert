#include <rules.h>
#include <catch.hpp>
#include <ast.h>
#include <sstream>

using namespace ts;
using namespace gfm;

TEST_CASE("AtxHeading", "[rules]") { 
    REQUIRE(rules[0]->tag() == "h"); 
}