#pragma once
#include <istream>
#include <string>
#include <tuple>

namespace ts {
enum class token_t : char { blank, word, punctation, endl, end };

std::tuple<token_t, std::string> read_token(std::istream &in);
}