#ifndef common_h

#define common_h

#include "../common/includes.h"

#define VECTOR_PUSH(vec, str, ord) \
	const char* ord = StringHeavy(str); \
	vec.push_back(ord); \

#define VECTOR_PUSH_TUPLE(vec, str, pointer, ord, ord1) \
	const char* ord = StringHeavy(str); \
	zgui::multi_select_item ord1; \
	ord1.name = ord; \
	ord1.value = pointer; \
	vec.push_back(ord1); \

#define BLOCK __asm __emit 0xB0 __asm __emit 0x0B __asm __emit 0xF0 __asm __emit 0xB0 __asm __emit 0x0B __asm __emit 0xF0 __asm __emit 0xB0 __asm __emit 0xBE __asm __emit 0xEF __asm __emit 0xDE __asm __emit 0xAD __asm __emit 0x01 __asm __emit 0xDE __asm __emit 0xAD
#define JUNK(a) __asm jmp a BLOCK

namespace common {

	extern HMODULE currentModule;
	extern HMODULE engineModule;
	extern HMODULE clientModule;
	extern HMODULE materialsystemModule;
	extern HMODULE vguimatsurfaceModule;
	extern HMODULE vstdlibModule;
	extern HMODULE soundsystemModule;
	extern HMODULE vgui2Module;
	extern HMODULE datacacheModule;
	extern HMODULE dx9apiModule;
	extern HMODULE inputSysModule;
	extern HMODULE localizeModule;
	extern HMODULE steamApiModule;
	extern HMODULE studiorenderModule;

	extern std::string luminaPath;

	extern bool active;

	extern bool unload;

	extern float hitmarkerTime;
	extern int   hitmarkerDamage;

//#ifdef _DEBUG
	void ps(std::string message);
	void pf(std::string fmt, ...);
//#endif

	void exit();
}

#endif // !common_h