#ifndef drawModelExecute_h

#define drawModelExecute_h

#include "../../common/includes.h"

void __stdcall drawModelExecuteHook(void* context, void* state, const ModelRenderInfo_t& renderInfo, void* matrix);

using drawModelExecuteFn = void(__thiscall*)(void*, void*, void*, const ModelRenderInfo_t&, void*);

#endif