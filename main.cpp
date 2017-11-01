#include <translator.h>
#include <iostream>

int main() {
    auto &in = std::cin;
    auto &out = std::cout;

    auto gfm = ts::make_parser("gfm");
    auto html = ts::make_render("html");

    ts::set_default_render(html);

    {  //一行行读取并输出
        // auto tag = ts::make_root();
        ts::AstNode line{"root"};
        do {
            line = gfm->parse_line_from(in);
            out << line;
        } while (true);

        std::cout << "Whole Html is: " << std::endl;
        std::cout << gfm->document() << std::endl;
    }

    {  //全部读取并输出
        in >> gfm;
        out << gfm->document();
    }
}