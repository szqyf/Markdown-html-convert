#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "noncopyable.h"

namespace ts {
class Ast;
using AstNode = std::shared_ptr<Ast>;
using Asts = std::vector<AstNode>;

class Ast final : private noncopyable,
                  public std::enable_shared_from_this<Ast> {
   private:
    using extend_t = std::unordered_map<std::string, std::string>;
    using vchildren_t = std::function<void(Asts::iterator)>;
    using vextends_t = std::function<void(extend_t::iterator)>;

   public:
    const std::string tag() const { return tag_; }

    const std::string text() const { return text_; }

    // const extend_t &extends() const { return extends_; }

    // const Asts &children() const { return children_; }

    const Asts::iterator me() const { return me_; }

    const AstNode parent() const { return parent_; }

   private:
    std::string tag_;
    std::string text_;
    extend_t extends_;
    Asts children_;
    Asts::iterator me_;
    AstNode parent_;

   public:
    static const std::string Root;

   public:
    Ast(std::string _tag = Root, std::string _text = "")
        : tag_(_tag), text_(_text) {}

   public:
    const size_t size() const { return children_.size(); }

    const bool empty() const { return children_.empty(); }

    const size_t extend_size() const { return extends_.size(); }

    const bool extend_empty() const { return extends_.empty(); }

    const AstNode add_child(std::string _tag, std::string _text = "");

    void remove_child(AstNode node);

    void clear_children() { children_.clear(); }

    void visit_children(vchildren_t visit);

    AstNode add_extend(std::pair<std::string, std::string> value);

    AstNode remove_extend(std::string name);

    void clear_extends() { extends_.clear(); }

    void visit_extends(vextends_t visit);

    //    private:
    //     void reset() {
    //         text_ = "";
    //         children_.clear();
    //         extendings_.clear();
    //     }
};
}