#include <document.h>
#include <algorithm>
#include <cctype>
#include <functional>
#include <string>

using namespace ts;
namespace gfm {

using read_f = std::function<bool(char)>;

std::string read(std::istream &in, read_f reader) {
    std::string buf;
    char ch;

    while (!in.eof() && in.get(ch))
        if (reader(ch))
            buf += ch;
        else
            break;

    return buf;
}

const AstNode Document::from(std::istream &in) {
    std::string buf;
    // document_->reset();
    reset_ast(document_);
    node = append_ast(document_, "p");

    while (!in.eof()) {
        bool fol = true;  // first of line

        {
            buf = read(in, [](char ch) {
                return ch < 0 || std::isalpha(ch) || std::isdigit(ch);
            });

            if (!buf.empty()) {
                fol = false;
                append_ast(node, "text", buf);
                // node->text += buf;
            }
        }

        {
            buf = read(in, [](char ch) { return std::isblank(ch); });
            auto b = buf.begin();
            auto size = buf.size();

            if (!buf.empty() && fol &&
                (size >= 4 || *b == '\t')) {  //行首是4个空格或者是tab
                fol = false;
                node = append_ast(node, "codeblock");
                //todo: parse code block here
            } else if (!fol || (size >= 4 || *b == '\t')) {
                append_ast(node, "text", buf);

                int next = in.peek();

                if (size >= 2 &&
                    (next == 13 || next == 10)) {  //行末超过两个空格
                    append_ast(node, "br");
                }
            }
        }

        {
            buf = read(in, [](char ch) { return std::ispunct(ch); });
            std::string header[]{"#", "##", "###", "####", "#####", "#######"};
            auto find = std::find(std::begin(header), std::end(header), buf);

            if (find != std::end(header)) {
                auto pos = std::distance(find, std::begin(header));
                auto h = append_ast(node, "h");
                set_ast_extending(h, {"level", std::to_string(pos)});
                //todo: find text and continue set extendings here
            }
        }

        buf = read(in, [](char ch) { return ch == '\n' || ch == '\r'; });
    }

    return document_;
}

const AstNode Document::parse_line_from(std::istream &in) { return nullptr; }

const AstNode Document::document() const { return document_; }

Document::Document(AstNode node) : document_(node) {
    if (node == nullptr) document_ = node;
}
}