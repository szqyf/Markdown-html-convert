#pragma once

#include <string>
#include <unordered_map>

namespace md {
class Token {
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
        return properties;
    }

  private:
    std::string tag_;
    std::unordered_map<std::string, std::string> properties_;
};
}