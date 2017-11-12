//该文件为自动生成，请勿自行修改
#include <rules.h>
#include <rule/AtxHeading.h>
#include <rule/Br.h>
#include <rule/Em.h>
#include <rule/Img.h>
#include <rule/linktext.h>
#include <rule/text.h>

namespace gfm { 
	std::vector<std::shared_ptr<ts::IParserRule>> rules {
		std::make_shared<rule::AtxHeading>(),
		std::make_shared<rule::Br>(),
		std::make_shared<rule::Em>(),
		std::make_shared<rule::Img>(),
		std::make_shared<rule::linktext>(),
		std::make_shared<rule::text>(),
	};
}