#ifndef lockCursor_h

#define lockCursor_h

#include "../../common/includes.h"

using lockCursorFn = void(__thiscall*)(void*);

void __stdcall lockCursorHook();

#endif