#include <rule.h>

namespace gfm {
class AtxHeading : public ts::Simple {
   public:
    const std::string tag() const { return "h"; }
    void read(std::string buf, std::istream &in, ts::p_ast_t &parent) {}

   public:
    AtxHeading() {
        must_fol_ = true;
        start_ = [](std::string s) { return s.front() == '#'; };
        end_ = [](std::string s) { return true; };
    }
};
}