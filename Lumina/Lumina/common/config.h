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
};

#define CHAMS_(name) \
	chams_t name; \

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
			int hitmarkerSound;
			int headShootSound;
			int roundStartSound;
			int roundEndLostSound;
			int roundEndWonSound;
			int bombPlantedSound;
			int playerKickSound;
		} sounds;

		bool showSpectators;
		bool showGrenadePred;
		bool showRadar;
	};

	struct cheat {

		bool fastStop;
		bool silentWalk;
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