#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
enum class paragraph_t { new_paragraph, paragraph, anyway };

class core : public ts::IParserRule {
   public:
    virtual paragraph_t paragraph_type() const = 0;
};
}  // namespace rule
}  // namespace gfm