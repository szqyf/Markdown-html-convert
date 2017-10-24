#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "noncopyable.h"

namespace ts {
class Ast;
using AstNode = std::shared_ptr<Ast>;
using Asts = std::vector<AstNode>;

class Ast final : private noncopyable {
   public:
    const std::string tag() const { return tag_; }

    const std::string text() const { return text_; }

    std::unordered_map<std::string, std::string> &extendings() {
        return extendings_;
    }

    Asts &children() { return children_; }

    void clear() {
        children_.clear();
        extendings_.clear();
        text_ = "";
    }

   private:
    std::string tag_;
    std::string text_;
    std::unordered_map<std::string, std::string> extendings_;
    Asts children_;

   public:
    static const std::string Root;

    static AstNode make(std::string tag = Root, std::string text = "") {
        return AstNode(new Ast(tag, text));
    }

   private:
    Ast(std::string _tag, std::string _text) : tag_(_tag), text_(_text) {}
};
}