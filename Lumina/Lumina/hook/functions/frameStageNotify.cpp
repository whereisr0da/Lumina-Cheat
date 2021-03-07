#include "frameStageNotify.h"
#include "../hook.h"

#include "../../common/includes.h"
#include "../../common/common.h"
#include "../../sdk/interfaces.h"
#include "../../features/visuals/skinchanger.h"
#include "../../features/visuals/visualMisc.h"
#include "../../features/backtrack/backtrack.h"

void __stdcall frameStageNotifyHook(int frameStage) {

	VMProtectBeginMutation("frameStageNotifyHook");

	auto returnCall = reinterpret_cast<frameStageNotifyPrototype>(hook::clientHook.get_original(37));

	if (common::unload || !game::isEnvironmentValid())
		return returnCall(interfaces::modelRender, frameStage);

	static auto backtrack_init = (backtrack::init(), false);

	if (frameStage == FRAME_RENDER_START) {
		visualMisc::drawGrenadePrediction();
		visualMisc::maintainCrosshair();
		visualMisc::optimization();
	}

	else if (frameStage == FRAME_NET_UPDATE_END) {
		backtrack::update();
	}

	// safe call
	returnCall(interfaces::modelRender, frameStage);

	skinchanger::frameStageNotify(frameStage);

	VMProtectEnd();
}