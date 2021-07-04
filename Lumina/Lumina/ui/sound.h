#ifndef sound_h

#define sound_h

#include <string>
#include <vector>

namespace sound {

	void init();

	void playOpeningSound();

	void playClosingSound();

	void playSoundShort(int id);

	extern std::vector<std::string> sounds_short;
	extern std::vector<std::string> sounds_long;
}
#endif