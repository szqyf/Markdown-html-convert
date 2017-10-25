#pragma once

#include <istream>
#include <memory>
#include "ast.h"
#include "noncopyable.h"

namespace ts {
class IParser : private noncopyable {
   public:
    virtual const AstNode from(std::istream &in) = 0;

    virtual const AstNode parse_line_from(std::istream &in) = 0;

    virtual const AstNode document() const = 0;

   public:
    virtual ~IParser() {}

   protected:
    AstNode make_ast(std::string tag = Ast::Root, std::string text = "") {
        return AstNode(new Ast(tag, text));
    }

    void reset_ast(AstNode &node) { node->reset(); }

    AstNode append_ast(AstNode &node, std::string tag, std::string text = "") {
        auto child = make_ast(tag, text);
        node->children_.push_back(child);
        return child;
    }

    AstNode &set_ast_extending(AstNode &node,
                               std::pair<std::string, std::string> value) {
        node->extendings_.insert(value);
        return node;
    }
};
}