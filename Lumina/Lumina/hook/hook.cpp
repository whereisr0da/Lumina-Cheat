#include "hook.h"
#include "../sdk/interfaces.h"
#include "../common/common.h"

/*
typedef MDLHandle_t(__thiscall* iFindMdl)(void*, char*);

void __fastcall findMdl(void* _this, void* _edx, char* FilePath) {

	auto returnCall = reinterpret_cast<iFindMdl>(hook::cacheMdlHook.get_original(10));

	common::pf(XorStr("findMdl() : OK %s"), FilePath);

	returnCall(interfaces::mdlCache, FilePath);
}*/

namespace hook {

	vmt viewRenderHook;
	vmt renderViewHook;
	vmt modelRenderHook;
	vmt clientHook;
	vmt surfaceHook;
	vmt panelHook;
	vmt soundSystemHook;
	vmt findMaterialHook;
	vmt cacheMdlHook;
	vmt clientModeHook;
	vmt engineSound;
	vmt direct3d;
	vmt bspQuery;
	vmt fileSystemHook;
	vmt eventManagerHook;

	void isValid(bool var, std::string name) {

		VMProtectBeginMutation("hook::isValid");

		if (var)
		{
#ifdef _DEBUG
			common::pf(XorStr("hook::isValid : %s.setup done"), name.c_str());
#endif 
		}
		else
		{
#ifdef _DEBUG
			common::pf(XorStr("hook::isValid : %s.setup fail"), name.c_str());
#endif 
			common::exit();
		}

		VMProtectEnd();
	}

	void shutdown() {

		VMProtectBeginMutation("hook::shutdown");

		panelHook.release();
		clientHook.release();
		surfaceHook.release();
		modelRenderHook.release();
		fileSystemHook.release();
		clientModeHook.release();
		cacheMdlHook.release();

		VMProtectEnd();
	}

	int init() {

		VMProtectBeginMutation("hook::init");

		HOOK_SETUP(panelHook, "vgui2.dll", interfaces::panel, pad0)
		HOOK_SETUP(clientHook, "client.dll", interfaces::baseClientDll, pad1)
		HOOK_SETUP(surfaceHook, "vguimatsurface.dll", interfaces::surface, pad2)
		HOOK_SETUP(modelRenderHook, "engine.dll", interfaces::modelRender, pad3)
		HOOK_SETUP(fileSystemHook, "engine.dll", interfaces::fileSystem, pad4)
		HOOK_SETUP(clientModeHook, "client.dll", interfaces::clientMode, pad5)
		//HOOK_SETUP(eventManagerHook, "engine.dll", interfaces::eventManager, pad6)
		HOOK_SETUP(cacheMdlHook, "datacache.dll", interfaces::mdlCache, pad7)

		panelHook.hook_index(41, reinterpret_cast<void*>(paintTraverseHook));

		clientHook.hook_index(4, reinterpret_cast<void*>(shutdownHook));
		clientHook.hook_index(6, reinterpret_cast<void*>(levelInitPostEntityHook));
		clientHook.hook_index(37, reinterpret_cast<void*>(frameStageNotifyHook));

		surfaceHook.hook_index(67, reinterpret_cast<void*>(lockCursorHook));

		modelRenderHook.hook_index(21, reinterpret_cast<void*>(drawModelExecuteHook));

		fileSystemHook.hook_index(101, reinterpret_cast<void*>(hkGetUnverifiedFileHashes));
		fileSystemHook.hook_index(129, reinterpret_cast<void*>(hkAllowLooseFileLoads));
		fileSystemHook.hook_index(128, reinterpret_cast<void*>(hkCanLoadThirdPartyFiles));

		clientModeHook.hook_index(44, reinterpret_cast<void*>(doPostScreenEffectHook));
		clientModeHook.hook_index(24, reinterpret_cast<void*>(createMoveHook));
		clientModeHook.hook_index(17, reinterpret_cast<void*>(shouldDrawFogHook));

		//cacheMdlHook.hook_index(10, reinterpret_cast<void*>(findMdl));

		//eventManagerHook.hook_index(8, reinterpret_cast<void*>(fireEventClientSideHook));

		VMProtectEnd();

		return 0;
	}
}
