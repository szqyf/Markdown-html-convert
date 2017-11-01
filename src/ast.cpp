#include <ast.h>
#include <memory>
#include <stdexcept>

namespace ts {
const nodes_t::const_iterator AstNode::begin() { return children_->begin(); }
const nodes_t::const_iterator AstNode::end() { return children_->end(); }

AstNode &Ast::add(std::string tag, std::string text) {
    nodes_.emplace_back(tag, text, shared_from_this());
    auto node = nodes_.end() - 1;
    node->me_ = node;

    return *node;
}

p_ast_t Ast::remove(AstNode node) {
    nodes_.erase(node.me_);
    return shared_from_this();
}

p_ast_t Ast::remove(int pos) {
    try {
        auto node = nodes_.at(pos);
        return remove(node);
    } catch (std::out_of_range &e) {
        return shared_from_this();
    }
}
}