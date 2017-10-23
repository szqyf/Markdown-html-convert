#include <translator.h>
#include <exception>
#include <strstream>
#include "gfm/module.h"

namespace ts {
std::shared_ptr<Parser> make_parser(std::string what, const std::string str) {
    return make_parser(what, std::istrstream(str));
}

std::shared_ptr<Parser> make_parser(std::string what, const std::istream &in) {
    if (gfm::match(what)) return gfm::make_parser(in);

    throw std::runtime_error("make parser error");
}

std::shared_ptr<IRender> make_render(std::string what, std::ostream &out) {
    return nullptr;
}
}