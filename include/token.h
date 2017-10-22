#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "noncopyable.h"

namespace ts {
class Syntax;
class Token : private noncopyable {
   public:
    /**
     * @brief 获取类型的唯一描述，可以从配置文件中获取
     *
     * @return std::string
     */
    const std::string tag() const { return tag_; }

    /**
     * @brief 该类型使用的属性值，可以在render的时候使用
     *
     * @return std::unordered_map<std::string, std::string>
     */
    const std::unordered_map<std::string, std::string> &properties() const {
        return properties_;
    }

    /**
     * @brief 返回父亲节点
     *
     * @return std::shared_ptr<Token>
     */
    const std::unique_ptr<Token> *parent() const { return parent_; }

    std::unique_ptr<Token> &add_child(std::string _tag) {
        auto token = std::unique_ptr<Token>(new Token(_tag, current_));
        children_.emplace_back(token);
    }

   private:
    std::string tag_;
    std::unordered_map<std::string, std::string> properties_;
    std::unique_ptr<Token> *parent_, *current_;
    std::vector<std::unique_ptr<Token>> children_;

   public:
    static const std::string Root = "Root";

    static std::unique_ptr<Token> make_root() {
        return std::unique_ptr<Token>(new Token(Root, nullptr));
    }

    static bool remove(
        const std::vector<std::unique_ptr<Token>>::iterator &it) {
        auto p = *it->parent();

        if (p != null) (*p)->children.erase(it);

        return true;
    }

   private:
    Token(std::string _tag, std::unique_ptr<Token> *_p)
        : tag_(_tag), parent_(_p) {}
};
}