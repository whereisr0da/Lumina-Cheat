#ifndef events_h

#define events_h

#include "../sdk/interfaces/IGameEventManager.h"
#include "includes.h"

struct eventInfo {
	char* name;
	uint32_t hash;
	bool clientside;
	void* callback;
};

using eventWorker = void(*)(IGameEvent*, eventInfo*);

// from fatality.win source code

namespace events {

	void init();
	void shutdown();

	class listener : public IGameEventListener2
	{
	public:

		listener();

		virtual void	FireGameEvent(IGameEvent* event);

		int				GetEventDebugID() override { return 0x2A; };
	};
}

#endif // !events_h