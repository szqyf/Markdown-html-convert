#pragma once

#include <render.h>
#include <memory>
#include <string>
#include "../../lib/html/include/html_render.h"

namespace html {
inline bool match(std::string name) { return name == "html"; }

inline bool has_parser() { return false; }

inline bool has_render() { return true; }

inline std::shared_ptr<ts::IParser> make_parser() { return nullptr; }

inline std::shared_ptr<ts::IRender> make_render() {
    return std::make_shared<Render>();
}
}  // namespace html