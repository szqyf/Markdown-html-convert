#include <document.h>
#include <rules.h>
#include <token.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace ts;
namespace gfm {
const AstNode &Document::from(std::istream &in) {
    document_.children()->clear();

    bool fol = true;
    auto nodes = document_;

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
            nodes = document_.children()->add("p");
            fol = true;
            continue;
        }

        for (auto &rule : rules) {
            if (rule->matched(fol, reader)) {
                ts::AstNode node{rule->tag()};

                if (rule->need_paragrah() && nodes.tag() != "p")
                    nodes = document_.children()->add("p");

                reader.push_env();
                if (!rule->parse(reader, nodes, node)) {
                    reader.pop_env();
                    continue;
                } else {
                    nodes.children()->add(node);
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

const AstNode &Document::parse_line_from(std::istream &in) { return document_; }

const AstNode &Document::document() const { return document_; }

Document::Document() {
    // if (node == nullptr) document_ = node;
}
}  // namespace gfm