#ifndef skinchanger_h

#define skinchanger_h

#include <string>
#include <vector>

namespace skinchanger {

	extern std::vector<std::string> playerModels;

	extern bool updateSkin;

	void init();

	void frameStageNotify(int frameStage);

	void applyWeaponSkins();

	void applyPlayerModel(int frameStage);
}

#endif // !skinchanger_h