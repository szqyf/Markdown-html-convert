#pragma once

#include <rule.h>

namespace gfm {
namespace rule {
class linktext : public simple {
    const std::string tag() const override { return "a"; }
    const std::string from_ast(ts::p_ast_t p) const override { return ""; }
};
}
}