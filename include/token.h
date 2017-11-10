#pragma once
#include <functional>
#include <istream>
#include <string>
#include <tuple>
#include <vector>

namespace ts {
enum class token_t : char { blank, word, punctation, endl, end };

class Token {
   public:
    using postread_t = std::function<void(token_t &, std::string &)>;
    bool read();
    void push();
    void pop();
    void on_postread(postread_t postread);

   public:
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
    postread_t postread_;

   public:
    Token(std::istream &in)
        : in_(in.rdbuf()), cur_(0), saved_(-1), postread_(nullptr) {}
};
}  // namespace ts