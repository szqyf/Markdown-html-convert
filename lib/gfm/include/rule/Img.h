#pragma once
#include <rule.h>

namespace gfm {
namespace rule {
class Img : public ts::IParserRule {
   public:
    std::string tag() const override { return "img"; }

    bool need_paragrah() const override { return true; }

    bool matched(bool beginl, const ts::Token &in) const override {
        return in.str() == "!";
    }

    bool parse(ts::Token &in, const ts::AstNode &p,
               ts::AstNode &node) const override {
        in.read();
        if (in.str() != "[") return false;

        {
            std::string alt = "";
            while (in.read() && in.str() != "]") {  //获取alt
                if (in.str() == "\\") {             //转义
                    in.read();
                    alt += in.str();
                } else
                    alt += in.str();
            }
            node.extends("alt", alt);
        }

        in.read();
        if (in.str() != "[" || in.str() != "(") return false;

        {
            std::string src = "";
            if (in.str() == "(") {  //获取src
                while (in.read() && in.str() != ")") src += in.str();
            }
        }

        return true;
    }
};
}  // namespace rule
}  // namespace gfm