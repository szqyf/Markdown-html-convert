#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>
#include "noncopyable.h"
#include "syntax.h"
#include "token.h"

namespace ts {
class Parser : private noncopyable {
   public:
    virtual std::unique_ptr<Token> parse(std::string text) = 0;
    virtual std::unique_ptr<Token> parse(const std::istream &stream) = 0;

    virtual std::unique_ptr<Token> parse_line(
        std::string text, const std::unique_ptr<Token> &root) = 0;
    virtual std::unique_ptr<Token> parse_line(
        const std::istream &stream, const std::unique_ptr<Token> &root) = 0;

   public:
    virtual ~Parser() {}
};
}