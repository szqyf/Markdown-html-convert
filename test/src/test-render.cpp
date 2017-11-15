#include <gfm_parser.h>
#include <html_render.h>
#include <catch.hpp>
#include <iostream>
#include <sstream>

#include <tools.h>

using namespace std;
using namespace html;

TEST_CASE("basic render", "[render]") {
    gfm::Parser document;

    stringstream ss{R"([text\]](icon\ .jpg "Hello world\"list"))"};
    auto p = document.from(ss);

    html::Render render;
    auto h = render.render(p);

    cout << h << endl;
}

TEST_CASE("encodeString test", "[render]") {
    //std::string str{"< > &amp; & &#x10; \""};
    std::string str{"< > & &amp; &amp; \""};

    //REQUIRE(encodeString(str, cAmps|cDoubleAmps|cAngles|cQuotes) =="&lt; &gt; &amp; &amp; &#x10; &quot;") ;
    REQUIRE(encodeString(str, cAmps|cDoubleAmps|cAngles|cQuotes) =="&lt; &gt; &amp; &amp; &amp;  &quot;") ;

}