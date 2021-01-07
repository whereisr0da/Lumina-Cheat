#ifndef serverSideChecks_h

#define serverSideChecks_h

using hkAllowLooseFileLoads_fn = void(__fastcall*)(void*, void*, bool);

void __fastcall hkAllowLooseFileLoads(void* ecx, void* edx, bool allow);

int __stdcall hkGetUnverifiedFileHashes(void* _this, void* someclass, int nMaxFiles);

int __fastcall hkCanLoadThirdPartyFiles(void* _this);

#endif // !serverSideChecks_h
