#include "../common/common.h"
#include "interfaces.h"

namespace interfaces {

	IBaseClientDll* baseClientDll = NULL;
	IEngineClient* engineClient = NULL;
	IVRenderView* renderView = NULL;
	IClientEntityList* clientEntityList = NULL;
	IMaterialSystem* materialSystem = NULL;
	IVModelRender* modelRender = NULL;
	IVModelInfo* modelInfo = NULL;
	IVPanel* panel = NULL;
	IConsole* console = NULL;
	ISurface* surface = NULL;
	void* eventManager = NULL;
	void* inputSys = NULL;
	void* mdlCache = NULL;
	void* engineSoundClient = NULL;
	IVDebugOverlay* debugOverlay = NULL;
	C_CSPlayerResource** playerResource = NULL;
	IGlobalVarsBase* globals = NULL;
	IDirect3DDevice9* d3dDevice9 = NULL;
	void* loadFromBufferMaterial = NULL;
	void* initKeyValuesMaterial = NULL;
	ICVar* cvar = NULL;
	IGameEventManager2* gameEventManager = NULL;
	void* voiceRecordStart = NULL;
	void* fileSystem = NULL;
	void* UCS2ToUTF8 = NULL;
	void* itemSchema = NULL;
	ILocalize* localize = NULL;
	forceUpdateFn forceUpdate = NULL;
	CGlowObjectManager* glowManager = NULL;
	hasC4Fn hasC4 = NULL;
	getSequenceActivityFn getSequenceActivity = NULL;
	ClientMode* clientMode = NULL;
	CNetworkStringTableContainer* clientStringTableContainer = NULL;
	ISteamGameServer* steamGameServer = NULL;
	IStudioRender* studioRender = NULL;
	invalidatePhysicsRecursiveFn invalidatePhysicsRecursive = NULL;

	void init() {

		VMProtectBeginMutation("interfaces::init");

		resolveModules();

		fromName();

		fromPattern();

#ifdef _DEBUG
		common::ps(StringHeavy("interfaces::init : done"));
#endif

		VMProtectEnd();
	}

	void erase() {

		/*
		* can't be used due to mutation
		erase_function((uint8_t*)interfaces::init);
		erase_function((uint8_t*)interfaces::resolveModules);
		erase_function((uint8_t*)interfaces::getInterface);
		erase_function((uint8_t*)interfaces::fromName);
		erase_function((uint8_t*)interfaces::fromPattern);
		erase_function((uint8_t*)interfaces::patternToByte);
		erase_function((uint8_t*)interfaces::patternScan);
		erase_function((uint8_t*)interfaces::isValid);
		*/

#ifdef _DEBUG
		common::ps(StringHeavy("interfaces::erase : done"));
#endif
	}

	void resolveModules()
	{
		VMProtectBeginMutation("interfaces::resolveModules");

		RESOLVE_MODULE("client.dll", common::clientModule)
		RESOLVE_MODULE("engine.dll", common::engineModule)
		RESOLVE_MODULE("materialsystem.dll", common::materialsystemModule)
		RESOLVE_MODULE("vguimatsurface.dll", common::vguimatsurfaceModule)
		RESOLVE_MODULE("vstdlib.dll", common::vstdlibModule)
		RESOLVE_MODULE("soundsystem.dll", common::soundsystemModule)
		RESOLVE_MODULE("vgui2.dll", common::vgui2Module)
		RESOLVE_MODULE("datacache.dll", common::datacacheModule)
		RESOLVE_MODULE("shaderapidx9.dll", common::dx9apiModule)
		RESOLVE_MODULE("inputsystem.dll", common::inputSysModule)
		RESOLVE_MODULE("localize.dll", common::localizeModule)
		RESOLVE_MODULE("steam_api.dll", common::steamApiModule)
		RESOLVE_MODULE("studiorender.dll", common::studiorenderModule)

#ifdef _DEBUG
		common::ps(StringHeavy("interfaces::resolveModules : done"));
#endif

		VMProtectEnd();
	}

	void isValid(void* var, const char* name) {

		VMProtectBeginMutation("interfaces::isValid");

		if (var == NULL) {
#ifdef _DEBUG
			common::pf(StringHeavy("interfaces::isValid : %s fail to load"), name);
#endif
			common::exit(); 
		} 

#ifdef _DEBUG
		else {
			common::pf(StringHeavy("interfaces::isValid : %s loaded at 0x%x"), name, var);
		}
#endif
		VMProtectEnd();
	}

	/*
	void* getInterface(HMODULE module, const char* name)
	{
		VMProtectBeginMutation("interfaces::getInterface");

		using createInterfacePrototype = void*(*)(const char*, int*);

		auto createInterfaceAddress = (createInterfacePrototype)(LI_FN(GetProcAddress).get()(module, StringHeavy("CreateInterface")));

		auto interfaceAddress = createInterfaceAddress(name, nullptr);

		VMProtectEnd();

		return interfaceAddress;
	}

	bool checkPageProtection(HMODULE hModule, LPCVOID iAddress, int protection) {

		MEMORY_BASIC_INFORMATION mbi = { 0 };

		if (VirtualQuery(iAddress, &mbi, sizeof(mbi)) == sizeof(mbi)) 
			return mbi.AllocationBase && mbi.Protect & protection;

		return false;
	}*/

	void* getInterfaceAddress(HMODULE hModule, hash32_t fnvInterface)
	{
		// credits : https://www.unknowncheats.me/forum/counterstrike-global-offensive/165359-easy-createinterface.html

		VMProtectBeginMutation("interfaces::getInterfaceAddress");

		void* pCreateInterface = NULL;

		// resolve the CreateInterface function dynamicaly from exports
		RESOLVE_EXPORT(pCreateInterface, CreateInterface, "CreateInterface*", hModule, void*)

		ULONG ShortJump = (ULONG)pCreateInterface + 5; //magic number shit explained above

		ULONG Jump = (((ULONG)pCreateInterface + 5) + *(ULONG*)ShortJump) + 4;

		InterfaceNode* List = **(InterfaceNode***)(Jump + 6);

		do {
			if (List)
			{
				if (FNV1a::get(List->InterfaceName) == fnvInterface)
					return List->Interface();
			}

		} while (List = List->NextInterface);

		VMProtectEnd();

		return 0;
	}

	void fromName()
	{
		VMProtectBeginMutation("interfaces::fromName");

		RESOLVE_INTERFACE(baseClientDll, ("VClient018"), common::clientModule, IBaseClientDll)
		RESOLVE_INTERFACE(engineClient, ("VEngineClient014"), common::engineModule, IEngineClient)
		RESOLVE_INTERFACE(materialSystem, ("VMaterialSystem080"), common::materialsystemModule, IMaterialSystem)
		RESOLVE_INTERFACE(panel, ("VGUI_Panel009"), common::vgui2Module, IVPanel)
		RESOLVE_INTERFACE(surface, ("VGUI_Surface031"), common::vguimatsurfaceModule, ISurface)
		RESOLVE_INTERFACE(clientEntityList, ("VClientEntityList003"), common::clientModule, IClientEntityList)
		RESOLVE_INTERFACE(debugOverlay, ("VDebugOverlay004"), common::engineModule, IVDebugOverlay)
		RESOLVE_INTERFACE(modelInfo, ("VModelInfoClient004"), common::engineModule, IVModelInfo)
		RESOLVE_INTERFACE(modelRender, ("VEngineModel016"), common::engineModule, IVModelRender)
		RESOLVE_INTERFACE(renderView, ("VEngineRenderView014"), common::engineModule, IVRenderView)
		RESOLVE_INTERFACE(cvar, ("VEngineCvar007"), common::vstdlibModule, ICVar)
		RESOLVE_INTERFACE(gameEventManager, ("GAMEEVENTSMANAGER002"), common::engineModule, IGameEventManager2)
		RESOLVE_INTERFACE(localize, ("Localize_001"), common::localizeModule, ILocalize)
		RESOLVE_INTERFACE(console, ("VEngineCvar007"), common::vstdlibModule, IConsole)
		RESOLVE_INTERFACE(clientStringTableContainer, ("VEngineClientStringTable001"), common::engineModule, CNetworkStringTableContainer)
		RESOLVE_INTERFACE(studioRender, ("VStudioRender026"), common::studiorenderModule, IStudioRender)
		RESOLVE_INTERFACE(mdlCache, ("MDLCache004"), common::datacacheModule, void)

#ifdef _DEBUG
			common::ps(StringHeavy("interfaces::fromName : done"));
#endif
			VMProtectEnd();
	}

	void fromPattern()
	{
		VMProtectBeginMutation("interfaces::fromPattern");

		RESOLVE_PATTERN(d3dDevice9, **(IDirect3DDevice9 ***), common::dx9apiModule, "A1 ? ? ? ? 50 8B 08 FF 51 0C", 1)
		RESOLVE_PATTERN(playerResource, *(C_CSPlayerResource ***), common::clientModule, "A1 ? ? ? ? 57 85 C0 74 08", 1)
		RESOLVE_PATTERN(loadFromBufferMaterial, (void*), common::clientModule, "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04", 0)
		RESOLVE_PATTERN(initKeyValuesMaterial, (void*), common::clientModule, "55 8B EC 51 33 C0 C7 45", 0)
		RESOLVE_PATTERN(voiceRecordStart, (void*), common::engineModule, "55 8B EC 83 EC 0C 83 3D ? ? ? ? ? 56 57", 0)
		RESOLVE_PATTERN(fileSystem, **(void***), common::engineModule, "8B 0D ? ? ? ? 8D 95 ? ? ? ? 6A 00 C6", 2)
		RESOLVE_PATTERN(itemSchema, (void*), common::clientModule, "E8 ? ? ? ? FF 76 0C 8D 48 04 E8", 0)
		RESOLVE_PATTERN(forceUpdate, (forceUpdateFn), common::engineModule, "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85", 0)
		RESOLVE_PATTERN(glowManager, *(CGlowObjectManager**), common::clientModule, "0F 11 05 ? ? ? ? 83 C8 01 C7 05 ? ? ? ? 00 00 00 00", 3)
		RESOLVE_PATTERN(hasC4, hasC4Fn, common::clientModule, "56 8B F1 85 F6 74 31", 0)
		RESOLVE_PATTERN(invalidatePhysicsRecursive, invalidatePhysicsRecursiveFn, common::clientModule, "55 8B EC 83 E4 F8 83 EC 0C 53 8B 5D 08 8B C3 56 83 E0 04", 0)
		RESOLVE_PATTERN(getSequenceActivity, getSequenceActivityFn, common::clientModule, "55 8B EC 53 8B 5D 08 56 8B F1 83", 0)

		// from export 

		RESOLVE_EXPORT(UCS2ToUTF8, V_UCS2ToUTF8, "UCS2ToUTF8*", common::vstdlibModule, int(*)(const wchar_t* ucs2, char* utf8, int len))

		// from offsets

		globals = **reinterpret_cast<IGlobalVarsBase***>((*reinterpret_cast<uintptr_t**>(baseClientDll)[0] + 0x1F));	
		isValid(globals, StringHeavy("**IGlobalVarsBase***"));

		clientMode = **reinterpret_cast<ClientMode***>((*reinterpret_cast<uintptr_t**>(baseClientDll))[10] + 5);
		isValid(clientMode, StringHeavy("**ClientMode***"));

		//setupSteamInterfaces();

		//D3DDevice9 = **(IDirect3DDevice9 ***)(patternScan((HMODULE)dx9api, StringHeavy("A1 ? ? ? ? 50 8B 08 FF 51 0C")) + 1);

#ifdef _DEBUG
		common::ps(StringHeavy("interfaces::fromPattern : done"));
#endif

		VMProtectEnd();
	}

	/*
	ISteamGameServer* BruteInterfaceSteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, ISteamClient* steamClient)
	{
		// thx OneShot

		VMProtectBeginMutation("interfaces::BruteInterfaceSteamGameServer");

		std::string interfaceName = StringHeavy("SteamGameServer");

		char buffer[64];
		int count = 0;
		sprintf(buffer, XorStr("%s%03i"), interfaceName.c_str(), 0);
		auto hInterface = steamClient->GetISteamGameServer(hSteamUser, hSteamPipe, buffer);

		while (count < 200)
		{
			count++;

			if (count == 1000)
				return nullptr;

			sprintf(buffer, XorStr("%s%03i"), interfaceName.c_str(), count);
			hInterface = steamClient->GetISteamGameServer(hSteamUser, hSteamPipe, buffer);

			if (hInterface) {
#ifdef _DEBUG
				common::pf(StringHeavy("interfaces::setupSteamInterfaces : ISteamGameServer is version %03i"), count);
#endif
			}
		}

		VMProtectEnd();

		return hInterface;
	}

	void setupSteamInterfaces() {

		VMProtectBeginMutation("interfaces::setupSteamInterfaces");

		HSteamUser hSteamUser = ((HSteamUser(__cdecl*)(void))(getExport(common::steamApiModule, StringHeavy("SteamAPI_GetHSteamUser"))))();
		isValid((void*)hSteamUser, StringHeavy("hSteamUser"));

		HSteamPipe hSteamPipe = ((HSteamPipe(__cdecl*)(void))(getExport(common::steamApiModule, StringHeavy("SteamAPI_GetHSteamPipe"))))();
		isValid((void*)hSteamPipe, StringHeavy("hSteamPipe"));

		ISteamClient* steamClient = ((ISteamClient*(__cdecl*)(void))(getExport(common::steamApiModule, StringHeavy("SteamClient"))))();
		isValid(steamClient, StringHeavy("ISteamClient*"));

		steamGameServer = steamClient->GetISteamGameServer(hSteamUser, hSteamPipe, StringHeavy("SteamGameServer010"));
		//steamGameServer = BruteInterfaceSteamGameServer(hSteamUser, hSteamPipe, steamClient);
		isValid(steamGameServer, StringHeavy("ISteamGameServer*"));

		VMProtectEnd();
	}

	void* getExport(const char* module_name, const char* export_name) {

		VMProtectBeginMutation("interfaces::getExport");

		HMODULE mod;

		while (!((mod = GetModuleHandleA(module_name))))
			Sleep(100);

		VMProtectEnd();

		return reinterpret_cast<void*>(GetProcAddress(mod, export_name));
	}

	void* getExport(HMODULE module, const char* export_name) {

		VMProtectBeginMutation("interfaces::getExport2");

		void* pFunction = reinterpret_cast<void*>(GetProcAddress(module, export_name));

		VMProtectEnd();

		return pFunction;
	}*/

	std::vector<int> patternToByte(const char* pattern) {

		auto bytes = std::vector<int>{};

		VMProtectBeginMutation("interfaces::patternToByte");

		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}

		VMProtectEnd();

		return bytes;
	}

	std::uint8_t* patternScan(void* module, const char* signature) {

		VMProtectBeginMutation("interfaces::patternScan");

		auto dos_headers = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
		auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>((std::uint8_t*)module + dos_headers->e_lfanew);

		auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
		auto pattern_bytes = patternToByte(signature);
		auto scan_bytes = reinterpret_cast<std::uint8_t*>(module);

		auto s = pattern_bytes.size();
		auto d = pattern_bytes.data();

		for (auto i = 0ul; i < size_of_image - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				if (scan_bytes[i + j] != d[j] && d[j] != -1) {
					found = false;
					break;
				}
			}
			if (found) {
				return &scan_bytes[i];
			}
		}

		VMProtectEnd();

		return nullptr;
	}
}
