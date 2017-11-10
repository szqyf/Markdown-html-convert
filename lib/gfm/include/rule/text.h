#include <rule.h>

namespace gfm {
namespace rule {
class text : public simple {
   protected:
    bool start(const ts::Token& token) const override { return true; }
    bool end(const ts::Token& token) const override { return true; }

   public:
    const std::string tag() const override { return "text"; }

   public:
    text() {
        start_at_beginl_ = false;
        stop_at_endl_ = true;
    }
};
}  // namespace rule
}  // namespace gfm