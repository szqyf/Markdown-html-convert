#include <rule.h>

namespace gfm {
namespace rule {
class AtxHeading : public simple {
   protected:
    bool start(std::string str) const override {
        return str.front() == '#' && str.size() <= 6;
    }

    bool end(std::string str) const override { return true; }

   public:
    const std::string tag() const override { return "h"; }

   public:
    AtxHeading() {
        start_at_beginl_ = true;
        stop_at_endl_ = true;
    }
};
}
}