#include <ast.h>
#include <memory>

namespace ts {
AstNode &Ast::add(std::string tag, std::string text) {
    nodes_.emplace_back(tag, text, shared_from_this());
    auto node = nodes_.end();
    node--;
    node->me_ = node;

    return *node;
    // auto
}

p_ast_t Ast::remove(AstNode node) {
    nodes_.erase(node.me_);
    return shared_from_this();
}
}