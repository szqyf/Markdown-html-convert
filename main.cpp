#include <translator.h>
#include <iostream>

int main() {
    auto gfm = ts::make_parser("gfm");
    auto html = ts::make_render("html");
    const std::istream &in = std::cin;

    {  //一行行读取并输出
        auto token = ts::make_root();
        while (!in.eof()) {
            auto line = gfm->parse_line(in, token);
            std::cout << html->render(line) << std::endl;
        }
    }

    {  //全部读取并输出
        auto token = gfm->parse(in);
        std::cout << html->render(token) << std::endl;
    }
}