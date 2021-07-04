#ifndef misc_h_

#define misc_h_

#include <string>

namespace misc {

	extern bool nameChanged;

	void hitmarkerSound(void* event, void* eventInfo);

	//void fixSkin(void* event, void* eventInfo);

	void roundSounds(void* event, void* eventInfo);

	void headShoot(void* event, void* eventInfo);

	void fakeMessage(std::string mes);

	void fastStop(void* cmd);

	void copyClipboardExploit();

	void silentWalk(void* cmd_);

	void infiniteDuck(void* cmd);

	void hideVoteName();

	void voteRealer(void* event, void* eventInfo);
}

#endif // !misc_h_