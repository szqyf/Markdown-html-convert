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

const AstNode &Document::from(std::istream &in) {
    return document_;
    // std::string buf;
    // document_->clear_children();

    // auto node = document_->add_child("p");

    // while (!in.eof()) {
    //     bool fol = true;  // first of line

    //     {
    //         buf = read(in, [](char ch) { return std::isblank(ch); });
    //         auto b = buf.begin();
    //         auto size = buf.size();

    //         if (!buf.empty() && fol &&
    //             (size >= 4 || *b == '\t')) {  //行首是4个空格或者是tab
    //             fol = false;
    //             node = document_->add_child("codeblock");
    //             // todo: parse code block here
    //         } else if (!fol || (size >= 4 || *b == '\t')) {
    //             node->add_child("text", buf);

    //             int next = in.peek();

    //             if (size >= 2 &&
    //                 (next == 13 || next == 10)) {  //行末超过两个空格
    //                 node->add_child("br");
    //             }
    //         } else if (fol) {
    //             int next = in.peek();

    //             if (next == 13 || next == 10) {  //空行
    //                 node = document_->add_child("p");
    //             }
    //         }
    //     }

    //     {
    //         buf = read(in, [](char ch) {
    //             return ch < 0 || std::isalpha(ch) || std::isdigit(ch);
    //         });

    //         if (!buf.empty()) {
    //             fol = false;
    //             node->add_child("text", buf);
    //             // node->text += buf;
    //         }
    //     }

    //     {
    //         buf = read(in, [](char ch) { return std::ispunct(ch); });

    //         if (fol) {
    //             std::string header[]{"#",    "##",    "###",
    //                                  "####", "#####", "#######"};
    //             auto find =
    //                 std::find(std::begin(header), std::end(header), buf);

    //             if (find != std::end(header)) {
    //                 auto pos = std::distance(find, std::begin(header));
    //                 auto h = node->add_child("h");
    //                 h->add_extend({"level", std::to_string(pos)});
    //                 // todo: find text and continue set extendings here
    //             }
    //         }
    //     }

    //     buf = read(in, [](char ch) { return ch == '\n' || ch == '\r'; });
    // }

    // return document_;
}

const AstNode Document::parse_line_from(std::istream &in) {
    return document_;
}

const AstNode Document::document() const { return document_; }

Document::Document():document_("root") {
    
    // if (node == nullptr) document_ = node;
}
}