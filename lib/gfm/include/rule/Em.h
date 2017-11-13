#include "../rules.h"

namespace gfm {
namespace rule {
class Em : public ts::IParserRule {
   public:
    std::string tag() const override { return "em"; }

    bool need_paragrah() const override { return true; }

    bool matched(bool beginl, const ts::Token &in) const override {
        return in.str() == "*" || in.str() == "_";
    }

    bool parse(ts::Token &in, const ts::AstNode &p, ts::AstNode &node) const override {
        return true;
    }
};
}  // namespace rule
}  // namespace gfm