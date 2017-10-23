#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "noncopyable.h"

namespace ts {
class Tag;
using Tags = std::vector<std::shared_ptr<Tag>>;
using TagPtr = std::shared_ptr<Tag>;

class Tag final : private noncopyable {
   public:
    /**
     * @brief 获取类型的唯一描述，可以从配置文件中获取
     *
     * @return std::string
     */
    const std::string tag() const { return tag_; }

    const std::string text() const { return text_; }

    const std::unordered_map<std::string, std::string> extends() const {
        return extends_;
    }

    const Tags &children() const { return children_; }

    const bool is_root() { return tag_ == Root; }

    void clear() {
        children_.clear();
        extends_.clear();
        text_ = "";
    }

   private:
    std::string tag_;
    std::string text_;
    std::unordered_map<std::string, std::string> extends_;
    // std::unique_ptr<Token> *parent_, *current_;
    Tags children_;

   public:
    static const std::string Root;

    static TagPtr make_root() { return TagPtr(new Tag(Root)); }

   private:
    Tag(std::string _tag) : tag_(_tag) {}
};
}