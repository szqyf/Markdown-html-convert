#include <ast.h>
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace ts {
AstNode &Ast::add(std::string tag, std::string text) {
    emplace_back(tag, text);

    return back();
}

AstNode &Ast::add(std::string tag, extend_t _init) {
    emplace_back(tag, _init);

    return back();
}

p_ast_t Ast::add(extend_t _init) {
    for (auto &el: _init)
        emplace_back(el.first, el.second);
    
    return shared_from_this();
}


p_ast_t Ast::remove(const AstNode &node) {
    nodes_t::iterator found = end();

    for (auto i = begin(); i != end(); ++i)
        if (*i == node) {
            found = i;
            break;
        }

    if (found != end()) erase(found);

    return shared_from_this();
}

p_ast_t Ast::remove(size_t pos) {
    if (pos < size()) erase(begin() + pos);

    return shared_from_this();
}
}