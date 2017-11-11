#include <token.h>
#include <cctype>
#include <functional>
#include <tuple>
#include <vector>

namespace ts {
using read_t = std::function<bool(char, char)>;
std::vector<read_t> readers{
    [](char c, char p) { return c > 0 && std::isblank(c); },
    [](char c, char p) { return c < 0 || std::isalnum(c); },
    [](char c, char p) {
        return c > 0 && std::ispunct(c) && (c == p || p == 0);
    },
    [](char c, char p) {
        return c > 0 && std::isspace(c) && !std::isblank(c);
    }};

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
        int i = 0;

        if (!in_.eof()) {
            for (auto& rs : readers) {
                char c, p = 0;
                while (in_.get(c))
                    if (rs(c, p)) {
                        r += (p = c);
                    } else {
                        in_.unget();
                        break;
                    }

                if (!r.empty()) break;

                ++i;
            }
        } else
            i = static_cast<int>(token_t::end);

        token_t tk = static_cast<token_t>(i);

        if (readed_ != nullptr) readed_(tk, r);

        stack_.emplace_back(std::make_tuple(tk, r));
    }
    cur_++;

    return token() != token_t::end;
}

std::tuple<token_t, std::string> read_token(std::istream& in) {
    std::string r;
    int i = 0;

    for (auto& rs : readers) {
        char c, p = 0;
        while (in.get(c))
            if (rs(c, p)) {
                r += (p = c);
            } else {
                in.unget();
                break;
            }

        if (!r.empty()) break;

        ++i;
    }

    return std::make_tuple(static_cast<token_t>(i), r);
}
}  // namespace ts