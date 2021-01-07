#ifndef interfaces_h

#define interfaces_h

#include "../common/includes.h"

#define RESOLVE_MODULE(NAME, VAR) VAR = (HMODULE)LI_MODULE(NAME).cached(); \
	isValid(VAR, StringHeavy(NAME)); \

#define RESOLVE_INTERFACE(VAR, NAME, MODULE, TYPE) VAR = reinterpret_cast<TYPE*>(getInterface(MODULE, NAME)); \
	isValid(VAR, StringHeavy(NAME)); \

#define RESOLVE_PATTERN(VAR, CAST, MODULE, _PATTERN, PADDING) VAR = CAST(patternScan(MODULE, StringHeavy(_PATTERN)) + PADDING); \
	isValid(VAR, StringHeavy(_PATTERN)); \

class ClientMode {};

namespace interfaces {

	using forceUpdateFn = void(__cdecl*)();
	using hasC4Fn = bool(__thiscall*)(void*);
	using getSequenceActivityFn = int(__fastcall*)(void*, studiohdr_t*, int);

	extern IBaseClientDll* baseClientDll;
	extern IEngineClient* engineClient;
	extern IVRenderView* renderView;
	extern IClientEntityList* clientEntityList;
	extern IMaterialSystem* materialSystem;
	extern IVModelRender* modelRender;
	extern IVModelInfo* modelInfo;
	extern IVPanel* panel;
	extern IConsole* console;
	extern ISurface* surface;
	extern void* eventManager;
	extern void* inputSys;
	extern void* mdlCache;
	extern void* engineSoundClient;
	extern IGlobalVarsBase* globals;
	extern IDirect3DDevice9* d3dDevice9;
	extern IVDebugOverlay* debugOverlay;
	extern C_CSPlayerResource** playerResource;
	extern void* loadFromBufferMaterial;
	extern void* initKeyValuesMaterial;
	extern ICVar* cvar;
	extern void* voiceRecordStart;
	extern IGameEventManager2* gameEventManager;
	extern void* fileSystem;
	extern void* UCS2ToUTF8;
	extern void* itemSchema;
	extern ILocalize* localize;
	extern forceUpdateFn forceUpdate;
	extern CGlowObjectManager* glowManager;
	extern hasC4Fn hasC4;
	extern ClientMode* clientMode;
	extern getSequenceActivityFn getSequenceActivity;
	extern CNetworkStringTableContainer* clientStringTableContainer;
	extern ISteamGameServer* steamGameServer;
	extern IStudioRender* studioRender;

	void init();
	void* getExport(const char* module_name, const char* export_name);
	void resolveModules();
	void fromName();
	void fromPattern();
	void erase();
	void isValid(void* var, const char* name);
	void* getInterface(HMODULE module, const char* name);
	std::vector<int> patternToByte(const char* pattern);
	std::uint8_t* patternScan(void* module, const char* signature);
	void setupSteamInterfaces();
	void* getExport(HMODULE module, const char* export_name);
}

#endif