#include <parser.h>

namespace ts {
IParser::AstHelper &IParser::AstHelper::operator=(IParser::AstHelper &&oth) {
    if (this != &oth) {
        this->node_ = oth.node_;
        oth.node_ = nullptr;
    }

    return *this;
}

void IParser::AstHelper::reset() {
    node_->text_ = "";
    node_->children_.clear();
    node_->extendings_.clear();
}

IParser::AstHelper IParser::AstHelper::push_leaf(std::string tag,
                                                 std::string text) {
    auto node = AstNode(new Ast(tag, text));
    node_->children_.push_back(node);

    return IParser::AstHelper(node);
}

IParser::AstHelper &IParser::AstHelper::set_extendings(
    std::pair<std::string, std::string> value) {
    node_->extendings_.emplace(value);
    
    return *this;
}
}