#pragma once
#include <istream>
#include <string>
#include <tuple>
#include <vector>

namespace ts {
enum class token_t : char { blank, word, punctation, endl, end };

class Token {
   public:
    bool read();
    void push();
    void pop();

    const token_t token() const;
    const std::string str() const;

   private:
    struct _bag_t {
        token_t token;
        std::string str;
        _bag_t(token_t t, std::string s) : token(t), str(s) {}
    };
    std::vector<_bag_t> stack_;
    std::istream in_;
    int cur_, saved_;

   public:
    Token(std::istream &in) : in_(in.rdbuf()), cur_(0), saved_(-1) {}
};
}