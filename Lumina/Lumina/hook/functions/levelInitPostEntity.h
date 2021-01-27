#ifndef levelInitPostEntity_h

#define levelInitPostEntity_h

using levelInitPostEntityFn = void(__thiscall*)(void*);

void __fastcall levelInitPostEntityHook(void* ecx, void* edx);

#endif // !levelInitPostEntity_h
