#include <html_render.h>

namespace html {
std::string Render::render(const ts::AstNode &root) {
    std::string html = "";
    for (auto &r : root) {
        if (r.tag() == "text") {
            html += r.extends("text");
        } else {
            html += "<" + r.tag();

            if (r.extends()->size() != 0) {
                auto keys = ts::keys(r.extends_r());
                for (auto &key : keys)
                    html += " " + key + "=\"" + r.extends(key) + "\"";
            }

            html += ">" + render(r) + "</" + r.tag() + ">";
        }
    }
    return html;
}
}  // namespace html