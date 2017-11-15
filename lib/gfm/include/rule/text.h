#include <rule.h>
#include <utils.h>

namespace gfm {
namespace rule {
class text : public core {
   public:
    std::string tag() const override { return "text"; }
    paragraph_t paragraph_type() const { return paragraph_t::in_paragraph; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return true;
    }
    ts::result_t parse(ts::Token &in, ts::AstNode &parent) const override {
        parent.children("text", in.str());

        return ts::result_t::ok;
    }
};
}  // namespace rule
}  // namespace gfm