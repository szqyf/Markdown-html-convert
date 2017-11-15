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
    paragraph_t paragraph_type() const { return paragraph_t::anyway; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return beginl && in.token() == ts::token_t::blank;
    }
    ts::result_t parse(ts::Token &in, ts::AstNode &parent) const override {
        auto r = ts::result_t::failure;
        if (parent.tag() == "p") return ts::result_t::ok;
        if (in.str().size() < 4) return ts::result_t::skip;
        in.read();
        if (in.token() == ts::token_t::endl) r = ts::result_t::ok;
        in.unread();

        return r;
    }
};
}  // namespace rule
}  // namespace gfm