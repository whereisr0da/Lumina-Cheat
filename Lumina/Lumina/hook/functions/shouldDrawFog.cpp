#include "../../common/includes.h"

bool __fastcall shouldDrawFogHook(void* ecx, void* edx) {
	return !config::cheats.optimization;
}
