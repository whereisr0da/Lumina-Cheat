#ifndef createMove_h

#define createMove_h

using createMoveFn = bool(__thiscall*)(void*, float, void*);

bool __stdcall createMoveHook(float smt, void* cmd);

#endif