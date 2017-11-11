#pragma once

#include <render.h>

namespace html {
class Render : public ts::IRender {
   public:
    std::string render(const ts::AstNode &root);
};
}  // namespace html