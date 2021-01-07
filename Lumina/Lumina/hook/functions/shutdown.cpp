#include "shutdown.h"
#include "../../sdk/interfaces.h"
#include "../../ui/menu.h"
#include "../../common/common.h"
#include "../../common/input.h"
#include "../../common/events.h"

void __stdcall shutdownHook(void* _interface) {

	VMProtectBeginMutation("shutdownHook");

	auto returnCall = reinterpret_cast<shutdownFN>(hook::clientHook.get_original(4));

#ifdef _DEBUG
	common::ps(XorStr("shutdownHook : started"));
#endif 

	common::unload = true;

	events::shutdown();

	hook::shutdown();

	input::undo();

	common::active = false;

#ifdef _DEBUG
	common::ps(XorStr("shutdownHook : done"));
#endif 

	returnCall(interfaces::baseClientDll);

	VMProtectEnd();
}