#include <utils.h>

using namespace ts;
namespace gfm {
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