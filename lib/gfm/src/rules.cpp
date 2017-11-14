//该文件为自动生成，请勿自行修改
#include <rule/AtxHeading.h>
#include <rule/Blank.h>
#include <rule/Blockquote.h>
#include <rule/Br.h>
#include <rule/Bullet.h>
#include <rule/Codeblock.h>
#include <rule/Em.h>
#include <rule/HtmlEscape.h>
#include <rule/HtmlRaw.h>
#include <rule/Img.h>
#include <rule/Link.h>
#include <rule/Paragraph.h>
#include <rule/SetxHeading.h>
#include <rule/Strong.h>
#include <rule/linktext.h>
#include <rule/text.h>
#include <rules.h>

using namespace gfm::rule;

namespace gfm {
std::vector<std::shared_ptr<core>> rules{
    std::make_shared<Blank>(),      std::make_shared<Blockquote>(),
    std::make_shared<AtxHeading>(), std::make_shared<SetxHeading>(),
    std::make_shared<Bullet>(),     std::make_shared<Codeblock>(),
    std::make_shared<Paragraph>(),  std::make_shared<Em>(),
    std::make_shared<Strong>(),     std::make_shared<Br>(),
    std::make_shared<HtmlEscape>(), std::make_shared<HtmlRaw>(),
    std::make_shared<Img>(),        std::make_shared<Link>(),
    std::make_shared<linktext>(),   std::make_shared<text>(),
};
}