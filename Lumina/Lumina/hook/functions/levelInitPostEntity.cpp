#include "../../common/includes.h"

#include "../../features/visuals/world.h"
#include "../../sdk/interfaces.h"

void __fastcall levelInitPostEntityHook(void* ecx, void* edx) {

	VMProtectBeginMutation("levelInitPostEntityHook");

	auto returnCall = reinterpret_cast<levelInitPostEntityFn>(hook::clientHook.get_original(6));

	returnCall(ecx);

	world::worldModulation();
	world::changeWorldSky();

	VMProtectEnd();
}