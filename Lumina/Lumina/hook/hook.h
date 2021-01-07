#pragma once

#ifndef hook_h

#define hook_h

#include "vtableHook.h"

#define HOOK_SETUP(VTABLE, MODULE, INTERFACE_, TMP) bool TMP = VTABLE.setup(INTERFACE_, StringHeavy(MODULE)); \
		isValid(TMP, StringHeavy(MODULE)); \

namespace hook {

	int init();
	void shutdown();
	extern vmt renderViewHook;
	extern vmt viewRenderHook;
	extern vmt modelRenderHook;
	extern vmt clientHook;
	extern vmt surfaceHook;
	extern vmt panelHook;
	extern vmt soundSystemHook;
	extern vmt findMaterialHook;
	extern vmt cacheMdlHook;
	extern vmt clientModeHook;
	extern vmt engineSound;
	extern vmt direct3d;
	extern vmt fileSystemHook;
	extern vmt bspQuery;
	extern vmt eventManagerHook;
}

#endif // !hook_h