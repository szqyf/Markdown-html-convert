#include <rule.h>

namespace gfm {
namespace rule {
class text : public simple {
   public:
    const std::string tag() const { return "text"; }
    const std::string from_ast(ts::p_ast_t p) const override { return ""; }

   public:
    text() {
        start_at_beginl_ = false;
        stop_at_endl_ = true;
        start_ = [](std::string c) { return true; };
        end_ = [](std::string c) { return true; };
    }
};
}
}