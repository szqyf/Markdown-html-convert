#include <rule.h>

namespace gfm {
namespace rule {
class text : public simple {
   protected:
    bool start(std::string str) const override { return true; }
    bool end(std::string str) const override { return true; }

   public:
    const std::string tag() const override { return "text"; }
    const std::string from_ast(ts::p_ast_t p) const override { return ""; }

   public:
    text() {
        start_at_beginl_ = false;
        stop_at_endl_ = true;
    }
};
}
}