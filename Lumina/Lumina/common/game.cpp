#include "game.h"

#include "../sdk/interfaces.h"
#include "common.h"

namespace game {

	Entity* getLocalPlayer() {

		VMProtectBeginMutation("game::getLocalPlayer");

		Entity* entity = (Entity*)interfaces::clientEntityList->GetClientEntity(interfaces::engineClient->GetLocalPlayer());

		VMProtectEnd();

		return entity;
	}

	bool isEnvironmentValid() {

		VMProtectBeginMutation("game::isEnvironmentValid");

		bool result = interfaces::engineClient->IsConnected() && interfaces::engineClient->IsInGame();

		VMProtectEnd();

		return result;
	}

	ConVar* getConvarNullCallback(const char* name) {

		VMProtectBeginMutation("game::getConvarNullCallback");

		ConVar* convar = (ConVar*)interfaces::console->get_convar(name);

		*(int*)((DWORD)&convar->fnChangeCallbacks + 0xC) = NULL;

		VMProtectEnd();

		return convar;
	}
}
