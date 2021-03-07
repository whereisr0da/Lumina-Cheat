#include "paintTraverse.h"

#include "../../sdk/interfaces.h"
#include "../../ui/menu.h"
#include "../../features/visuals/esp.h"
#include "../../features/visuals/visualMisc.h"
#include "../../common/common.h"

void __stdcall paintTraverseHook(unsigned int panel, bool force_repaint, bool allow_force) {

	VMProtectBeginMutation("paintTraverseHook");

	auto returnCall = reinterpret_cast<paintTraverseFN>(hook::panelHook.get_original(41));

	if (common::unload)
		return returnCall(interfaces::panel, panel, force_repaint, allow_force);

	// render the original process
	returnCall(interfaces::panel, panel, force_repaint, allow_force);

	// last panel
	if (FNV1a::get(interfaces::panel->GetName(panel)) == HASH("MatSystemTopPanel")) {

		if (game::getLocalPlayer() && game::isEnvironmentValid())
		{
			esp::paintTraverse();
			
			visualMisc::drawSpreadCircle();

			visualMisc::drawSpectators();

			visualMisc::drawFlashTimer();

			visualMisc::drawHitmarker();
		}

		menu::draw();

		//visualMisc::watermark();
	}

	VMProtectEnd();
}