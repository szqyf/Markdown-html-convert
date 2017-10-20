#pragma once

#include "noncopyable.h"
#include <istream>
#include <memory>
#include <vector>

namespace md {
class Token;
class Syntax : private noncopyable {
  public:
    bool matched(std::string buf);
    std::vector<std::shared_ptr<Token>>
    get_tokens(const std::shared_ptr<Token> parent, std::string buf,
               std::istream &stream);

  protected:
    std::vector<std::string> startsWith_;
    std::vector<std::string> endsWith_;

  public:
    virtual ~Syntax(){};
};
}