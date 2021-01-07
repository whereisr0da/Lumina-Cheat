#ifndef paintTraverse_h

#define paintTraverse_h

#include "../../common/includes.h"

using paintTraverseFN = void(__thiscall*)(IVPanel*, unsigned int, bool, bool);

void __stdcall paintTraverseHook(unsigned int panel, bool force_repaint, bool allow_force);

#endif