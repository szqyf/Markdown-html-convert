#include <common.h>

namespace md {
std::shared_ptr<Parser> make_parser(std::string what) { return nullptr; }
std::shared_ptr<Render> make_render(std::string what) { return nullptr; }
std::shared_ptr<Token> make_root_token() { return Token::make_root(); }
}