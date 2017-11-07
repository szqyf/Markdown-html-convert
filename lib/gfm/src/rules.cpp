#include <rules.h>

namespace gfm { 
	std::vector<std::shared_ptr<ts::IRule>> rules {
		std::make_shared<rule::AtxHeading>(),
		std::make_shared<rule::text>(),
	};
}