#include <translator.h>
#include <exception>
#include <sstream>
#include "gfm/module.h"
#include "html/module.h"

namespace ts {
static std::shared_ptr<IRender>* defaultRender{nullptr};

std::shared_ptr<IParser> make_parser(std::string what) {
    if (gfm::match(what) && gfm::has_parser()) return gfm::make_parser();
    if (html::match(what) && html::has_parser()) return html::make_parser();

    throw std::runtime_error("make parser error");
}

std::shared_ptr<IRender> make_render(std::string what) {
    if (gfm::match(what) && gfm::has_render()) return gfm::make_render();
    if (html::match(what) && html::has_render()) return html::make_render();

    throw std::runtime_error("make render error");
}

void set_default_render(std::shared_ptr<IRender> render) {
    if (render != nullptr) defaultRender = &render;
}

std::ostream& operator<<(std::ostream& out, AstNode node) {
    if (defaultRender != nullptr) out << (*defaultRender)->render(node);
    return out;
}

std::istream& operator>>(std::istream& in, std::shared_ptr<IParser> parser) {
    if (parser != nullptr) parser->from(in);
    return in;
}

std::ostream& operator<<(std::ostream& out, std::shared_ptr<IParser> parser) {
    if (parser != nullptr) return out << parser->document();

    return out;
}
}