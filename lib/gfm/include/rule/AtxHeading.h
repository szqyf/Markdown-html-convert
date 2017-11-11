#include <rule.h>

namespace gfm {
namespace rule {
class AtxHeading : public simple {
   protected:
    bool start(const ts::Token& token) const override {
        return token.str().front() == '#' && token.str().size() <= 6;
    }

    bool end(const ts::Token& token) const override { return true; }

   public:
    const std::string tag() const override { return "h"; }

   public:
    AtxHeading() {
        start_at_beginl_ = true;
        stop_at_endl_ = true;
    }
};
}  // namespace rule
}  // namespace gfm