#include <rule.h>
#include <utils.h>

namespace gfm {
namespace rule {
/**
 * @brief 处理行首空格的Rule
 *
 */
class Blank : public core {
   public:
    std::string tag() const override { return ""; }
    paragraph_t paragraph_type() const override { return paragraph_t::anyway; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return beginl && in.token() == ts::token_t::blank;
    }
    bool parse(ts::Token &in, const ts::AstNode &parent,
               ts::AstNode &node) const override {
        bool r = false;
        if (parent.tag() == "p") return true;
        if (in.str().size() < 4) return true;
        in.read();
        r = (in.token() == ts::token_t::endl);
        in.unread();

        return r;
    }
};
}  // namespace rule
}  // namespace gfm