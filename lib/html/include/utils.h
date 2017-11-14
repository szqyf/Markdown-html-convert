#pragma once
#include <ast.h>
#include <token.h>
#include <istream>
#include <string>

#include <stack>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/unordered_set.hpp>

namespace html {

enum EncodingFlags { cAmps=0x01, cDoubleAmps=0x02, cAngles=0x04, cQuotes=0x08 }; 
   
std::string encodeString(const std::string& src, int encodingFlags);
}  // namespace gfm