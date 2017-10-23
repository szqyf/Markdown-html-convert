#include <translator.h>
#include <iostream>

int main() {
    auto gfm = ts::make_parser("gfm");
    auto html = ts::make_render("html");
    const std::istream &in = std::cin;

    {  //一行行读取并输出
        // auto tag = ts::make_root();
        while (!in.eof()) {
            auto line = gfm->parse_line(in);
            std::cout << html->render(line) << std::endl;
        }

        std::cout << "Whole Html is: " << std::endl
                  << html->render(gfm->document()) << std::endl;
    }

    {  //全部读取并输出
        auto tag = gfm->parse(in);
        std::cout << html->render(tag) << std::endl;
    }
}