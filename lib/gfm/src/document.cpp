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

AstNode Document::from(std::istream &in) {
    std::string buf;
    document_->clear();

    while (!in.eof()) {
        AstNode node;

        buf = read(in, [](char ch) {
            return ch < 0 || std::isalpha(ch) || std::isdigit(ch);
        });

        if (!buf.empty())
            node = Ast::make("p", text);

        buf = read(in, [](char ch) { return std::isblank(ch); });

        if (!buf.empty())
            
    }

    return document_;
}

AstNode Document::parse_line_from(std::istream &in) { return nullptr; }

const AstNode Document::document() const { return document_; }

Document::Document(AstNode node) : document_(node) {
    if (node == nullptr) document_ = node;
}
}