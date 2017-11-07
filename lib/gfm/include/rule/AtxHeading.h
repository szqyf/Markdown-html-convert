#include <rule.h>

namespace gfm {
namespace rule {
class AtxHeading : public simple {
   public:
    const std::string tag() const override { return "h"; }
    // bool to_ast(std::istream &in, ts::p_ast_t &parent) override { return true; }
    const std::string from_ast(ts::p_ast_t p) const override { return ""; }

   public:
    AtxHeading() {
        start_at_beginl_ = true;
        stop_at_endl_ = true;
        start_ = [](std::string s) { return s.front() == '#' && s.size() <= 6; };
        end_ = [](std::string s) { return true; };
    }
};
}
}