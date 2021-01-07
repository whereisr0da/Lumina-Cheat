#include "doPostScreenEffects.h"

#include "../hook.h"
#include "../../sdk/interfaces.h"
#include "../../features/visuals/glow.h"
#include "../../common/common.h"

int __stdcall doPostScreenEffectHook(int value) {

	auto returnCall = reinterpret_cast<doPostScreenEffectFn>(hook::clientModeHook.get_original(44));

	VMProtectBeginMutation("doPostScreenEffectHook");

	if (game::isEnvironmentValid() && !common::unload)
	{
		glow::execute();
	}

	VMProtectEnd();

	return returnCall(interfaces::clientMode, value);
}