#pragma once

#include <memory>
#include <string>
#include "tag.h"

namespace ts {
class IRender {
   public:
    virtual std::string render(const TagPtr &root) = 0;

   public:
    virtual ~IRender() {}
};
}