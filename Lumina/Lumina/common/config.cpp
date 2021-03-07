#include "config.h"

#include "common.h"
#include "../ui/menu.h"
#include "json/json.h"

#include <fstream>

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
		BOOL_WRITE(cheats.optimization, config[XorStr("optimization")])

		BOOL_WRITE(cheats.backtrack, config[XorStr("backtrack")])
		FLOAT_WRITE(cheats.backtrackVisibility, config[XorStr("backtrackVisibility")])
		FLOAT_WRITE(cheats.backtrackTime, config[XorStr("backtrackTime")])

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
		config[XorStr("optimization")] = cheats.optimization;

		config[XorStr("backtrack")] = cheats.backtrack;
		config[XorStr("backtrackVisibility")] = cheats.backtrackVisibility;
		config[XorStr("backtrackTime")] = cheats.backtrackTime;

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
		COLOR_JSON_READ(visual.enemyEsp.espColor, config[XorStr("enemyEsp")][XorStr("espColor")])

		BOOL_WRITE(visual.glow.enable, config[XorStr("glow")][XorStr("enable")]);
		FLOAT_WRITE(visual.glow.bloom, config[XorStr("glow")][XorStr("bloom")]);
		BOOL_WRITE(visual.glow.onlyIfDead, config[XorStr("glow")][XorStr("onlyIfDead")])

		COLOR_JSON_READ(visual.glow.glowColor, config[XorStr("glow")][XorStr("glowColor")])

		BOOL_WRITE(visual.skins.enable, config[XorStr("skins")][XorStr("enable")]);

		SKIN_COLLECTION_JSON_READ(ctSkins, "ctSkins")

		//config::visual.skins.ctSkins.knifeId
		INT_WRITE(visual.skins.ctSkins.knifeId, config[XorStr("skins")][XorStr("ctSkins")][XorStr("knifeId")])
		INT_WRITE(visual.skins.ctSkins.knifePaint, config[XorStr("skins")][XorStr("ctSkins")][XorStr("knifePaint")])

		SKIN_COLLECTION_JSON_READ(tSkins, "tSkins")

		INT_WRITE(visual.skins.tSkins.knifeId, config[XorStr("skins")][XorStr("tSkins")][XorStr("knifeId")])
		INT_WRITE(visual.skins.tSkins.knifePaint, config[XorStr("skins")][XorStr("tSkins")][XorStr("knifePaint")])

		BOOL_WRITE(visual.showSpectators, config[XorStr("showSpectators")]);
		BOOL_WRITE(visual.spreadCircle.enable, config[XorStr("spreadCircle")][XorStr("enable")]);
		FLOAT_WRITE(visual.spreadCircle.min, config[XorStr("spreadCircle")][XorStr("min")]);
		BOOL_WRITE(visual.indicators.showFlashDuration, config[XorStr("indicators")][XorStr("showFlashDuration")]);

		CHAMS_JSON_READ(enemyChamsVisible, "enemyChamsVisible", color1)
		CHAMS_JSON_READ(enemyChamsBacktrack, "enemyChamsBacktrack", color1)
		CHAMS_JSON_READ(handChams, "handChams", color2)
		CHAMS_JSON_READ(sleeveChams, "sleeveChams", color3)

		BOOL_WRITE(visual.showGrenadePred, config[XorStr("showGrenadePred")]);

		BOOL_WRITE(visual.world.enable, config[XorStr("world")][XorStr("enable")]);
		COLOR_JSON_READ(visual.world.worldColor, config[XorStr("world")][XorStr("worldColor")])
		COLOR_JSON_READ(visual.world.propsColor, config[XorStr("world")][XorStr("propsColor")])

		BOOL_WRITE(visual.sky.enable, config[XorStr("sky")][XorStr("enable")]);
		INT_WRITE(visual.sky.sky, config[XorStr("sky")][XorStr("sky")]);
		COLOR_JSON_READ(visual.sky.skyColor, config[XorStr("sky")][XorStr("skyColor")])

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


		COLOR_JSON_WRITE(espColor, visual.enemyEsp.espColor)

		config[XorStr("enemyEsp")][XorStr("espColor")] = espColor;

		config[XorStr("glow")][XorStr("enable")] = visual.glow.enable;
		config[XorStr("glow")][XorStr("onlyIfDead")] = visual.glow.onlyIfDead;
		config[XorStr("glow")][XorStr("bloom")] = visual.glow.bloom;

		COLOR_JSON_WRITE(glowColor, visual.glow.glowColor)

		config[XorStr("glow")][XorStr("glowColor")] = glowColor;

		config[XorStr("skins")][XorStr("enable")] = visual.skins.enable;

		SKIN_COLLECTION_JSON(ctSkins, "ctSkins")

		config[XorStr("skins")][XorStr("ctSkins")][XorStr("knifeId")] = visual.skins.ctSkins.knifeId;
		config[XorStr("skins")][XorStr("ctSkins")][XorStr("knifePaint")] = visual.skins.ctSkins.knifePaint;

		SKIN_COLLECTION_JSON(tSkins, "tSkins")
		config[XorStr("skins")][XorStr("tSkins")][XorStr("knifeId")] = visual.skins.tSkins.knifeId;
		config[XorStr("skins")][XorStr("tSkins")][XorStr("knifePaint")] = visual.skins.tSkins.knifePaint;



		config[XorStr("showGrenadePred")] = visual.showGrenadePred;
		config[XorStr("showSpectators")] = visual.showSpectators;
		config[XorStr("spreadCircle")][XorStr("enable")] = visual.spreadCircle.enable;
		config[XorStr("spreadCircle")][XorStr("min")] = visual.spreadCircle.min;
		config[XorStr("indicators")][XorStr("showFlashDuration")] = visual.indicators.showFlashDuration;

		CHAMS_JSON(enemyChamsVisible, "enemyChamsVisible", color1, color1_)
		CHAMS_JSON(enemyChamsBacktrack, "enemyChamsBacktrack", color4, color4_)
		CHAMS_JSON(handChams, "handChams", color2, color2_)
		CHAMS_JSON(sleeveChams, "sleeveChams", color3, color3_)

		config[XorStr("world")][XorStr("enable")] = visual.world.enable;
		COLOR_JSON_WRITE(worldColor, visual.world.worldColor)
		config[XorStr("world")][XorStr("worldColor")] = worldColor;
		COLOR_JSON_WRITE(propsColor, visual.world.propsColor)
		config[XorStr("world")][XorStr("propsColor")] = propsColor;

		config[XorStr("sky")][XorStr("enable")] = visual.sky.enable;
		config[XorStr("sky")][XorStr("sky")] = visual.sky.sky;
		COLOR_JSON_WRITE(skyColor, visual.sky.skyColor)
		config[XorStr("sky")][XorStr("skyColor")] = skyColor;

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