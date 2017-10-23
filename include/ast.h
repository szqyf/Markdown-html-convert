#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "noncopyable.h"

namespace ts {
class Ast;
using Asts = std::vector<std::shared_ptr<Ast>>;
using AstNode = std::shared_ptr<Ast>;

class Ast final : private noncopyable {
   public:
    /**
     * @brief 获取类型的唯一描述，可以从配置文件中获取
     *
     * @return std::string
     */
    const std::string tag() const { return tag_; }

    const std::string text() const { return text_; }

    const std::unordered_map<std::string, std::string> extendings() const {
        return extendings_;
    }

    const Asts &children() const { return children_; }

    const bool is_root() { return tag_ == Root; }

    void clear() {
        children_.clear();
        extendings_.clear();
        text_ = "";
    }

   private:
    std::string tag_;
    std::string text_;
    std::unordered_map<std::string, std::string> extendings_;
    // std::unique_ptr<Token> *parent_, *current_;
    Asts children_;

   public:
    static const std::string Root;

    static AstNode make_root() { return AstNode(new Ast(Root)); }

   private:
    Ast(std::string _tag) : tag_(_tag) {}
};
}