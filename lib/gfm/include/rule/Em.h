#include "../rules.h"

namespace gfm {
namespace rule {
class Em : public core {
   public:
    std::string tag() const override { return "em"; }
    paragraph_t paragraph_type() const { return paragraph_t::in_paragraph; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return in.str() == "*" || in.str() == "_";
    }
    bool parse(ts::Token &in, ts::AstNode &parent) const override {
        return true;
    }
};
}  // namespace rule
}  // namespace gfm