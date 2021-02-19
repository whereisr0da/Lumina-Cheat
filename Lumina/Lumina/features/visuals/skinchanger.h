#ifndef skinchanger_h

#define skinchanger_h

#include <string>
#include <vector>

#define SKIN_SLOT(id,side,weapon,weaponObject) \
	case (int)id: \
		 applySkin(itemDefinitionIndex, weaponObject, &(config::visual.skins.side.weapon), &info); \
	break; \

#define STICKER_SLOT(id,side,weapon,slot) \
	case (int)id: \
		switch (slot) \
		{\
		case 0:\
			return config::visual.skins.side.weapon.sticker1;\
		case 1:\
			return config::visual.skins.side.weapon.sticker2;\
		case 2:\
			return config::visual.skins.side.weapon.sticker3;\
		case 3:\
			return config::visual.skins.side.weapon.sticker4;\
		case 4:\
			return config::visual.skins.side.weapon.sticker4;\
		default:\
			break;\
		}\
	break;\

#define STICKER_GROUPE(side,slot) \
	STICKER_SLOT(WEAPON_AK47,side,ak47Skin,slot) \
	STICKER_SLOT(WEAPON_AWP,side,awpSkin,slot) \
	STICKER_SLOT(WEAPON_USP_SILENCER,side,uspSkin,slot) \
	STICKER_SLOT(WEAPON_DEAGLE,side,deagleSkin,slot) \
	STICKER_SLOT(WEAPON_SSG08,side, ssg08Skin,slot) \
	STICKER_SLOT(WEAPON_SCAR20,side, scarSkin,slot) \
	STICKER_SLOT(WEAPON_M4A1, side, m4a1Skin,slot) \
	STICKER_SLOT(WEAPON_FAMAS, side, famasSkin, slot) \
	STICKER_SLOT(WEAPON_G3SG1, side, g3sg1Skin, slot) \
	STICKER_SLOT(WEAPON_M4A1_SILENCER, side, m4a1s1Skin, slot) \
	STICKER_SLOT(WEAPON_SG556, side, sg553Skin, slot) \
	STICKER_SLOT(WEAPON_AUG, side, augSkin, slot) \
	STICKER_SLOT(WEAPON_GALILAR, side, galilSkin, slot) \
	STICKER_SLOT(WEAPON_MAC10, side, mac10Skin, slot) \
	STICKER_SLOT(WEAPON_MP5SD, side, mp5Skin, slot) \
	STICKER_SLOT(WEAPON_MP7, side, mp7Skin, slot) \
	STICKER_SLOT(WEAPON_MP9, side, mp9Skin, slot) \
	STICKER_SLOT(WEAPON_BIZON, side, ppbizonSkin, slot) \
	STICKER_SLOT(WEAPON_P90, side, p90Skin, slot) \
	STICKER_SLOT(WEAPON_UMP45, side, umpSkin, slot) \
	STICKER_SLOT(WEAPON_CZ75A, side, cz75Skin, slot) \
	STICKER_SLOT(WEAPON_ELITE, side, dualberttaSkin, slot) \
	STICKER_SLOT(WEAPON_FIVESEVEN, side, fiveSevenSkin, slot) \
	STICKER_SLOT(WEAPON_GLOCK, side, glockSkin, slot) \
	STICKER_SLOT(WEAPON_P250, side, p250Skin, slot) \
	STICKER_SLOT(WEAPON_TEC9, side, tec9Skin, slot) \
	STICKER_SLOT(WEAPON_REVOLVER, side, revolverSkin, slot) \


// don't know why, but EU csgo version has two usp and cz id
#define SKIN_GROUPE(side,weaponObject) \
	SKIN_SLOT(WEAPON_AK47,side,ak47Skin,weaponObject) \
	SKIN_SLOT(WEAPON_AWP,side,awpSkin,weaponObject) \
	SKIN_SLOT(WEAPON_USP_SILENCER,side,uspSkin,weaponObject) \
	SKIN_SLOT(262205,side,uspSkin,weaponObject) \
	SKIN_SLOT(WEAPON_DEAGLE,side,deagleSkin,weaponObject) \
	SKIN_SLOT(WEAPON_SSG08,side, ssg08Skin,weaponObject) \
	SKIN_SLOT(WEAPON_SCAR20,side, scarSkin,weaponObject) \
	SKIN_SLOT(WEAPON_M4A1, side, m4a1Skin, weaponObject) \
	SKIN_SLOT(WEAPON_FAMAS, side, famasSkin, weaponObject) \
	SKIN_SLOT(WEAPON_G3SG1, side, g3sg1Skin, weaponObject) \
	SKIN_SLOT(WEAPON_M4A1_SILENCER, side, m4a1s1Skin, weaponObject) \
	SKIN_SLOT(WEAPON_SG556, side, sg553Skin, weaponObject) \
	SKIN_SLOT(WEAPON_AUG, side, augSkin, weaponObject) \
	SKIN_SLOT(WEAPON_GALILAR, side, galilSkin, weaponObject) \
	SKIN_SLOT(WEAPON_MAC10, side, mac10Skin, weaponObject) \
	SKIN_SLOT(WEAPON_MP5SD, side, mp5Skin, weaponObject) \
	SKIN_SLOT(WEAPON_MP7, side, mp7Skin, weaponObject) \
	SKIN_SLOT(WEAPON_MP9, side, mp9Skin, weaponObject) \
	SKIN_SLOT(WEAPON_BIZON, side, ppbizonSkin, weaponObject) \
	SKIN_SLOT(WEAPON_P90, side, p90Skin, weaponObject) \
	SKIN_SLOT(WEAPON_UMP45, side, umpSkin, weaponObject) \
	SKIN_SLOT(WEAPON_CZ75A, side, cz75Skin, weaponObject) \
	SKIN_SLOT(262207, side, cz75Skin, weaponObject) \
	SKIN_SLOT(WEAPON_ELITE, side, dualberttaSkin, weaponObject) \
	SKIN_SLOT(WEAPON_FIVESEVEN, side, fiveSevenSkin, weaponObject) \
	SKIN_SLOT(WEAPON_GLOCK, side, glockSkin, weaponObject) \
	SKIN_SLOT(WEAPON_P250, side, p250Skin, weaponObject) \
	SKIN_SLOT(WEAPON_TEC9, side, tec9Skin, weaponObject) \
	SKIN_SLOT(WEAPON_REVOLVER, side, revolverSkin, weaponObject) \


namespace skinchanger {

	extern std::vector<std::string> playerModels;
	extern std::vector<std::string> knifeModelNames;

	extern bool updateSkin;

	void init();

	void frameStageNotify(int frameStage);

	void applyWeaponSkins();

	void applyPlayerModel(int frameStage);
}

#endif // !skinchanger_h