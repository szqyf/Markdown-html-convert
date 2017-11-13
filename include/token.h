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
    void unread();
    void push_env();
    void pop_env();
    void clear_env();

   public:
    const token_t token() const;
    const std::string str() const;
    const bool eof() const;
    const bool has_puncation(std::string s) const;
    const bool all_space() const;

    bool enable_escaped() const { return enable_escaped_; }
    void enable_escaped(bool value) { enable_escaped_ = value; }
    char escaped_char() const { return escaped_ch_; }
    void escaped_char(char ch) { escaped_ch_ = ch; }

   private:
    std::vector<std::tuple<token_t, std::string>> stack_;
    std::istream in_;
    size_t cur_, saved_;
    readed_t readed_;
    bool enable_escaped_;
    char escaped_ch_;

   public:
    Token(std::istream &in, readed_t readed = nullptr)
        : in_(in.rdbuf()),
          cur_(0),
          saved_(-1),
          readed_(readed),
          enable_escaped_(true),
          escaped_ch_('\\') {}
};
}  // namespace ts