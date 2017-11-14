#include <rule/AtxHeading.h>
#include <rule/Img.h>
#include <rule/Link.h>
#include <rule/Paragraph.h>
#include <utils.h>
#include <string>

namespace gfm {
namespace rule {
bool AtxHeading::parse(ts::Token &in, ts::AstNode &parent) const {
    // node.extends("level", std::to_string(in.str().size()));
    ts::AstNode node{tag(), {{"level", std::to_string(in.str().size())}}};

    in.read();
    if (!in.all_space()) return false;
    if (in.token() == ts::token_t::endl) {
        in.unread();
        parent.children()->add(node);
        return true;
    }

    return false;
}

bool Paragraph::parse(ts::Token &in, ts::AstNode &parent) const {
    ts::AstNode node{tag()};
    bool r = true;

    do {
        r = gfm::parse(true, in, node, true);

        if (!r) break;
    } while (!(in.token() == ts::token_t::endl && in.str().size() >= 2));

    if (node.children()->size() != 0) parent.children()->add(node);
    return r;
}

bool Link::parse(ts::Token &in, ts::AstNode &parent) const {
    std::string alt, href, title;
    bool is_ref;

    if (!parse_link(in, alt, href, title, is_ref)) return false;

    parent
        .children(tag(), {{"href", href},
                          {"title", title},
                          {"is_ref", is_ref ? "true" : "false"}})
        .children("text", alt);

    return true;
}

bool Img::parse(ts::Token &in, ts::AstNode &parent) const {
    in.read();

    std::string alt, href, title;
    bool is_ref;

    if (!parse_link(in, alt, href, title, is_ref)) return false;

    parent.children(tag(), {{"alt", alt},
                            {"src", href},
                            {"title", title},
                            {"is_ref", is_ref ? "true" : "false"}});

    return true;
}
}  // namespace rule
}  // namespace gfm