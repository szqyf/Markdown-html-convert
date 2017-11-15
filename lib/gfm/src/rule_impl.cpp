#include <rule/AtxHeading.h>
#include <rule/Codeblock.h>
#include <rule/Img.h>
#include <rule/Link.h>
#include <rule/Paragraph.h>
#include <utils.h>
#include <string>

namespace gfm {
namespace rule {
ts::result_t AtxHeading::parse(ts::Token &in, ts::AstNode &parent) const {
    // node.extends("level", std::to_string(in.str().size()));
    auto str = in.str();
    ts::result_t r = ts::result_t::failure;

    in.read();
    if (!in.all_space())
        in.unread();
    else if (in.token() == ts::token_t::endl) {
        in.unread();
        parent.children(tag(), {{"level", std::to_string(str.size())}});
        return ts::result_t::ok;
    } else {
        ts::AstNode node{
            &parent, tag(), {{"level", std::to_string(str.size())}}};
        while (in.read()) {
            r = gfm::parse(false, in, node);

            if (r == ts::result_t::failure) {
                if (in.token() == ts::token_t::blank) {
                    in.push_env();
                    in.read();
                    if (in.token() == ts::token_t::punctation &&
                        in.str().front() == '#') {
                        in.read();
                        if (in.token() == ts::token_t::endl) {
                            r = ts::result_t::ok;
                            in.clean_env();
                            break;
                        } else
                            in.pop_env();
                    } else
                        in.pop_env();
                }
                node.children("text", in.str());
            } else if (r == ts::result_t::jumpout)
                break;

            if (in.token() == ts::token_t::endl) break;
        }

        parent.children()->emplace_back(node);
    }
    return r;
}

ts::result_t Codeblock::parse(ts::Token &in, ts::AstNode &parent) const {
    ts::result_t r = ts::result_t::failure;
    ts::AstNode node{&parent, tag()};

    in.read();
    if (in.token() == ts::token_t::word) {
        auto lang = in.str();
        in.read();
        if (in.token() == ts::token_t::endl)
            node.extends("lang", lang);
        else if (in.token() == ts::token_t::punctation &&
                 in.str().front() == '`' && in.str().size() >= 3) {
            node.children("text", lang);
            in.unread();
            parent.children()->emplace_back(node);

            return ts::result_t::ok;
        }
    }

    in.enable_escaped(false);
    std::string code{""};

    while (in.read()) {
        if (in.token() == ts::token_t::endl) {
            in.push_env();
            in.read();
            if (in.token() == ts::token_t::blank)
                in.read();
            if (in.token() == ts::token_t::punctation &&
                in.str().front() == '`' && in.str().size() >= 3)
                break;
            in.pop_env();
        }

        code += in.str();
    }

    node.children("text", code);
    parent.children()->emplace_back(node);
    in.enable_escaped(true);

    return ts::result_t::ok;
}

ts::result_t Paragraph::parse(ts::Token &in, ts::AstNode &parent) const {
    ts::AstNode node{&parent, tag()};
    ts::result_t r = ts::result_t::ok;
    bool fol = true;

    while (true) {
        r = gfm::parse(fol, in, node, true);

        if (r == ts::result_t::failure)
            node.children("text", in.str());
        else if (r == ts::result_t::jumpout)
            break;

        fol = (r == ts::result_t::skip
                   ? fol
                   : (in.token() != ts::token_t::blank && node.size() == 0) ||
                         in.token() == ts::token_t::endl);

        if (!in.read()) break;
        if (in.token() == ts::token_t::endl && in.str().size() >= 2) break;
    }

    if (node.size() != 0) parent.children()->emplace_back(node);
    return ts::result_t::ok;
}

ts::result_t Link::parse(ts::Token &in, ts::AstNode &parent) const {
    std::string alt, href, title;
    bool is_ref;

    if (!parse_link(in, alt, href, title, is_ref)) return ts::result_t::failure;

    parent
        .children(tag(), {{"href", href},
                          {"title", title},
                          {"is_ref", is_ref ? "true" : "false"}})
        .children("text", alt);

    return ts::result_t::ok;
}

ts::result_t Img::parse(ts::Token &in, ts::AstNode &parent) const {
    in.read();

    std::string alt, href, title;
    bool is_ref;

    if (!parse_link(in, alt, href, title, is_ref)) return ts::result_t::failure;

    parent.children(tag(), {{"alt", alt},
                            {"src", href},
                            {"title", title},
                            {"is_ref", is_ref ? "true" : "false"}});

    return ts::result_t::ok;
}
}  // namespace rule
}  // namespace gfm