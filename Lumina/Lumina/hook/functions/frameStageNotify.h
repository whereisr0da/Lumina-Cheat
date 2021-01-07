#ifndef frameStageNotify_h

#define frameStageNotify_h

void __stdcall frameStageNotifyHook(int frameStage);

using frameStageNotifyPrototype = void(__thiscall*)(void*, int);

#endif