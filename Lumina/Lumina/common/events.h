#ifndef events_h

#define events_h

#include "../sdk/interfaces/IGameEventManager.h"

// from fatality.win source code

using eventWorker = void(*)(IGameEvent*);

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