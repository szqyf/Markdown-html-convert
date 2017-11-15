#include <tools.h>

using namespace ts;
namespace html
{
std::string encodeString(const std::string &src, int encodingFlags)
{

    bool amps = (encodingFlags & cAmps) != 0,
         doubleAmps = (encodingFlags & cDoubleAmps) != 0,
         angleBrackets = (encodingFlags & cAngles) != 0,
         quotes = (encodingFlags & cQuotes) != 0;
    std::string tgt;

    for (std::string::const_iterator i = src.begin(), ie = src.end(); i != ie; ++i)
    {
        if (*i == '&' && amps)
        {
            static const std::regex cIgnore("^(&amp;)|(&#[0-9]{1,3};)|(&#[xX][0-9a-fA-F]{1,2};)");
            if (std::regex_search(i, ie, cIgnore))
            {
                tgt.push_back(*i);
            }
            else
            {
                tgt += "&amp;";
            }
        }
        else if (*i == '&' && doubleAmps)
            tgt += "&amp;";
        else if (*i == '<' && angleBrackets)
            tgt += "&lt;";
        else if (*i == '>' && angleBrackets)
            tgt += "&gt;";
        else if (*i == '\"' && quotes)
            tgt += "&quot;";
        else
            tgt.push_back(*i);
    }

    return tgt;
}
} // namespace gfm