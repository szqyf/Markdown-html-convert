#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "noncopyable.h"

namespace ts {
class Ast;
class AstNode;
using p_ast_t = std::shared_ptr<Ast>;
using nodes_t = std::vector<AstNode>;
using extend_t = std::unordered_map<std::string, std::string>;
using p_ext_t = std::shared_ptr<extend_t>;
class AstNode {
    friend class Ast;

   private:
    std::string tag_;
    std::string text_;
    p_ext_t extends_;
    p_ast_t children_;
    nodes_t::iterator me_;

   public:
    const std::string tag() const { return tag_; }
    const std::string text() const { return text_; }

    void set_tag(std::string tag) { tag_ = tag; }
    void set_text(std::string text) { text_ = text; }

    p_ext_t extends() { return extends_; }
    extend_t &extends_r() { return *extends_; }
    p_ast_t children() { return children_; }
    Ast &children_r() { return *children_; }

    const nodes_t::iterator me() const { return me_; }

   public:
    const nodes_t::const_iterator begin();
    const nodes_t::const_iterator end();

   public:
    AstNode(std::string _tag, std::string _text = "", p_ast_t _parent = nullptr)
        : tag_(_tag), text_(_text) {
        children_ = std::make_shared<Ast>(_parent);
        extends_ = std::make_shared<extend_t>();
    }
};

class Ast : public std::enable_shared_from_this<Ast> {
   private:
    nodes_t nodes_;
    p_ast_t parent_;

   public:
    const bool empty() const { return nodes_.empty(); }
    const size_t size() const { return nodes_.size(); }

    const AstNode &at(int index) const { return nodes_.at(index); }
    const nodes_t::const_iterator begin() const { return nodes_.begin(); }
    const nodes_t::const_iterator end() const { return nodes_.end(); }

    AstNode &add(std::string tag, std::string text = "");
    p_ast_t remove(AstNode node);
    p_ast_t remove(int pos);
    void clear() { nodes_.clear(); }

   public:
    explicit Ast(p_ast_t _parent = nullptr) : parent_(_parent) {}
};
}