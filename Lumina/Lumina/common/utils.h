#ifndef utils_h

#define utils_h

#include "../sdk/math/Vector.h"
#include "../sdk/structs/mystructs.h"
#include "../sdk/structs/Entity.h"

#include <vector>
#include "../sdk/structs/structs.h"

namespace utils
{
	std::vector<paint_kit> getSkinsInfo();
	bool getEntityBox(Entity* ent, box& in);
	bool precacheModel(const char* szModelName);
}


#endif // !utils_h