#include "events.h"

#include "../sdk/interfaces.h"
#include "../features/misc/voice.h"
#include "../features/misc/misc.h"
#include "common.h"

namespace events {

	listener* eventListener = NULL;

	std::map<std::string, eventWorker*> eventWorkers;

	void init() {

		eventWorkers = {};

		eventListener = new listener();

#ifdef _DEBUG
		common::ps(XorStr("events::init : done"));
#endif
	}

	void shutdown() {

		interfaces::gameEventManager->RemoveListener(eventListener);
		
		eventWorkers.clear();

		delete eventListener;
	}

#define ADD_EVENT(str,pointer,var) \
	std::string var = XorStr(str); \
	eventWorkers[var] = (eventWorker*)pointer;\

	listener::listener()
	{
		VMProtectBeginMutation("listener::listener");

		ADD_EVENT("player_hurt", misc::hitmarkerSound, tmp0)
		//ADD_EVENT("player_spawned", misc::fixSkin, tmp1)
		ADD_EVENT("round_end", misc::roundSounds, tmp2)
		ADD_EVENT("round_start", misc::roundSounds, tmp3)
		ADD_EVENT("player_death", misc::headShoot, tmp4)

		for (auto& eventPointer : eventWorkers)
			interfaces::gameEventManager->AddListener(this, eventPointer.first.c_str(), false);

#ifdef _DEBUG
		common::ps(XorStr("listener::listener : done"));
#endif

		VMProtectEnd();
	};

	void listener::FireGameEvent(IGameEvent* event) {

		VMProtectBeginMutation("listener::FireGameEvent");

		if (event) {

			std::string eventName = event->GetName();

			if (eventWorkers.count(eventName)) 
				((eventWorker)eventWorkers.at(eventName))(event);
		
		}

		VMProtectEnd();
	}
}
