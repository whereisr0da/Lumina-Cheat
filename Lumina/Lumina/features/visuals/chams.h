#ifndef chams_h

#define chams_h

#include "../../common/includes.h"
#include "../../sdk/math/Color.h"
#include "../../sdk/structs/IMaterial.h"

struct materialInfo {
	void* ecx;
	void* currentState;
	const ModelRenderInfo_t& mrenderInfo;
	void* currentMatrix;
};

namespace chams {

	void init();

	bool drawModelExecute(void* context, void* state, const ModelRenderInfo_t& renderInfo, void* matrix, const char* modelName, bool arms, bool sleeve);

	void drawMaterial(chams_t* chams, const ModelRenderInfo_t& renderInfo);

	extern const char* materialsNames[];
	extern int materialSize;

	//IMaterial* createMaterial(std::string name, std::string buffer, std::string type);
	//void initKeyValues(KeyValues* kv_, std::string name_);
	//void loadFromBuffer(KeyValues* vk_, std::string name_, std::string buffer_);
}

#endif // !chams_h