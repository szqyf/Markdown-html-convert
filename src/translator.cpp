#include <translator.h>
#include <exception>
#include "gfm/module.h"

namespace ts {
std::shared_ptr<Parser> make_parser(std::string what) {
    if (gfm::match(what)) return gfm::make_parser();

    throw std::runtime_error("make parser error");
}

std::shared_ptr<IRender> make_render(std::string what) { return nullptr; }
}