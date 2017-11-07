#include <token.h>
#include <cctype>
#include <functional>
#include <vector>

namespace ts {
using read_t = std::function<bool(char, char)>;

std::vector<read_t> readers{
    [](char c, char p) { return c > 0 && std::isblank(c); },
    [](char c, char p) { return c < 0 || std::isalnum(c); },
    [](char c, char p) { return c > 0 && std::ispunct(c) && (c == p || p == 0); },
    [](char c, char p) { return c > 0 && std::isspace(c) && !std::isblank(c); }};

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
}