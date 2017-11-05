#include <rules.h>

namespace gfm { 
	std::vector<std::shared_ptr<ts::IRule>> rules {std::make_shared<AtxHeading>(),
	};
}