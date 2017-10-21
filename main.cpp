#include <translator.h>
#include <iostream>

int main() {
    auto gfm = ts::make_parser("gfm");
    auto html = ts::make_render("html");
    const std::istream &in = std::cin;

    {  //一行行读取并输出
        auto token = ts::make_root_token();
        while (!in.eof()) {
            auto line = gfm->parse_line(in, token);
            auto str = html->render(line);
            std::cout << str << std::endl;
        }
    }

    {  //全部读取并输出
        auto tk = gfm->parse(in);
        std::cout << html->render(tk) << std::endl;
    }
}