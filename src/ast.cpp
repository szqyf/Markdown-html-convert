#include <ast.h>
#include <memory>

namespace ts {
const std::string Ast::Root = "root";

const AstNode Ast::add_child(std::string _tag, std::string _text) {
    children_.emplace_back(std::make_shared<Ast>(_tag, _text));
    me_ = children_.end();
    me_--;

    return *me_;
}

void Ast::remove_child(AstNode node) { children_.erase(node->me_); }

void Ast::add_extend(std::pair<std::string, std::string> value) {
    extendings_.emplace(value);
}

void Ast::remove_extend(std::string name) { extendings_.erase(name); }
}