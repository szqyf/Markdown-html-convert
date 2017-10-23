#include <translator.h>
#include <iostream>

int main() {
    const std::istream &in = std::cin;
    const std::ostream &out = std::cout;

    auto gfm = ts::make_parser("gfm", in);
    auto html = ts::make_render("html", out);

    {  //一行行读取并输出
        // auto tag = ts::make_root();
        ts::AstNode line;
        do {
            line = gfm->parse_line();
            html->render(line);
        } while (line != nullptr);

        std::cout << "Whole Html is: " << std::endl;
        html->render(gfm->document());
    }

    {  //全部读取并输出
        auto tag = gfm->parse();
        html->render(tag);
    }
}