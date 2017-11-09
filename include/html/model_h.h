#pragma once

#include <render.h>
#include <memory>
#include <string>
#include "../../lib/html/include/document_h.h"

namespace html {

inline bool has_render() { return true; }

inline std::shared_ptr<ts::IRender> make_render() { 
    return std::make_shared<Document_h>();
}
}