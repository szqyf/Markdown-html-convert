#include <rule/AtxHeading.h>
#include <rule/Img.h>
#include <rule/Link.h>
#include <utils.h>
#include <string>

namespace gfm {
namespace rule {
bool AtxHeading::parse(ts::Token &in, const ts::AstNode &parent,
                       ts::AstNode &node) const {
    node.extends("level", std::to_string(in.str().size()));

    in.read();
    if (!in.all_space()) return false;
    if (in.token() == ts::token_t::endl) {
        in.unread();
        return true;
    }
}

bool Link::parse(ts::Token &in, const ts::AstNode &p, ts::AstNode &node) const {
    std::string alt, href, title;
    bool is_ref;

    if (!parse_link(in, alt, href, title, is_ref)) return false;

    node.extends("href", href);
    node.extends("title", title);
    node.children()->add("text", alt);
    node.extends("is_ref", is_ref ? "true" : "false");

    return true;
}

bool Img::parse(ts::Token &in, const ts::AstNode &p, ts::AstNode &node) const {
    in.read();

    std::string alt, href, title;
    bool is_ref;

    if (!parse_link(in, alt, href, title, is_ref)) return false;

    node.extends("alt", alt);
    node.extends("src", href);
    node.extends("title", title);
    node.extends("is_ref", is_ref ? "true" : "false");

    return true;
}
}  // namespace rule
}  // namespace gfm