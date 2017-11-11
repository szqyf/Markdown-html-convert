#include <document.h>
#include <rules.h>
#include <token.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace ts;
namespace gfm {
const p_ast_t Document::from(std::istream &in) {
    document_->clear();

    bool fol = true;
    auto paragraph = document_->add("p");

    Token reader{in, [](token_t &token, std::string &str) {
                     if (token == token_t::blank) {
                         while (true) {
                             auto pos = std::string::npos;
                             if ((pos = str.find("\t")) != std::string::npos)
                                 str.replace(pos, 4, "    ");
                             else
                                 break;
                         }
                     }
                 }};

    while (reader.read()) {
        token_t token = reader.token();
        std::string buf = reader.str();

        if (token == token_t::blank) {
            if (fol && buf.size() < 4) {
                fol = true;
                continue;
            }
        }

        if (token == token_t::endl &&
            std::count(buf.begin(), buf.end(), '\n') > 2) {
            paragraph = document_->add("p");
            fol = true;
            continue;
        }

        for (auto &rule : rules) {
            if (rule->matched(fol, reader)) {
                reader.push_env();
                auto nodes = paragraph.children();
                if (!rule->to_ast(reader, nodes)) {
                    reader.pop_env();
                    continue;
                } else {
                    reader.clear_env();
                    reader.skip(-1);
                    break;
                }
            }
        }

        fol = reader.token() == token_t::endl;
    }

    return document_;
}

const p_ast_t Document::parse_line_from(std::istream &in) { return document_; }

const p_ast_t Document::document() const { return document_; }

Document::Document() {
    document_ = std::make_shared<Ast>();
    // if (node == nullptr) document_ = node;
}
}  // namespace gfm