#include "../rules.h"

namespace gfm {
namespace rule {
class Em : public simple {
   protected:
    bool start(const ts::Token& token) const override { return token.str() == "**" || token.str() == "__"; }
    bool end(const ts::Token& token) const override { return true; }

   public:
    std::string tag() const override { return "em"; }

   public:
    Em() {
        start_at_beginl_ = false;
        stop_at_endl_ = true;
        add_start_ = true;
    }
};
}  // namespace rule
}  // namespace gfm