#include <gfm_parser.h>
#include <rules.h>
#include <token.h>
#include <utils.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace ts;
namespace gfm {
const AstNode &Parser::from(std::istream &in) {
    document_.children()->clear();

    bool fol = true;
    auto &parent = document_;

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
        auto r = parse(fol, reader, document_);

        fol = (r == ts::result_t::skip ? fol
                                       : reader.token() == ts::token_t::endl);
    }
    // token_t token = reader.token();
    // std::string buf = reader.str();

    // if (token == token_t::endl &&
    //     std::count(buf.begin(), buf.end(), '\n') >= 2) {
    //     parent = document_.children("p", "");
    //     fol = true;
    //     continue;
    // }

    // for (auto &rule : rules) {
    //     if (rule->matched(fol, reader)) {
    //         // ts::AstNode node{rule->tag()};

    //         // if (rule->paragraph_type() == rule::paragraph_t::paragraph
    //         &&
    //         //     parent.tag() != "p")
    //         //     parent = document_.children()->add("p");
    //         // else if (rule->paragraph_type() ==
    //         //              rule::paragraph_t::new_paragraph &&
    //         //          parent.tag() == "p") {
    //         //     if (parent.children()->size() == 0)
    //         //         document_.children()->remove(parent);
    //         //     parent = document_;
    //         // }

    //         reader.push_env();
    //         if (!rule->parse(reader, parent)) {
    //             reader.pop_env();
    //             continue;
    //         } else {
    //             // if (!rule->tag().empty())
    //             parent.children()->add(node); break;
    //         }
    //     }
    // }

    // fol = reader.token() == token_t::endl;
    // }

    return document_;
}

const AstNode &Parser::parse_line_from(std::istream &in) { return document_; }

const AstNode &Parser::document() const { return document_; }

Parser::Parser() {
    // if (node == nullptr) document_ = node;
}
}  // namespace gfm