#include <rule.h>

namespace gfm {
namespace rule {
class text : public ts::IParserRule {
   public:
    std::string tag() const override { return "text"; }
    bool need_paragrah() const override { return true; }
    bool matched(bool beginl, const ts::Token &in) const override {
        return true;
    }
    bool parse(ts::Token &in, const ts::AstNode &parent,
               ts::AstNode &node) const override {
        if (in.str() == "\\") {  //转义
            in.read();
            auto token = in.token();

            if (token == ts::token_t::word || token == ts::token_t::punctation)
                node.extends("text", in.str());
            else {
                node.extends("text", "\\");
                in.skip(-1);
            }
        } else
            node.extends("text", in.str());

        in.read();

        return true;
    }
};
}  // namespace rule
}  // namespace gfm