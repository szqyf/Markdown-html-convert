#include <document.h>

using namespace ts;
namespace gfm {
AstNode Document::from(std::istream &in) { return nullptr; }

AstNode Document::parse_line_from(std::istream &in) { return nullptr; }

const AstNode Document::document() { return document_; }

Document::Document(AstNode node) : document_(node) {
    if (node == nullptr) document = node_;
}
}