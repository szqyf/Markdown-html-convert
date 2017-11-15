#include <gfm_parser.h>
#include <html_render.h>
#include <catch.hpp>
#include <iostream>
#include <sstream>

using namespace std;

TEST_CASE("basic render", "[render]") {
    gfm::Parser document;

    stringstream ss{R"([text\]](icon\ .jpg "Hello world\"list"))"};
    auto p = document.from(ss);

    html::Render render;
    auto h = render.render(p);

    cout << h << endl;
}