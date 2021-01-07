#ifndef menu_h

#define menu_h

#include "../sdk/math/Color.h"
#include "texture.h"
//#include "../ui/fgui/widgets/checkbox.hpp"
//#include "../ui/fgui/widgets/multibox.hpp"

namespace menu {

	extern bool visible;

	extern int x;
	extern int y;
	extern int alphaBackground;
	extern int alphaIntro;

	extern int lineSize;
	extern int spaceSize;
	extern int tabSpaceSize;
	extern int tabIconX;

	extern Color lightTop;
	extern Color lightBottom;

	extern Color mainTop;
	extern Color mainBottom;

	extern Color mainTabLight;
	extern Color mainTab;

	extern Color highContrast;

	extern Color textColor;

	extern texture logo;

	extern std::string inputSkin ;
	extern std::string inputKnifeSkin ;
	extern std::string inputWear ;
	extern std::string inputSeed ;

	extern std::string inputSticker1 ;
	extern std::string inputSticker2 ;
	extern std::string inputSticker3 ;
	extern std::string inputSticker4 ;

	extern void loadConfig();

	void drawVisualTab();
	void drawMiscTab();
	void drawSkinTab();
	void drawSound();

	void init();
	void drawMenu();
	void toggle();
	void skinUpdateCallback();
	//void multiboxCallback(std::pair<std::vector<std::string>, std::vector<bool*>> config, std::shared_ptr<FGUI::CMultiBox> box);
	//void checkboxCallback(bool* configValue, std::shared_ptr<FGUI::CCheckBox> checkbox);
	void draw();
	void drawIntro();
	void moduleAlpha();
	void drawBackground();
}

#endif