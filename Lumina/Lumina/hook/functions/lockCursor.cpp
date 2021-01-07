#include "lockCursor.h"
#include "../../sdk/interfaces.h"
#include "../../ui/menu.h"
#include "../../common/common.h"

void __stdcall lockCursorHook(){

	auto returnCall = reinterpret_cast<lockCursorFn>(hook::surfaceHook.get_original(67));

	VMProtectBeginMutation("lockCursorHook");

	if (common::unload)
		return returnCall(interfaces::surface);

	if (menu::visible) {

		interfaces::surface->UnlockCursor();
		return;
	}

	VMProtectEnd();

	return returnCall(interfaces::surface);
}