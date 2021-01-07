#include "config.h"

#include "common.h"
#include "../ui/menu.h"
#include "json/json.h"

#include <fstream>

#define BOOL_WRITE(bool_, config) \
	std::istringstream(config.asString()) >> std::boolalpha >> bool_;

#define INT_WRITE(int_, config) \
	 int_ = std::stoi(config.asString());

#define FLOAT_WRITE(float_, config) \
	 float_ = std::stof(config.asString());

namespace config {

	visuals visual;
	cheat cheats;

	void init() {

		ZeroMemory(&visual, sizeof(visuals));
		ZeroMemory(&cheats, sizeof(cheat));

#ifdef _DEBUG
		common::ps(XorStr("config::init : done"));
#endif
	}

	void openCheatConfig(std::string name) {

		VMProtectBeginMutation("config::openCheatConfig");

		std::string configPath = common::luminaPath + name;

		Json::Value config;

		std::ifstream file(configPath, std::ifstream::binary);

		file >> config;

		BOOL_WRITE(cheats.fastStop, config[XorStr("fastStop")])
		BOOL_WRITE(cheats.silentWalk, config[XorStr("silentWalk")])

#ifdef _DEBUG
		common::ps(XorStr("config::openCheatConfig : done"));
#endif

		VMProtectEnd();
	}

	void saveCheatConfig(std::string name) {

		VMProtectBeginMutation("config::saveCheatConfig");

		std::string configPath = common::luminaPath + name;

		Json::Value config;


		config[XorStr("fastStop")] = cheats.fastStop;
		config[XorStr("silentWalk")] = cheats.silentWalk;

		std::remove(configPath.c_str());

		std::ofstream file;

		file.open(configPath.c_str(), std::ios_base::app);

		Json::StreamWriterBuilder builder;

		builder["commentStyle"] = "None";
		builder["indentation"] = "   ";

		std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

		writer->write(config, &file);

		file.close();

#ifdef _DEBUG
		common::ps(XorStr("config::saveCheatConfig : done"));
#endif

		VMProtectEnd();
	}

	void openVisualConfig(std::string name) {

		VMProtectBeginMutation("config::openVisualConfig");

		std::string configPath = common::luminaPath + name;

		Json::Value config;

		std::ifstream file(configPath, std::ifstream::binary);

		file >> config;

		// serialization is not working :(
		// so ghettto json read

		BOOL_WRITE(visual.enemyEsp.showOnlyIsDead, config[XorStr("enemyEsp")][XorStr("showOnlyIsDead")])
		BOOL_WRITE(visual.enemyEsp.showBox, config[XorStr("enemyEsp")][XorStr("showBox")]);
		BOOL_WRITE(visual.enemyEsp.showName, config[XorStr("enemyEsp")][XorStr("showName")]);
		BOOL_WRITE(visual.enemyEsp.showSkeleton, config[XorStr("enemyEsp")][XorStr("showSkeleton")]);
		BOOL_WRITE(visual.enemyEsp.showLife, config[XorStr("enemyEsp")][XorStr("showLife")]);
		BOOL_WRITE(visual.enemyEsp.showAmmo, config[XorStr("enemyEsp")][XorStr("showAmmo")]);
		BOOL_WRITE(visual.enemyEsp.showIcons, config[XorStr("enemyEsp")][XorStr("showIcons")]);
		BOOL_WRITE(visual.enemyEsp.showWeaponName, config[XorStr("enemyEsp")][XorStr("showWeaponName")]);
		BOOL_WRITE(visual.enemyEsp.showWeaponIcon, config[XorStr("enemyEsp")][XorStr("showWeaponIcon")]);
		BOOL_WRITE(visual.enemyEsp.showPing, config[XorStr("enemyEsp")][XorStr("showPing")]);
		BOOL_WRITE(visual.enemyEsp.showMoney, config[XorStr("enemyEsp")][XorStr("showMoney")]);
		BOOL_WRITE(visual.enemyEsp.showArmor, config[XorStr("enemyEsp")][XorStr("showArmor")]);
		BOOL_WRITE(visual.enemyEsp.showHasDefuser, config[XorStr("enemyEsp")][XorStr("showHasDefuser")]);
		BOOL_WRITE(visual.enemyEsp.showDefusing, config[XorStr("enemyEsp")][XorStr("showDefusing")]);
		BOOL_WRITE(visual.enemyEsp.showReload, config[XorStr("enemyEsp")][XorStr("showReload")]);
		BOOL_WRITE(visual.enemyEsp.showBomb, config[XorStr("enemyEsp")][XorStr("showBomb")]);
		BOOL_WRITE(visual.enemyEsp.showFlashed, config[XorStr("enemyEsp")][XorStr("showFlashed")]);
		BOOL_WRITE(visual.enemyEsp.showScopping, config[XorStr("enemyEsp")][XorStr("showScopping")]);
		BOOL_WRITE(visual.enemyEsp.showCheating, config[XorStr("enemyEsp")][XorStr("showCheating")]);
		BOOL_WRITE(visual.enemyEsp.showFakeDuck, config[XorStr("enemyEsp")][XorStr("showFakeDuck")]);
		BOOL_WRITE(visual.enemyEsp.showLegitAA, config[XorStr("enemyEsp")][XorStr("showLegitAA")]);
		BOOL_WRITE(visual.enemyEsp.showFakeDuck, config[XorStr("enemyEsp")][XorStr("showFakeDuck")]);
		BOOL_WRITE(visual.enemyEsp.showPlanting, config[XorStr("enemyEsp")][XorStr("showPlanting")]);

		BOOL_WRITE(visual.sounds.enable, config[XorStr("sounds")][XorStr("enable")]);
		INT_WRITE(visual.sounds.hitmarkerSound, config[XorStr("sounds")][XorStr("hitmarkerSound")]);
		INT_WRITE(visual.sounds.headShootSound, config[XorStr("sounds")][XorStr("headShootSound")]);
		INT_WRITE(visual.sounds.roundStartSound, config[XorStr("sounds")][XorStr("roundStartSound")]);
		INT_WRITE(visual.sounds.roundEndLostSound, config[XorStr("sounds")][XorStr("roundEndLostSound")]);
		INT_WRITE(visual.sounds.roundEndWonSound, config[XorStr("sounds")][XorStr("roundEndWonSound")]);
		INT_WRITE(visual.sounds.bombPlantedSound, config[XorStr("sounds")][XorStr("bombPlantedSound")]);
		INT_WRITE(visual.sounds.playerKickSound, config[XorStr("sounds")][XorStr("playerKickSound")]);


		BOOL_WRITE(visual.playerModel.enable, config[XorStr("playerModel")][XorStr("enable")]);
		INT_WRITE(visual.playerModel.id, config[XorStr("playerModel")][XorStr("id")]);

#define COLOR_JSON_READ(path,json) \
		path.SetColor(std::stoi(json[0].asString()),std::stoi(json[1].asString()),std::stoi(json[2].asString()),std::stoi(json[3].asString())); \

		COLOR_JSON_READ(visual.enemyEsp.espColor, config[XorStr("enemyEsp")][XorStr("espColor")])

		BOOL_WRITE(visual.glow.enable, config[XorStr("glow")][XorStr("enable")]);
		FLOAT_WRITE(visual.glow.bloom, config[XorStr("glow")][XorStr("bloom")]);
		BOOL_WRITE(visual.glow.onlyIfDead, config[XorStr("glow")][XorStr("onlyIfDead")])

		COLOR_JSON_READ(visual.glow.glowColor, config[XorStr("glow")][XorStr("glowColor")])

		BOOL_WRITE(visual.skins.enable, config[XorStr("skins")][XorStr("enable")]);

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

		SKIN_COLLECTION_JSON_READ(ctSkins, "ctSkins")

		//config::visual.skins.ctSkins.knifeId
		INT_WRITE(visual.skins.ctSkins.knifeId, config[XorStr("skins")][XorStr("ctSkins")][XorStr("knifeId")])
		INT_WRITE(visual.skins.ctSkins.knifePaint, config[XorStr("skins")][XorStr("ctSkins")][XorStr("knifePaint")])

		SKIN_COLLECTION_JSON_READ(tSkins, "tSkins")

		INT_WRITE(visual.skins.tSkins.knifeId, config[XorStr("skins")][XorStr("tSkins")][XorStr("knifeId")])
		INT_WRITE(visual.skins.tSkins.knifePaint, config[XorStr("skins")][XorStr("tSkins")][XorStr("knifePaint")])

#define CHAMS_JSON_READ(name, nameStr, pad) \
	BOOL_WRITE(visual.name.enable, config[XorStr(nameStr)][XorStr("enable")]); \
	BOOL_WRITE(visual.name.throughWall, config[XorStr(nameStr)][XorStr("throughWall")]); \
	BOOL_WRITE(visual.name.throughWallOnlyIfDead, config[XorStr(nameStr)][XorStr("throughWallOnlyIfDead")]); \
	INT_WRITE(visual.name.material, config[XorStr(nameStr)][XorStr("material")]); \
	BOOL_WRITE(visual.name.rainbowColor, config[XorStr(nameStr)][XorStr("rainbowColor")]); \
	COLOR_JSON_READ(visual.name.color, config[XorStr(nameStr)][XorStr("color")]) \

		BOOL_WRITE(visual.showSpectators, config[XorStr("showSpectators")]);
		BOOL_WRITE(visual.spreadCircle.enable, config[XorStr("spreadCircle")][XorStr("enable")]);
		FLOAT_WRITE(visual.spreadCircle.min, config[XorStr("spreadCircle")][XorStr("min")]);
		BOOL_WRITE(visual.indicators.showFlashDuration, config[XorStr("indicators")][XorStr("showFlashDuration")]);

		CHAMS_JSON_READ(enemyChamsVisible, "enemyChamsVisible", color1)

		BOOL_WRITE(visual.showGrenadePred, config[XorStr("showGrenadePred")]);

		menu::loadConfig();

#ifdef _DEBUG
			common::ps(XorStr("config::openVisualConfig : done"));
#endif

		VMProtectEnd();
	}

	void saveVisualConfig(std::string name) {

		VMProtectBeginMutation("config::saveVisualConfig");

		std::string configPath = common::luminaPath + name;

		Json::Value config;

		// serialization is not working :(
		// so ghettto json writing

		config[XorStr("enemyEsp")][XorStr("showOnlyIsDead")] = visual.enemyEsp.showOnlyIsDead;
		config[XorStr("enemyEsp")][XorStr("showBox")] = visual.enemyEsp.showBox;
		config[XorStr("enemyEsp")][XorStr("showName")] = visual.enemyEsp.showName;
		config[XorStr("enemyEsp")][XorStr("showSkeleton")] = visual.enemyEsp.showSkeleton;
		config[XorStr("enemyEsp")][XorStr("showLife")] = visual.enemyEsp.showLife;
		config[XorStr("enemyEsp")][XorStr("showAmmo")] = visual.enemyEsp.showAmmo;
		config[XorStr("enemyEsp")][XorStr("showIcons")] = visual.enemyEsp.showIcons;
		config[XorStr("enemyEsp")][XorStr("showWeaponName")] = visual.enemyEsp.showWeaponName;
		config[XorStr("enemyEsp")][XorStr("showWeaponIcon")] = visual.enemyEsp.showWeaponIcon;
		config[XorStr("enemyEsp")][XorStr("showPing")] = visual.enemyEsp.showPing;
		config[XorStr("enemyEsp")][XorStr("showMoney")] = visual.enemyEsp.showMoney;
		config[XorStr("enemyEsp")][XorStr("showArmor")] = visual.enemyEsp.showArmor;
		config[XorStr("enemyEsp")][XorStr("showHasDefuser")] = visual.enemyEsp.showHasDefuser;
		config[XorStr("enemyEsp")][XorStr("showDefusing")] = visual.enemyEsp.showDefusing;
		config[XorStr("enemyEsp")][XorStr("showReload")] = visual.enemyEsp.showReload;
		config[XorStr("enemyEsp")][XorStr("showBomb")] = visual.enemyEsp.showBomb;
		config[XorStr("enemyEsp")][XorStr("showFlashed")] = visual.enemyEsp.showFlashed;
		config[XorStr("enemyEsp")][XorStr("showScopping")] = visual.enemyEsp.showScopping;
		config[XorStr("enemyEsp")][XorStr("showCheating")] = visual.enemyEsp.showCheating;
		config[XorStr("enemyEsp")][XorStr("showFakeDuck")] = visual.enemyEsp.showFakeDuck;
		config[XorStr("enemyEsp")][XorStr("showLegitAA")] = visual.enemyEsp.showLegitAA;
		config[XorStr("enemyEsp")][XorStr("showFakeDuck")] = visual.enemyEsp.showFakeDuck;
		config[XorStr("enemyEsp")][XorStr("showPlanting")] = visual.enemyEsp.showPlanting;

		config[XorStr("sounds")][XorStr("enable")] = visual.sounds.enable;
		config[XorStr("sounds")][XorStr("hitmarkerSound")] = visual.sounds.hitmarkerSound;
		config[XorStr("sounds")][XorStr("headShootSound")] = visual.sounds.headShootSound;
		config[XorStr("sounds")][XorStr("roundStartSound")] = visual.sounds.roundStartSound;
		config[XorStr("sounds")][XorStr("roundEndLostSound")] = visual.sounds.roundEndLostSound;
		config[XorStr("sounds")][XorStr("roundEndWonSound")] = visual.sounds.roundEndWonSound;
		config[XorStr("sounds")][XorStr("bombPlantedSound")] = visual.sounds.bombPlantedSound;
		config[XorStr("sounds")][XorStr("playerKickSound")] = visual.sounds.playerKickSound;

		config[XorStr("playerModel")][XorStr("enable")] = visual.playerModel.enable;
		config[XorStr("playerModel")][XorStr("id")] = visual.playerModel.id;

#define COLOR_JSON_WRITE(name, path) \
		Json::Value name(Json::arrayValue); \
		name.append(Json::Value(path.r())); \
		name.append(Json::Value(path.g())); \
		name.append(Json::Value(path.b())); \
		name.append(Json::Value(path.a())); \

		COLOR_JSON_WRITE(espColor, visual.enemyEsp.espColor)

		config[XorStr("enemyEsp")][XorStr("espColor")] = espColor;

		config[XorStr("glow")][XorStr("enable")] = visual.glow.enable;
		config[XorStr("glow")][XorStr("onlyIfDead")] = visual.glow.onlyIfDead;
		config[XorStr("glow")][XorStr("bloom")] = visual.glow.bloom;

		COLOR_JSON_WRITE(glowColor, visual.glow.glowColor)

		config[XorStr("glow")][XorStr("glowColor")] = glowColor;

		config[XorStr("skins")][XorStr("enable")] = visual.skins.enable;

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

		SKIN_COLLECTION_JSON(ctSkins, "ctSkins")

		config[XorStr("skins")][XorStr("ctSkins")][XorStr("knifeId")] = visual.skins.ctSkins.knifeId;
		config[XorStr("skins")][XorStr("ctSkins")][XorStr("knifePaint")] = visual.skins.ctSkins.knifePaint;

		SKIN_COLLECTION_JSON(tSkins, "tSkins")
		config[XorStr("skins")][XorStr("tSkins")][XorStr("knifeId")] = visual.skins.tSkins.knifeId;
		config[XorStr("skins")][XorStr("tSkins")][XorStr("knifePaint")] = visual.skins.tSkins.knifePaint;

#define CHAMS_JSON(name, nameStr, pad) \
	config[XorStr(nameStr)][XorStr("enable")] = visual.name.enable; \
	config[XorStr(nameStr)][XorStr("throughWall")] = visual.name.throughWall; \
	config[XorStr(nameStr)][XorStr("throughWallOnlyIfDead")] = visual.name.throughWallOnlyIfDead; \
	config[XorStr(nameStr)][XorStr("material")] = visual.name.material; \
	config[XorStr(nameStr)][XorStr("rainbowColor")] = visual.name.rainbowColor; \
	COLOR_JSON_WRITE(pad, visual.name.color) \
	config[XorStr(nameStr)][XorStr("color")] = pad; \

		config[XorStr("showGrenadePred")] = visual.showGrenadePred;
		config[XorStr("showSpectators")] = visual.showSpectators;
		config[XorStr("spreadCircle")][XorStr("enable")] = visual.spreadCircle.enable;
		config[XorStr("spreadCircle")][XorStr("min")] = visual.spreadCircle.min;
		config[XorStr("indicators")][XorStr("showFlashDuration")] = visual.indicators.showFlashDuration;

		CHAMS_JSON(enemyChamsVisible, "enemyChamsVisible", color1)

		std::remove(configPath.c_str());

		std::ofstream file;

		file.open(configPath.c_str(), std::ios_base::app);

		Json::StreamWriterBuilder builder;

		builder["commentStyle"] = "None";
		builder["indentation"] = "   "; 

		std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

		writer->write(config, &file);

		file.close();

#ifdef _DEBUG
		common::ps(XorStr("config::saveVisualConfig : done"));
#endif

		VMProtectEnd();
	}
}