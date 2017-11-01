#include <ast.h>
#include <memory>

namespace ts {
const std::string Ast::Root = "root";

const AstNode Ast::add_child(std::string _tag, std::string _text) {
    children_.emplace_back(std::make_shared<Ast>(_tag, _text));
    me_ = children_.end();
    me_--;

    (*me_)->me_ = me_;
    (*me_)->parent_ = shared_from_this();

    return *me_;
}

void Ast::remove_child(AstNode node) { children_.erase(node->me_); }

void Ast::visit_children(Ast::vchildren_t visit) {
    for (auto& c : children_) visit(c);
}

AstNode Ast::add_extend(std::pair<std::string, std::string> value) {
    extends_.emplace(value);
    return shared_from_this();
}

AstNode Ast::remove_extend(std::string name) {
    extends_.erase(name);
    return shared_from_this();
}

void Ast::visit_extends(Ast::vextends_t visit) {
    for (auto& e : extends_) visit(e);
}
}