#include "events.h"

#include "../sdk/interfaces.h"
#include "../features/misc/voice.h"
#include "../features/misc/misc.h"
#include "common.h"

namespace events {

	listener* eventListener = NULL;

	std::map<hash32_t, eventInfo*> eventWorkers;

	void init() {

		eventWorkers = {};

		eventListener = new listener();

#ifdef _DEBUG
		common::ps(XorStr("events::init : done"));
#endif
	}

	void shutdown() {

		interfaces::gameEventManager->RemoveListener(eventListener);
		
		for (auto& eventInfoPointer : eventWorkers)
			free((eventInfo*)(eventInfoPointer.second));

		eventWorkers.clear();

		delete eventListener;

#ifdef _DEBUG
		common::ps(XorStr("events::shutdown : done"));
#endif
	}

#define ADD_EVENT(str,pointer,var) \
	eventInfo* var = (eventInfo*)malloc(sizeof(eventInfo)); \
	var->name = XorStr(str); \
	var->hash = HASH(str); \
	var->callback = (void*)pointer; \
	eventWorkers[var->hash] = var; \

	listener::listener()
	{
		VMProtectBeginMutation("listener::listener");

		ADD_EVENT("player_hurt", misc::hitmarkerSound, tmp0)
		//ADD_EVENT("player_spawned", misc::fixSkin, tmp1)
		ADD_EVENT("round_end", misc::roundSounds, tmp2)
		ADD_EVENT("round_start", misc::roundSounds, tmp3)
		ADD_EVENT("player_death", misc::headShoot, tmp4)

		for (auto& eventInfoPointer : eventWorkers)
			interfaces::gameEventManager->AddListener(this, eventInfoPointer.second->name, false);

#ifdef _DEBUG
		common::ps(XorStr("listener::listener : done"));
#endif

		VMProtectEnd();
	};

	void listener::FireGameEvent(IGameEvent* event) {

		VMProtectBeginMutation("listener::FireGameEvent");

		if (event) {

			hash32_t eventNameHash = FNV1a::get(event->GetName());

			if (eventWorkers.count(eventNameHash)){
				auto currentEventInfo = eventWorkers.at(eventNameHash);
				((eventWorker)currentEventInfo->callback)(event, currentEventInfo);
			}
		}

		VMProtectEnd();
	}
}
