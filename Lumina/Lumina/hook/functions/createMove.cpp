#include "../../common/includes.h"

#include "../../sdk/interfaces.h"
#include "../../common/common.h"
#include "../../features/misc/misc.h"
#include "../../features/backtrack/backtrack.h"
#include "../../features/misc/soundEsp.h"
#include "../../features/misc/voice.h"

bool __stdcall createMoveHook(float smt, void* cmd) {

	VMProtectBeginMutation("createMoveHook");

	auto returnCall = reinterpret_cast<createMoveFn>(hook::clientModeHook.get_original(24));

	CUserCmd* userCmd = (CUserCmd*)cmd;

	if(!userCmd || !userCmd->command_number || !game::getLocalPlayer() || !game::isEnvironmentValid() || common::unload)
		return returnCall(interfaces::clientMode, smt, cmd);

	bool originalCall = returnCall(interfaces::clientMode, smt, cmd);

	if (game::getLocalPlayer()->isAlive()) {
		misc::fastStop(userCmd);
		backtrack::run(userCmd);
		soundEsp::worker(userCmd);
		//misc::silentWalk(userCmd);
		misc::infiniteDuck(userCmd);
		voice::tick();
	}

	VMProtectEnd();

	return false;
}