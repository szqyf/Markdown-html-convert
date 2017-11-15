#include <translator.h>
#include <iostream>

int main() {
    auto &in = std::cin;
    auto &out = std::cout;

    auto gfm = ts::make_parser("gfm");
    auto html = ts::make_render("html");

    ts::set_default_render(html);

    {  //全部读取并输出
        in >> gfm;
        out << gfm;
        // out << html->render(gfm->document());
    }
}