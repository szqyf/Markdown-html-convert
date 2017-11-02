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
using nodes_t = std::vector<AstNode>;
using extend_t = std::unordered_map<std::string, std::string>;
using p_ext_t = std::shared_ptr<extend_t>;
using p_ast_t = std::shared_ptr<Ast>;
class Ast : protected nodes_t, public std::enable_shared_from_this<Ast> {
   public:
    using nodes_t::empty;
    using nodes_t::size;
    using nodes_t::begin;
    using nodes_t::end;
    using nodes_t::rbegin;
    using nodes_t::rend;
    using nodes_t::at;
    using nodes_t::operator[];
    using nodes_t::clear;
    using nodes_t::iterator;
    using nodes_t::const_iterator;

    AstNode &add(std::string tag, std::string text = "");
    AstNode &add(std::string tag, extend_t _init);

    p_ast_t remove(const AstNode &node);
    p_ast_t remove(size_t pos);
    // void clear() { nodes_.clear(); }

   public:
    explicit Ast() {}
};

class AstNode {
   private:
    std::string tag_;
    // std::string text_;
    p_ext_t extends_;
    p_ast_t children_;

   public:
    const std::string tag() const { return tag_; }
    // const std::string text() const { return text_; }

    void tag(std::string tag) { tag_ = tag; }
    // void text(std::string text) { text_ = text; }

    p_ext_t extends() { return extends_; }
    const std::string &extends(std::string key) const {
        return extends_->at(key);
    }
    extend_t &extends_r() { return *extends_; }
    p_ast_t children() { return children_; }
    Ast &children_r() { return *children_; }
    const AstNode &children(size_t pos) const { return children_->at(pos); }

   public:
    const nodes_t::const_iterator begin() { return children_->begin(); }
    const nodes_t::const_iterator end() { return children_->end(); }
    bool operator==(const AstNode &node) { return this == &node; }

   public:
    explicit AstNode(std::string _tag, std::string _text = "") : tag_(_tag) {
        children_ = std::make_shared<Ast>();
        extends_ = std::make_shared<extend_t>();
        if (!_text.empty()) extends_->emplace("value", _text);
    }

    explicit AstNode(std::string _tag, extend_t _init) : AstNode(_tag) {
        extends_->swap(_init);
    }
};
}