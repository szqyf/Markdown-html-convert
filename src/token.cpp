#include <token.h>
#include <cctype>
#include <map>
#include <tuple>
#include <vector>

namespace ts {
inline bool isblank(char c) { return c > 0 && std::isblank(c); }
inline bool isword(char c) { return c < 0 || std::isalnum(c); }
inline bool ispunct(char c) { return c > 0 && std::ispunct(c); }
inline bool isendl(char c) {
    return c > 0 && std::isspace(c) && !std::isblank(c);
}
inline token_t get_token_by_char(char c) {
    if (isblank(c)) return token_t::blank;
    if (isword(c)) return token_t::word;
    if (ispunct(c)) return token_t::punctation;
    if (isendl(c)) return token_t::endl;
    return token_t::end;
}

void Token::push_env() { saved_ = stack_.size(); }

void Token::pop_env() {
    cur_ = saved_;
    saved_ = -1;
}

void Token::clear_env() {
    cur_ = stack_.size();
    saved_ = -1;
}

void Token::skip(size_t step) {
    cur_ += step;
    if (cur_ < 0) cur_ = 0;
    if (cur_ > stack_.size()) cur_ = stack_.size();
}

const token_t Token::token() const {
    return cur_ == 0 ? token_t::endl : std::get<0>(stack_[cur_ - 1]);
}

const std::string Token::str() const {
    return cur_ == 0 ? "" : std::get<1>(stack_[cur_ - 1]);
}

bool Token::read() {
    auto size = stack_.size();

    if (cur_ == size) {
        std::string r;
        char c, p = 0;
        token_t tk = token_t::end;

        if (in_.get(c)) {
            if (enable_escaped_ && c == escaped_ch_) {
                tk = token_t::word;

                if (in_.get(c)) {
                    token_t t = get_token_by_char(c);

                    switch (t) {
                        case token_t::word:
                        case token_t::blank:
                            r.push_back(escaped_ch_);
                            r.push_back(c);
                            break;
                        case token_t::punctation:
                            r = c;
                            break;
                        case token_t::endl:
                            r.push_back(c);
                            r.push_back(c);
                            tk = token_t::endl;
                            break;
                    }
                } else {
                    r = escaped_ch_;
                }
            } else {
                tk = get_token_by_char(c);
                r = c;
            }

            p = c;

            while (in_.get(c)) {
                token_t t = get_token_by_char(c);

                if (t == tk && !(tk == token_t::punctation && p != c)) {
                    r += (p = c);
                } else {
                    in_.unget();
                    break;
                }
            }
        }

        if (readed_ != nullptr) readed_(tk, r);

        stack_.emplace_back(std::make_tuple(tk, r));
    }
    cur_++;

    return token() != token_t::end;
}

std::string Token::trunc(size_t size) {
    if (token() == token_t::end) return "";

    auto _str = str();
    if (_str.size() == 1) return _str;

    std::get<1>(stack_.back()) = _str.substr(0, size);
    _str = _str.substr(size);

    stack_.emplace_back(std::make_tuple(token(), _str));

    return str();
}
}  // namespace ts