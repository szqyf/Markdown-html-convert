#pragma once

#include <istream>
#include <memory>
#include "ast.h"
#include "noncopyable.h"

namespace ts {
class IParser : private noncopyable {
   public:
    virtual const AstNode &from(std::istream &in) = 0;

    virtual const AstNode parse_line_from(std::istream &in) = 0;

    virtual const AstNode document() const = 0;

   public:
    virtual ~IParser() {}

   protected:
    class AstHelper : private noncopyable {
       public:
        AstHelper(AstNode node) : node_(node) {}

        AstHelper(AstHelper &&oth) {
            if (this != &oth) {
                this->node_ = oth.node_;
                oth.node_ = nullptr;
            }
        };
        AstHelper &operator=(AstHelper &&oth);

       public:
        void reset();
        AstHelper push_leaf(std::string tag, std::string text = "");
        AstHelper &set_extendings(std::pair<std::string, std::string> value);
        const AstHelper &parent() const { return *parent_; }

       private:
        AstNode node_;
        AstHelper *parent_;
    };
};
}