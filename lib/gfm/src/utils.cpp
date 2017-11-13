#include <utils.h>

namespace gfm {
std::string get_text_with_escaped(ts::Token &in) {
    std::string str = in.str();
    if (str == "\\\\")
        str = "\\";
    else if (str == "\\") {  //转义
        in.read();
        auto token = in.token();

        if (token == ts::token_t::word || token == ts::token_t::punctation)
            str = in.trunc(1);
        else
            in.skip(-1);
    }

    return str;
}

}  // namespace gfm