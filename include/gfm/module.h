#pragma once

#include <parser.h>
#include <memory>
#include <string>
#include "../../lib/gfm/include/gfm_parser.h"

namespace gfm {
inline bool match(std::string name) { return name == "gfm"; }

inline bool has_parser() { return true; }

inline bool has_render() { return false; }

inline std::shared_ptr<ts::IParser> make_parser() {
    return std::make_shared<Parser>();
}

inline std::shared_ptr<ts::IRender> make_render() { return nullptr; }
}