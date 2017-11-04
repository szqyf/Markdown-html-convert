#include <utils.h>
#include <cctype>
#include <functional>
#include <vector>

namespace gfm {
using read_t = std::function<bool(char, char)>;

std::vector<read_t> readers{
    [](char c, char p) { return std::isblank(c); },
    [](char c, char p) { return std::isalnum(c) || c < 0; },
    [](char c, char p) { return std::ispunct(c) && (c == p || p == 0); },
    [](char c, char p) { return std::isspace(c) && !std::isblank(c); }};

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