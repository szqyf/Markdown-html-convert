//该文件为自动生成，请勿自行修改
#include <rules.h>
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
#include <rule/linktext.h>
#include <rule/SetxHeading.h>
#include <rule/Strong.h>
#include <rule/text.h>

namespace gfm { 
	std::vector<std::shared_ptr<rule::core>> rules {
		std::make_shared<rule::AtxHeading>(),
		std::make_shared<rule::Blank>(),
		std::make_shared<rule::Blockquote>(),
		std::make_shared<rule::Br>(),
		std::make_shared<rule::Bullet>(),
		std::make_shared<rule::Codeblock>(),
		std::make_shared<rule::Em>(),
		std::make_shared<rule::HtmlEscape>(),
		std::make_shared<rule::HtmlRaw>(),
		std::make_shared<rule::Img>(),
		std::make_shared<rule::Link>(),
		std::make_shared<rule::linktext>(),
		std::make_shared<rule::SetxHeading>(),
		std::make_shared<rule::Strong>(),
		std::make_shared<rule::text>(),
	};
}