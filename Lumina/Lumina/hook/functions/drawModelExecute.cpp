#include "drawModelExecute.h"

#include "../hook.h"
#include "../../sdk/interfaces.h"
#include "../../features/visuals/chams.h"
#include "../../common/common.h"

void __stdcall drawModelExecuteHook(void* context, void* state, const ModelRenderInfo_t& renderInfo, void* matrix) {
	
	VMProtectBeginMutation("drawModelExecuteHook");

	bool drawOriginal = true;

	auto returnCall = reinterpret_cast<drawModelExecuteFn>(hook::modelRenderHook.get_original(21));

	bool isEnvironmentValid = game::getLocalPlayer() && game::isEnvironmentValid();

	bool arms = false;
	bool sleeve = false;

	const char* modelName = "";

	// not optimized, but do it once :|
	if (renderInfo.pModel)
	{
		modelName = interfaces::modelInfo->GetModelName(renderInfo.pModel);

		if (modelName) {

			arms = strstr(modelName, XorStr("arms"));
			sleeve = strstr(modelName, XorStr("sleeve"));
		}
	}

	// IsForcedMaterialOverride is to avoid the glow material override
	// interfaces::modelRender->IsForcedMaterialOverride() don't works with patches
	// thx to Osiris
	if(common::unload || (interfaces::studioRender->isForcedMaterialOverride() && !(arms || sleeve)) || !isEnvironmentValid)
		return returnCall(interfaces::modelRender, context, state, renderInfo, matrix);

	drawOriginal = chams::drawModelExecute(context, state, renderInfo, matrix, modelName, arms, sleeve);

	if (drawOriginal)
		returnCall(interfaces::modelRender, context, state, renderInfo, matrix);

	VMProtectEnd();
}