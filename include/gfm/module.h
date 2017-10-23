#pragma once

#include <parser.h>
#include <memory>
#include <string>
#include "../../lib/gfm/include/document.h"

namespace gfm {
inline bool match(std::string name) { return true; }
inline std::shared_ptr<ts::Parser> make_parser() {
    return std::make_shared<Document>();
}
}