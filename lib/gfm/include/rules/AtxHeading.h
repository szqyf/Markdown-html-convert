#include <rule.h>

namespace gfm {
class AtxHeading : public ts::Simple {
   public:
    const std::string tag() const override { return "h"; }
    ts::p_ast_t to_ast(std::string buf, std::istream &in,
                       ts::p_ast_t &parent) override {
        return parent;
    }
    std::string from_ast(ts::p_ast_t p) override { return ""; }

   public:
    AtxHeading() {
        must_fol_ = true;
        start_ = [](std::string s) { return s.front() == '#'; };
        end_ = [](std::string s) { return true; };
    }
};
}