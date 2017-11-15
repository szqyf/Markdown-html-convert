#pragma once
#include <ast.h>
#include <token.h>
#include <istream>
#include <string>

#include <stack>
#include <regex>

namespace html {

enum EncodingFlags { cAmps=0x01, cDoubleAmps=0x02, cAngles=0x04, cQuotes=0x08 }; 
   
std::string encodeString(const std::string& src, int encodingFlags);
}  // namespace gfm