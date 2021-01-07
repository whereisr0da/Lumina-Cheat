#ifndef sound_h

#define sound_h

#include <string>
#include <vector>

namespace sound {

	void init();

	void playOpeningSound();

	void playClosingSound();

	void writeFile(const char* name, const char* buffer, int size);

	//extern const char openRaw[];

	//extern const char closeRaw[];

	extern std::vector<std::string> sounds;
}
#endif