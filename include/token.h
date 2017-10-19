#pragma once

#include <string>
#include <unordered_map>

namespace md {
enum class TokenSymbol {};

class Token {
public:
private:
    std::unordered_map<std::string, std::string> properties_;
    TokenSymbol token_;
};
}