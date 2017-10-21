#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>
#include "noncopyable.h"
#include "syntax.h"
#include "token.h"

namespace md {
class Parser : private noncopyable {
   public:
    virtual std::shared_ptr<Token> parse(std::string text) = 0;
    virtual std::shared_ptr<Token> parse(const std::istream &stream) = 0;

    virtual std::shared_ptr<Token> parse_line(std::string text,
                                              std::shared_ptr<Token> token) = 0;
    virtual std::shared_ptr<Token> parse_line(const std::istream &stream,
                                              std::shared_ptr<Token> token) = 0;

   public:
    virtual ~Parser() {}
};
}