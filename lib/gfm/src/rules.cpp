#include <rules.h>
#include <rule/core/simple.h>
#include <rule/AtxHeading.h>
#include <rule/linktext.h>
#include <rule/text.h>

namespace gfm { 
	std::vector<std::shared_ptr<ts::IRule>> rules {
		std::make_shared<rule::AtxHeading>(),
		std::make_shared<rule::linktext>(),
		std::make_shared<rule::text>(),
	};
}