#include <rules.h>
#include <utils.h>

using namespace ts;
namespace gfm {
result_t parse(bool beginl, ts::Token &in, ts::AstNode &parent, bool except_p) {
    result_t r = result_t::failure;
    for (auto &rule : rules) {
        if (except_p && rule->tag() == "p") continue;

        if (rule->matched(beginl, in)) {
            if (rule->paragraph_type() == rule::paragraph_t::out_paragraph &&
                except_p) {
                r = result_t::jumpout;
                break;
            }

            in.push_env();

            r = rule->parse(in, parent);

            if (r == result_t::failure)
                in.pop_env();
            else if (r == result_t::jumpout) {
                in.pop_env();
                break;
            } else {
                in.clean_env();
                break;
            }
        }
    }

    return r;
}

bool parse_link(ts::Token &in, std::string &alt, std::string &href,
                std::string &title, bool &is_ref) {
    is_ref = false;
    alt = "";
    href = "";
    title = "";

    if (!in.has_puncation("[")) return false;

    while (in.read() && !in.has_puncation("]"))  // get alt
        alt += in.str();

    in.read();
    if (!in.has_puncation("(") && !in.has_puncation("[")) return false;

    if (in.str() == "(")
        while (in.read() && !in.has_puncation(")")) {
            if (in.token() == token_t::endl)
                return false;
            else if (in.has_puncation("\"")) {
                while (in.read() && !in.has_puncation("\""))
                    if (in.token() == token_t::endl)
                        return false;
                    else
                        title += in.str();
            } else if (in.token() != token_t::blank)
                href += in.str();
        }
    else if (in.str() == "[") {
        is_ref = true;
        while (in.read() && !in.has_puncation("]"))
            if (in.token() == token_t::endl)
                return false;
            else
                href += in.str();
    }

    return true;
}
}  // namespace gfm