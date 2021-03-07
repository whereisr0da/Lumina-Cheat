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

#define CHAMS(config, vector, info, matrix) if (config.enable && vector) { \
		drawMaterial(&(config), info, matrix); \
		drawOriginal = false; \
	} \

#define CHAMS_ELSE(config, vector, info, matrix) else if (config.enable && vector) { \
		drawMaterial(&(config), info, matrix); \
		drawOriginal = false; \
	} \

namespace chams {

	void init();

	bool drawModelExecute(void* context, void* state, const ModelRenderInfo_t& renderInfo, void* matrix, const char* modelName, bool arms, bool sleeve);

	void drawMaterial(chams_t* chams, const ModelRenderInfo_t& renderInfo, void* matrix);

	extern const char* materialsNames[];
	extern int materialSize;
}

#endif // !chams_h