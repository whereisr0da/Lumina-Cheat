#include "common/includes.h"
#include "common/common.h"
#include "common/events.h"
#include "common/input.h"
#include "sdk/interfaces.h"
#include "ui/menu.h"
#include "ui/render.h"
#include "ui/fgui_/render.hpp"
#include "features/visuals/chams.h"
#include "features/misc/voice.h"
#include "features/visuals/skinchanger.h"
#include "features/visuals/animationfix.h"
#include "ui/sound.h"
#include "features/visuals/world.h"

bool CheckGame() {

	VMProtectBeginMutation("CheckGame");

	char fileName[MAX_PATH + 1];

	if (!GetModuleFileName(NULL, fileName, MAX_PATH + 1))
		return FALSE;

	const char* sCsgoCiphered = XorStr("csgo.exe");

	bool result = strstr(fileName, sCsgoCiphered);

	VMProtectEnd();

	return result;
}

DWORD WINAPI Start(LPVOID param) {

	VMProtectBeginMutation("Start");

	common::currentModule = (HMODULE)param;

	if (!CheckGame()) {
		common::exit();
		return FALSE;
	}

#ifdef _DEBUG

	LI_FN(AllocConsole).get()();

	freopen_s((FILE**)stdout, XorStr("CONOUT$"), XorStr("w"), stdout);

	common::ps(XorStr("Lumina build : 0.1.11"));

#endif

#ifdef _DEBUG
	common::ps(XorStr("Start : check if all modules are here"));
#endif

	while (!LI_FN(GetModuleHandleA).get()(XorStr("serverbrowser.dll")))
		Sleep(200);

	interfaces::init();

	chams::init();

	hook::init();

	config::init();

	sound::init();

	world::init();

	events::init();

	input::init();

	skinchanger::init();

	animationfix::init();

	//voice::init();

	render::init();

	zguiInit();

	menu::init();

#ifdef _DEBUG
	common::ps(XorStr("Start : everything done"));
#endif

	while (common::active)
		Sleep(200);

#ifdef _DEBUG
	common::ps(XorStr("Start : exiting the cheat"));
#endif 

	VMProtectEnd();

	return FALSE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {

	VMProtectBeginMutation("DllMain");

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls((HMODULE)hinstDLL);

		HANDLE thread = CreateThread(0, 0, Start, hinstDLL, 0, 0);

		CloseHandle(thread);
	}

	VMProtectEnd();

	return TRUE;
}

// crashhandler.dll exports
// same as the original; probably useless

// NOTE FROM 2020 : produce rare crashes because of g_dwDllEntryThreadId

#define EXPORT __declspec(dllexport)

volatile HMODULE hOriginalCrashHandler = NULL;

volatile PVOID pBreakpad_SetSteamID = NULL;
volatile PVOID pCreateInterface = NULL;
volatile PVOID pg_dwDllEntryThreadId = NULL;

int32_t EXPORT Breakpad_SetSteamID(int32_t arg1, int32_t arg2) {

	/*
	if (!hOriginalCrashHandler) {
		hOriginalCrashHandler = LI_FN(LoadLibraryA).get()(XorStr("crashhandler.dex"));
	}

	if (!pBreakpad_SetSteamID) {
		pBreakpad_SetSteamID = LI_FN(GetProcAddress).get()(hOriginalCrashHandler, XorStr("Breakpad_SetSteamID"));
	}

#ifdef _DEBUG
	common::pf(XorStr("Breakpad_SetSteamID : call to %p"), pBreakpad_SetSteamID);
#endif 

	return ((int32_t(*)(int32_t, int32_t))(pBreakpad_SetSteamID))(arg1, arg2);*/

	return 0;
}

int32_t EXPORT CreateInterface(char* arg1, int32_t* arg2) {

	/*
	if (!hOriginalCrashHandler) {
		hOriginalCrashHandler = LI_FN(LoadLibraryA).get()(XorStr("crashhandler.dex"));
	}

	if (!pCreateInterface) {
		pCreateInterface = LI_FN(GetProcAddress).get()(hOriginalCrashHandler, XorStr("CreateInterface"));
	}

#ifdef _DEBUG
	common::pf(XorStr("CreateInterface : call to %p"), pCreateInterface);
#endif 

	return ((int32_t(*)(char*, int32_t*))(pCreateInterface))(arg1, arg2);

	*/

	return 0;
}

void _declspec(naked) EXPORT g_dwDllEntryThreadId() {
	__asm {
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
	}
}