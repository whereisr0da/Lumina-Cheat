#ifndef config_h

#define config_h

#include "../sdk/math/Color.h"
#include <string>

struct skin {
		int paint; 
		float wear; 
		int seed; 
		bool stattrack;
		int stattrackCount; 
		int quality; 
		int sticker1; 
		int sticker2; 
		int sticker3; 
		int sticker4; 
}; 

#define SKIN(name) \
	skin name;
/*
	struct skin name { \
		int paint; \
		float wear; \
		int seed; \
		bool stattrack; \
		int stattrackCount; \
		int quality; \
		int sticker1; \
		int sticker2; \
		int sticker3; \
		int sticker4; \
	}; \
*/

#define SKIN_COLLECTION(name) \
	struct { \
		int knifeId; \
		int knifePaint; \
		SKIN(awpSkin) \
		SKIN(ak47Skin) \
		SKIN(uspSkin) \
		SKIN(deagleSkin) \
		SKIN(ssg08Skin) \
		SKIN(scarSkin) \
		SKIN(m4a1Skin) \
		SKIN(famasSkin) \
		SKIN(g3sg1Skin) \
		SKIN(m4a1s1Skin) \
		SKIN(sg553Skin) \
		SKIN(augSkin) \
		SKIN(galilSkin) \
	    SKIN(mac10Skin) \
		SKIN(mp5Skin) \
		SKIN(mp7Skin) \
		SKIN(mp9Skin) \
		SKIN(ppbizonSkin) \
		SKIN(p90Skin) \
		SKIN(umpSkin) \
		SKIN(cz75Skin) \
		SKIN(dualberttaSkin) \
		SKIN(fiveSevenSkin) \
		SKIN(glockSkin) \
		SKIN(p250Skin) \
		SKIN(tec9Skin) \
		SKIN(revolverSkin) \
	} name; \

struct chams_t
{
	bool enable;
	int material;
	bool rainbowColor;
	Color color;
	bool throughWall;
	bool throughWallOnlyIfDead;

	bool enableOverlay;
	int overlayMaterial;
	bool overlayRainbowColor;
	Color overlayColor;
};

#define CHAMS_(name) \
	chams_t name; \


#define BOOL_WRITE(bool_, config) \
	std::istringstream(config.asString()) >> std::boolalpha >> bool_;

#define INT_WRITE(int_, config) \
	 int_ = std::stoi(config.asString());

#define FLOAT_WRITE(float_, config) \
	 float_ = std::stof(config.asString());


#define CHAMS_JSON(name, nameStr, pad, pad0) \
	config[XorStr(nameStr)][XorStr("enable")] = visual.name.enable; \
	config[XorStr(nameStr)][XorStr("throughWall")] = visual.name.throughWall; \
	config[XorStr(nameStr)][XorStr("throughWallOnlyIfDead")] = visual.name.throughWallOnlyIfDead; \
	config[XorStr(nameStr)][XorStr("material")] = visual.name.material; \
	config[XorStr(nameStr)][XorStr("rainbowColor")] = visual.name.rainbowColor; \
	COLOR_JSON_WRITE(pad, visual.name.color) \
	config[XorStr(nameStr)][XorStr("color")] = pad; \
	config[XorStr(nameStr)][XorStr("enableOverlay")] = visual.name.enableOverlay; \
	config[XorStr(nameStr)][XorStr("overlayMaterial")] = visual.name.overlayMaterial; \
	config[XorStr(nameStr)][XorStr("overlayRainbowColor")] = visual.name.overlayRainbowColor; \
	COLOR_JSON_WRITE(pad0, visual.name.overlayColor) \
	config[XorStr(nameStr)][XorStr("overlayColor")] = pad0; \

#define COLOR_JSON_WRITE(name, path) \
		Json::Value name(Json::arrayValue); \
		name.append(Json::Value(path.r())); \
		name.append(Json::Value(path.g())); \
		name.append(Json::Value(path.b())); \
		name.append(Json::Value(path.a())); \

#define SKIN_JSON(side,name,sideStr,nameStr) \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("paint")] = visual.skins.side.name.paint; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("wear")] = visual.skins.side.name.wear; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("seed")] = visual.skins.side.name.seed; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("stattrack")] = visual.skins.side.name.stattrack; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("stattrackCount")] = visual.skins.side.name.stattrackCount; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("quality")] = visual.skins.side.name.quality; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("sticker1")] = visual.skins.side.name.sticker1; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("sticker2")] = visual.skins.side.name.sticker2; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("sticker3")] = visual.skins.side.name.sticker3; \
	config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("sticker4")] = visual.skins.side.name.sticker4; \

#define SKIN_COLLECTION_JSON(side, sideStr) \
		SKIN_JSON(side, awpSkin, sideStr, "awpSkin") \
		SKIN_JSON(side, ak47Skin, sideStr, "ak47Skin") \
		SKIN_JSON(side, uspSkin, sideStr, "uspSkin") \
		SKIN_JSON(side, deagleSkin, sideStr, "deagleSkin") \
		SKIN_JSON(side, ssg08Skin, sideStr, "ssg08Skin") \
		SKIN_JSON(side, scarSkin, sideStr, "scarSkin") \
		SKIN_JSON(side, m4a1Skin, sideStr, "m4a1Skin") \
		SKIN_JSON(side, famasSkin, sideStr, "famasSkin") \
		SKIN_JSON(side, g3sg1Skin, sideStr, "g3sg1Skin") \
		SKIN_JSON(side, m4a1s1Skin, sideStr, "m4a1s1Skin") \
		SKIN_JSON(side, sg553Skin, sideStr, "sg553Skin") \
		SKIN_JSON(side, augSkin, sideStr, "augSkin") \
		SKIN_JSON(side, galilSkin, sideStr, "galilSkin") \
	    SKIN_JSON(side, mac10Skin, sideStr, "mac10Skin") \
		SKIN_JSON(side, mp5Skin, sideStr, "mp5Skin") \
		SKIN_JSON(side, mp7Skin, sideStr, "mp7Skin") \
		SKIN_JSON(side, mp9Skin, sideStr, "mp9Skin") \
		SKIN_JSON(side, ppbizonSkin, sideStr, "ppbizonSkin") \
		SKIN_JSON(side, p90Skin, sideStr, "p90Skin") \
		SKIN_JSON(side, umpSkin, sideStr, "umpSkin") \
		SKIN_JSON(side, cz75Skin, sideStr, "cz75Skin") \
		SKIN_JSON(side, dualberttaSkin, sideStr, "dualberttaSkin") \
		SKIN_JSON(side, fiveSevenSkin, sideStr, "fiveSevenSkin") \
		SKIN_JSON(side, glockSkin, sideStr, "glockSkin") \
		SKIN_JSON(side, p250Skin, sideStr, "p250Skin") \
		SKIN_JSON(side, tec9Skin, sideStr, "tec9Skin") \
		SKIN_JSON(side, revolverSkin, sideStr, "revolverSkin") \


#define COLOR_JSON_READ(path,json) \
		path.SetColor(std::stoi(json[0].asString()),std::stoi(json[1].asString()),std::stoi(json[2].asString()),std::stoi(json[3].asString())); \

#define SKIN_JSON_READ(side,name,sideStr,nameStr) \
	INT_WRITE(visual.skins.side.name.paint, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("paint")]); \
	FLOAT_WRITE(visual.skins.side.name.wear, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("wear")]); \
	INT_WRITE(visual.skins.side.name.seed, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("seed")]); \
	BOOL_WRITE(visual.skins.side.name.stattrack, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("stattrack")]); \
	INT_WRITE(visual.skins.side.name.stattrackCount, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("stattrackCount")]); \
	INT_WRITE(visual.skins.side.name.quality, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("quality")]); \
	INT_WRITE(visual.skins.side.name.sticker1, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("sticker1")]); \
	INT_WRITE(visual.skins.side.name.sticker2, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("sticker2")]); \
	INT_WRITE(visual.skins.side.name.sticker3, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("sticker3")]); \
	INT_WRITE(visual.skins.side.name.sticker4, config[XorStr("skins")][XorStr(sideStr)][XorStr(nameStr)][XorStr("sticker4")]); \

#define CHAMS_JSON_READ(name, nameStr, pad) \
	BOOL_WRITE(visual.name.enable, config[XorStr(nameStr)][XorStr("enable")]); \
	BOOL_WRITE(visual.name.throughWall, config[XorStr(nameStr)][XorStr("throughWall")]); \
	BOOL_WRITE(visual.name.throughWallOnlyIfDead, config[XorStr(nameStr)][XorStr("throughWallOnlyIfDead")]); \
	INT_WRITE(visual.name.material, config[XorStr(nameStr)][XorStr("material")]); \
	BOOL_WRITE(visual.name.rainbowColor, config[XorStr(nameStr)][XorStr("rainbowColor")]); \
	COLOR_JSON_READ(visual.name.color, config[XorStr(nameStr)][XorStr("color")]) \
	BOOL_WRITE(visual.name.enableOverlay, config[XorStr(nameStr)][XorStr("enableOverlay")]); \
	INT_WRITE(visual.name.overlayMaterial, config[XorStr(nameStr)][XorStr("overlayMaterial")]); \
	BOOL_WRITE(visual.name.overlayRainbowColor, config[XorStr(nameStr)][XorStr("overlayRainbowColor")]); \
	COLOR_JSON_READ(visual.name.overlayColor, config[XorStr(nameStr)][XorStr("overlayColor")]) \


#define SKIN_COLLECTION_JSON_READ(side, sideStr) \
		SKIN_JSON_READ(side, awpSkin, sideStr, "awpSkin") \
		SKIN_JSON_READ(side, ak47Skin, sideStr, "ak47Skin") \
		SKIN_JSON_READ(side, uspSkin, sideStr, "uspSkin") \
		SKIN_JSON_READ(side, deagleSkin, sideStr, "deagleSkin") \
		SKIN_JSON_READ(side, ssg08Skin, sideStr, "ssg08Skin") \
		SKIN_JSON_READ(side, scarSkin, sideStr, "scarSkin") \
		SKIN_JSON_READ(side, m4a1Skin, sideStr, "m4a1Skin") \
		SKIN_JSON_READ(side, famasSkin, sideStr, "famasSkin") \
		SKIN_JSON_READ(side, g3sg1Skin, sideStr, "g3sg1Skin") \
		SKIN_JSON_READ(side, m4a1s1Skin, sideStr, "m4a1s1Skin") \
		SKIN_JSON_READ(side, sg553Skin, sideStr, "sg553Skin") \
		SKIN_JSON_READ(side, augSkin, sideStr, "augSkin") \
		SKIN_JSON_READ(side, galilSkin, sideStr, "galilSkin") \
	    SKIN_JSON_READ(side, mac10Skin, sideStr, "mac10Skin") \
		SKIN_JSON_READ(side, mp5Skin, sideStr, "mp5Skin") \
		SKIN_JSON_READ(side, mp7Skin, sideStr, "mp7Skin") \
		SKIN_JSON_READ(side, mp9Skin, sideStr, "mp9Skin") \
		SKIN_JSON_READ(side, ppbizonSkin, sideStr, "ppbizonSkin") \
		SKIN_JSON_READ(side, p90Skin, sideStr, "p90Skin") \
		SKIN_JSON_READ(side, umpSkin, sideStr, "umpSkin") \
		SKIN_JSON_READ(side, cz75Skin, sideStr, "cz75Skin") \
		SKIN_JSON_READ(side, dualberttaSkin, sideStr, "dualberttaSkin") \
		SKIN_JSON_READ(side, fiveSevenSkin, sideStr, "fiveSevenSkin") \
		SKIN_JSON_READ(side, glockSkin, sideStr, "glockSkin") \
		SKIN_JSON_READ(side, p250Skin, sideStr, "p250Skin") \
		SKIN_JSON_READ(side, tec9Skin, sideStr, "tec9Skin") \
		SKIN_JSON_READ(side, revolverSkin, sideStr, "revolverSkin") \

namespace config {

	struct visuals {

		struct
		{
			bool showOnlyIsDead;
			bool showBox;
			bool showName;
			bool showSkeleton;
			bool showLife;
			bool showAmmo;
			bool showIcons;
			bool showIconsOnly;
			bool showWeaponName;
			bool showWeaponIcon;
			bool showPing;
			bool showMoney;
			bool showArmor;
			bool showHasDefuser;
			bool showPlanting;
			bool showDefusing;
			bool showReload;
			bool showBomb;
			bool showFlashed;
			bool showScopping;
			bool showCheating;
			bool showFakeDuck;
			bool showLegitAA;
			Color espColor;

		} enemyEsp;

		struct {
			bool enable;
			bool onlyIfDead;
			float bloom;
			Color glowColor;
		} glow;

		struct
		{
			bool showName;
			Color espColor;
		} weaponEsp;

		struct
		{
			bool enable;
			int id;
		} playerModel;

		struct
		{
			bool enable;
			int id;
		} teamMateModel;

		CHAMS_(enemyChamsVisible)
		CHAMS_(enemyChamsNotVisible)
		CHAMS_(enemyChamsBacktrack)
		CHAMS_(weaponWorldChams)
		CHAMS_(handChams)
		CHAMS_(gloveChams)
		CHAMS_(sleeveChams)
		CHAMS_(weaponChams)

		struct
		{
			bool enable;
			float min;

		} spreadCircle;

		struct
		{
			bool showFlashDuration;

		} indicators;

		struct
		{
			bool enable;
			SKIN_COLLECTION(ctSkins)
			SKIN_COLLECTION(tSkins)
		} skins;

		struct
		{
			bool enable;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} hitmarkerSound;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} headShootSound;


			struct
			{
				int index;
				bool random;
				bool through_mic;
			} roundStartSound;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} roundEndLostSound;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} roundEndWonSound;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} bombPlantedSound;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} voteStartedSound;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} voteChangedSound;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} votePassedSound;

			struct
			{
				int index;
				bool random;
				bool through_mic;
			} voteFailledSound;

		} sounds;

		bool showSpectators;
		bool showGrenadePred;
		bool showRadar;

		struct
		{
			bool enable;
			Color worldColor;
			Color propsColor;
		} world;

		struct
		{
			bool enable;
			int sky;
			Color skyColor;
		} sky;
	};

	struct cheat {

		bool fastStop;
		bool silentWalk;
		bool optimization;
		bool infinitDuck;

		bool volumeEsp;

		bool backtrack;
		float backtrackVisibility;
		float backtrackTime;
	};

	extern visuals visual;

	extern cheat cheats;

	void init();

	void openVisualConfig(std::string name);

	void saveVisualConfig(std::string name);

	void openCheatConfig(std::string name);

	void saveCheatConfig(std::string name);
}

#endif