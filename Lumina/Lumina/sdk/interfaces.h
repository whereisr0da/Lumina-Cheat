#ifndef interfaces_h

#define interfaces_h

#include "../common/includes.h"

#define RESOLVE_MODULE(NAME, VAR) VAR = (HMODULE)LI_MODULE(NAME).cached(); \
	isValid(VAR, StringHeavy(NAME)); \

#define RESOLVE_INTERFACE(VAR, NAME, MODULE, TYPE) VAR = reinterpret_cast<TYPE*>(getInterfaceAddress(MODULE, HASH(NAME))); \
	isValid(VAR, StringHeavy(NAME)); \

#define RESOLVE_PATTERN(VAR, CAST, MODULE, _PATTERN, PADDING) VAR = CAST(patternScan(MODULE, StringHeavy(_PATTERN)) + PADDING); \
	isValid(VAR, StringHeavy(_PATTERN)); \

#define RESOLVE_EXPORT(VAR, NAME, NAME_STR, MODULE, CAST) void(*NAME); \
	VAR = (CAST)(LI_FN(NAME).in(MODULE));\
	isValid(VAR, StringHeavy(NAME_STR)); \

class ClientMode {};

struct InterfaceNode
{
	void* (*Interface)(); //0x0000
	char* InterfaceName; //0x0004 
	InterfaceNode* NextInterface; //0x0008 
};

class CHudChat
{
public:
	enum ChatFilters
	{
		CHAT_FILTER_NONE = 0,
		CHAT_FILTER_JOINLEAVE = 0x000001,
		CHAT_FILTER_NAMECHANGE = 0x000002,
		CHAT_FILTER_PUBLICCHAT = 0x000004,
		CHAT_FILTER_SERVERMSG = 0x000008,
		CHAT_FILTER_TEAMCHANGE = 0x000010,

		//=============================================================================
		// HPE_BEGIN:
		// [tj]Added a filter for achievement announce
		//=============================================================================

		CHAT_FILTER_ACHIEVEMENT = 0x000020,

		//=============================================================================
		// HPE_END
		//=============================================================================
	};

	void ChatPrintf(int iPlayerIndex, int iFilter, const char* fmt, ...)
	{
		using original_fn = void(__cdecl*)(void*, int, int, const char*, ...);
		return (*(original_fn**)this)[27](this, iPlayerIndex, iFilter, fmt);
	}
};


enum InvalidatePhysicsBits_t : int {
	POSITION_CHANGED = 0x1,
	ANGLES_CHANGED = 0x2,
	VELOCITY_CHANGED = 0x4,
	ANIMATION_CHANGED = 0x8,
	BOUNDS_CHANGED = 0x10,
	SEQUENCE_CHANGED = 0x20
};

namespace interfaces {

	using invalidatePhysicsRecursiveFn = void(__thiscall*)(void*, InvalidatePhysicsBits_t);
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
	extern invalidatePhysicsRecursiveFn invalidatePhysicsRecursive;
	extern ClientMode* clientMode;
	extern getSequenceActivityFn getSequenceActivity;
	extern CNetworkStringTableContainer* clientStringTableContainer;
	extern ISteamGameServer* steamGameServer;
	extern IStudioRender* studioRender;
	extern i_client_state* clientState;
	extern CHudChat* hudChat;

	void init();
	void* getExport(const char* module_name, const char* export_name);
	void resolveModules();
	void fromName();
	void fromPattern();
	void erase();
	void isValid(void* var, const char* name);
	//void* getInterface(HMODULE module, const char* name);
	void* getInterfaceAddress(HMODULE hModule, hash32_t fnvInterface);
	std::vector<int> patternToByte(const char* pattern);
	std::uint8_t* patternScan(void* module, const char* signature);
	void setupSteamInterfaces();
	void* getExport(HMODULE module, const char* export_name);

	template<class T>
	static T* FindHudElement(const char* name);
}

#endif