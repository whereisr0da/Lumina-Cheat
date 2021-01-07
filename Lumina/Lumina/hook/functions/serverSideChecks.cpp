#include "serverSideChecks.h"

#include "../hook.h"

int __stdcall hkGetUnverifiedFileHashes(void* _this, void* someclass, int nMaxFiles)
{
	return 0;
}

int __fastcall hkCanLoadThirdPartyFiles(void* _this)
{
	return 1;
}

void __fastcall hkAllowLooseFileLoads(void* ecx, void* edx, bool allow)
{
	VMProtectBeginMutation("hkAllowLooseFileLoads");

	auto returnCall = reinterpret_cast<hkAllowLooseFileLoads_fn>(hook::fileSystemHook.get_original(129));

	returnCall(ecx, edx, true);

	VMProtectEnd();
}