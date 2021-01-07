#ifndef shutdown_h

#define shutdown_h

using shutdownFN = void(__thiscall*)(void*);

void __stdcall shutdownHook(void* _interface);

#endif