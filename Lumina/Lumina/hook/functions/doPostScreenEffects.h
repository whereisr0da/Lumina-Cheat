#ifndef doPostScreenEffects_h

#define doPostScreenEffects_h

using doPostScreenEffectFn = int(__thiscall*)(void *, int);

int __stdcall doPostScreenEffectHook(int value);

#endif