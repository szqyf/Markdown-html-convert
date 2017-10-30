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
class IParser;

class Ast final : private noncopyable {
   private:
    friend class IParser;
    using extend_t = std::unordered_map<std::string, std::string>;

   public:
    const std::string tag() const { return tag_; }

    const std::string text() const { return text_; }

    const extend_t &extendings() const { return extendings_; }

    const Asts &children() const { return children_; }

   private:
    std::string tag_;
    std::string text_;
    extend_t extendings_;
    Asts children_;

   public:
    static const std::string Root;

   private:
    Ast(std::string _tag, std::string _text) : tag_(_tag), text_(_text) {}

//    private:
//     void reset() {
//         text_ = "";
//         children_.clear();
//         extendings_.clear();
//     }
};
}