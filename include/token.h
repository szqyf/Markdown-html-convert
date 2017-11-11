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
    using readed_t = std::function<void(token_t &, std::string &)>;
    bool read();
    void push_env();
    void pop_env();
    void clear_env();
    void skip(size_t step);

   public:
    const token_t token() const;
    const std::string str() const;

   private:
    // struct _bag_t {
    //     token_t token;
    //     std::string str;
    //     _bag_t(token_t t, std::string s) : token(t), str(s) {}
    // };
    std::vector<std::tuple<token_t, std::string>> stack_;
    std::istream in_;
    size_t cur_, saved_;
    readed_t readed_;

   public:
    Token(std::istream &in, readed_t readed = nullptr)
        : in_(in.rdbuf()), cur_(0), saved_(-1), readed_(readed) {}
};
}  // namespace ts