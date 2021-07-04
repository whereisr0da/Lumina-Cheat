#include "menu.h"

//#include "fgui/render.hpp"
#include "../ui/zgui/dist/zgui.hh"
//#include "fgui_old/FGUI.hh"

#include "../ui/render.h"

#include "../common/includes.h"
#include "../common/input.h"
#include "../common/common.h"
#include "../common/config.h"

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <cstdint>
#include <sstream>

#include "../features/visuals/chams.h"
#include "../features/visuals/skinchanger.h"
#include "../features/misc/soundEsp.h"
#include "../features/misc/misc.h"
#include "../features/misc/voice.h"

#include "image.h"
#include "sound.h"

#include "../features/visuals/world.h"

namespace menu {

	bool visible = false;
	bool inTransition = false;

	int alphaBackground = 0;

	int alphaIntro = 0;

	bool inIntro = true;

	int frameTime = 2;

	int startSleep = 100;
	int tabIconX = 217;

	int sizeX = 572;
	int sizeY = 640;

	int lineSize = 3;
	int spaceSize = 20;
	int tabSpaceSize = 78;

	UINT32 currentFrame = 0;

	Color lightTop;
	Color lightBottom;

	Color mainTop;
	Color mainBottom;

	Color mainTabLight;
	Color mainTab;

	Color highContrast;

	std::string pseudo;


	Color textColor;

	texture logo;

	int wait = 100 * 3;

	std::vector<std::string> materialsNames = {
	};

	std::vector<std::string> sides = {

	};

	std::vector<std::string> weaponNames = {

	};

	std::vector<std::string> knifeNames = {

	};

	std::vector<std::string> modelNames = {
	};

	std::vector<skin*> tSkins = {
		&(config::visual.skins.tSkins.ak47Skin),
		&(config::visual.skins.tSkins.deagleSkin),
		&(config::visual.skins.tSkins.awpSkin),
		&(config::visual.skins.tSkins.m4a1Skin),
		&(config::visual.skins.tSkins.scarSkin),
		&(config::visual.skins.tSkins.ssg08Skin),
		&(config::visual.skins.tSkins.uspSkin),
		&(config::visual.skins.tSkins.famasSkin),
		&(config::visual.skins.tSkins.g3sg1Skin),
		&(config::visual.skins.tSkins.m4a1s1Skin),
		&(config::visual.skins.tSkins.sg553Skin),
		&(config::visual.skins.tSkins.augSkin),
		&(config::visual.skins.tSkins.galilSkin),
		&(config::visual.skins.tSkins.mac10Skin),
		&(config::visual.skins.tSkins.mp5Skin),
		&(config::visual.skins.tSkins.mp7Skin),
		&(config::visual.skins.tSkins.mp9Skin),
		&(config::visual.skins.tSkins.ppbizonSkin),
		&(config::visual.skins.tSkins.p90Skin),
		&(config::visual.skins.tSkins.umpSkin),
		&(config::visual.skins.tSkins.cz75Skin),
		&(config::visual.skins.tSkins.dualberttaSkin),
		&(config::visual.skins.tSkins.fiveSevenSkin),
		&(config::visual.skins.tSkins.glockSkin),
		&(config::visual.skins.tSkins.p250Skin),
		&(config::visual.skins.tSkins.tec9Skin),
		&(config::visual.skins.tSkins.revolverSkin),
	};

	std::vector<skin*> ctSkins = {
		&(config::visual.skins.ctSkins.ak47Skin),
		&(config::visual.skins.ctSkins.deagleSkin),
		&(config::visual.skins.ctSkins.awpSkin),
		&(config::visual.skins.ctSkins.m4a1Skin),
		&(config::visual.skins.ctSkins.scarSkin),
		&(config::visual.skins.ctSkins.ssg08Skin),
		&(config::visual.skins.ctSkins.uspSkin),
		&(config::visual.skins.ctSkins.famasSkin),
		&(config::visual.skins.ctSkins.g3sg1Skin),
		&(config::visual.skins.ctSkins.m4a1s1Skin),
		&(config::visual.skins.ctSkins.sg553Skin),
		&(config::visual.skins.ctSkins.augSkin),
		&(config::visual.skins.ctSkins.galilSkin),
		&(config::visual.skins.ctSkins.mac10Skin),
		&(config::visual.skins.ctSkins.mp5Skin),
		&(config::visual.skins.ctSkins.mp7Skin),
		&(config::visual.skins.ctSkins.mp9Skin),
		&(config::visual.skins.ctSkins.ppbizonSkin),
		&(config::visual.skins.ctSkins.p90Skin),
		&(config::visual.skins.ctSkins.umpSkin),
		&(config::visual.skins.ctSkins.cz75Skin),
		&(config::visual.skins.ctSkins.dualberttaSkin),
		&(config::visual.skins.ctSkins.fiveSevenSkin),
		&(config::visual.skins.ctSkins.glockSkin),
		&(config::visual.skins.ctSkins.p250Skin),
		&(config::visual.skins.ctSkins.tec9Skin),
		&(config::visual.skins.ctSkins.revolverSkin),
	};

	/*
	std::vector<skin*> chams = {
		&(config::visual.enemyChamsVisible.),
		&(config::visual.skins.tSkins.deagleSkin),
		&(config::visual.skins.tSkins.awpSkin),
		&(config::visual.skins.tSkins.m4a1Skin),
		&(config::visual.skins.tSkins.scarSkin),
		&(config::visual.skins.tSkins.ssg08Skin),
		&(config::visual.skins.tSkins.uspSkin),
	};*/


	int currentSide = 0;

	int currentSkin = 0;

	std::vector<std::string> skinsName = std::vector<std::string>();

	std::vector<zgui::multi_select_item> espIndicators = {

	};

	std::vector<zgui::multi_select_item> worldIndicator = {

	};

	void* currentTabDrawFunction;

	void init() {

		VMProtectBeginMutation("menu::init");

		logo = texture(images::logoData, 206, 36);

		lightTop = Color(134, 44, 63, 255);
		lightBottom = Color(150, 51, 126, 255);

		mainTop = Color(115, 3, 26, 255);
		mainBottom = Color(124, 0, 93, 255);

		mainTabLight = Color(104, 51, 76, 255);
		mainTab = Color(69, 0, 32, 255);

		highContrast = Color(48, 0, 15, 255);

		textColor = Color(255,255,255,255);

		currentTabDrawFunction = &drawSkinTab;

		std::vector<paint_kit> skins = utils::getSkinsInfo();

		for (size_t i = 0; i < skins.size(); i++)
		{
			std::string name = std::to_string(skins[i].id);
			name.append(" | ");
			name.append(skins[i].name);

			skinsName.push_back(name);
		}

		VECTOR_PUSH_TUPLE(espIndicators, "Ammo", &(config::visual.enemyEsp.showAmmo), tmp0, tmp0_)
		VECTOR_PUSH_TUPLE(espIndicators, "Armor", &(config::visual.enemyEsp.showArmor), tmp1, tmp1_)
		VECTOR_PUSH_TUPLE(espIndicators, "Has bomb", &(config::visual.enemyEsp.showBomb), tmp2, tmp2_)
		VECTOR_PUSH_TUPLE(espIndicators, "Cheating", &(config::visual.enemyEsp.showCheating), tmp3, tmp3_)
		VECTOR_PUSH_TUPLE(espIndicators, "Defusing", &(config::visual.enemyEsp.showDefusing), tmp4, tmp4_)
		VECTOR_PUSH_TUPLE(espIndicators, "Fake duck", &(config::visual.enemyEsp.showFakeDuck), tmp5, tmp5_)
		VECTOR_PUSH_TUPLE(espIndicators, "Flashed", &(config::visual.enemyEsp.showFlashed), tmp6, tmp6_)
		VECTOR_PUSH_TUPLE(espIndicators, "Has defuser", &(config::visual.enemyEsp.showHasDefuser), tmp7, tmp7_)
		VECTOR_PUSH_TUPLE(espIndicators, "Legit AA", &(config::visual.enemyEsp.showLegitAA), tmp8, tmp8_)
		VECTOR_PUSH_TUPLE(espIndicators, "Money", &(config::visual.enemyEsp.showMoney), tmp9, tmp9_)
		VECTOR_PUSH_TUPLE(espIndicators, "Ping", &(config::visual.enemyEsp.showPing), tmp10, tmp10_)
		VECTOR_PUSH_TUPLE(espIndicators, "Reload", &(config::visual.enemyEsp.showReload), tmp11, tmp11_)
		VECTOR_PUSH_TUPLE(espIndicators, "Scopping", &(config::visual.enemyEsp.showScopping), tmp12, tmp12_)
		VECTOR_PUSH_TUPLE(espIndicators, "Planting", &(config::visual.enemyEsp.showPlanting), tmp13, tmp13_)

		VECTOR_PUSH_TUPLE(worldIndicator, "Flash duration", &(config::visual.indicators.showFlashDuration), tmp14, tmp14_)

		VECTOR_PUSH(materialsNames, "TEXTURED", pad0)
		VECTOR_PUSH(materialsNames, "FLAT", pad1)
		VECTOR_PUSH(materialsNames, "MEHSES", pad2)
		VECTOR_PUSH(materialsNames, "METALIC", pad3)
		VECTOR_PUSH(materialsNames, "OVERLAY", pad4___)
		VECTOR_PUSH(materialsNames, "CHROME", pad5___)

		VECTOR_PUSH(sides, "CT", pad4)
		VECTOR_PUSH(sides, "T", pad5)

		VECTOR_PUSH(weaponNames, "AK47", pad6)
		VECTOR_PUSH(weaponNames, "DEAGLE", pad7)
		VECTOR_PUSH(weaponNames, "AWP", pad8)
		VECTOR_PUSH(weaponNames, "M4A1", pad9)
		VECTOR_PUSH(weaponNames, "SCAR", pad10)
		VECTOR_PUSH(weaponNames, "SSG08", pad11)
		VECTOR_PUSH(weaponNames, "USP", pad12)
			VECTOR_PUSH(weaponNames, "FAMAS", pad121)
			VECTOR_PUSH(weaponNames, "G3SG1", pad122)
			VECTOR_PUSH(weaponNames, "M4A1_SILENCER", pad123)
			VECTOR_PUSH(weaponNames, "SG556", pad124)
			VECTOR_PUSH(weaponNames, "AUG", pad125)
			VECTOR_PUSH(weaponNames, "GALILAR", pad126)
			VECTOR_PUSH(weaponNames, "MAC10", pad127)
			VECTOR_PUSH(weaponNames, "MP5SD", pad128)
			VECTOR_PUSH(weaponNames, "MP7", pad129)
			VECTOR_PUSH(weaponNames, "MP9", pad1210)
			VECTOR_PUSH(weaponNames, "BIZON", pad1211)
			VECTOR_PUSH(weaponNames, "P90", pad1212)
			VECTOR_PUSH(weaponNames, "UMP45", pad1213)
			VECTOR_PUSH(weaponNames, "CZ75A", pad1214)
			VECTOR_PUSH(weaponNames, "ELITE", pad1215)
			VECTOR_PUSH(weaponNames, "FIVESEVEN", pad1216)
			VECTOR_PUSH(weaponNames, "GLOCK", pad1217)
			VECTOR_PUSH(weaponNames, "P250", pad1218)
			VECTOR_PUSH(weaponNames, "TEC9", pad1219)
			VECTOR_PUSH(weaponNames, "REVOLVER", pad1220)


		VECTOR_PUSH(knifeNames, "Default T", pad13)
		VECTOR_PUSH(knifeNames, "Default CT", pad14)
		VECTOR_PUSH(knifeNames, "Bayonet", pad15)
		VECTOR_PUSH(knifeNames, "M9 Bayonet", pad16)
		VECTOR_PUSH(knifeNames, "Karambit", pad17)
		VECTOR_PUSH(knifeNames, "Bowie", pad18)
		VECTOR_PUSH(knifeNames, "Butterfly", pad19)
		VECTOR_PUSH(knifeNames, "Falchion", pad20)
		VECTOR_PUSH(knifeNames, "Flip", pad21)
		VECTOR_PUSH(knifeNames, "Tactical", pad22)
		VECTOR_PUSH(knifeNames, "Push", pad23)
		VECTOR_PUSH(knifeNames, "Jackknife", pad24)
		VECTOR_PUSH(knifeNames, "Stiletto", pad25)
		VECTOR_PUSH(knifeNames, "Widowmaker", pad26)
		VECTOR_PUSH(knifeNames, "Ursus", pad27)
		VECTOR_PUSH(knifeNames, "Outdoor", pad28)
		VECTOR_PUSH(knifeNames, "Canis", pad29)
		VECTOR_PUSH(knifeNames, "Ord", pad30)
		VECTOR_PUSH(knifeNames, "Css", pad31)


			VECTOR_PUSH(modelNames, "ctm_fbi_variantb.mdl", tmp20)
			VECTOR_PUSH(modelNames, "lara.mdl", tmp20_)
			VECTOR_PUSH(modelNames, "cortana.mdl", tmp21)
			VECTOR_PUSH(modelNames, "samus.mdl", tmp22)
			VECTOR_PUSH(modelNames, "goku.mdl", tmp23)
			VECTOR_PUSH(modelNames, "cuddleleader.mdl", tmp24)
			VECTOR_PUSH(modelNames, "viper_v1f.mdl", tmp25)
			VECTOR_PUSH(modelNames, "sas.mdl", tmp26)
			VECTOR_PUSH(modelNames, "lincoln.mdl", tmp27)
			VECTOR_PUSH(modelNames, "karachenko.mdl", tmp28)
			VECTOR_PUSH(modelNames, "gign.mdl", tmp29)
			VECTOR_PUSH(modelNames, "carrie.mdl", tmp30)
			VECTOR_PUSH(modelNames, "707.mdl", tmp31)

			VECTOR_PUSH(modelNames, "tm_phoenix_variantf.mdl", tmp40)
			VECTOR_PUSH(modelNames, "tm_phoenix_variantg.mdl", tmp41)
			VECTOR_PUSH(modelNames, "tm_phoenix_varianth.mdl", tmp42)

			/*
			


			VECTOR_PUSH(modelNames, "fbi_variantb", tmp20)
			VECTOR_PUSH(modelNames, "Lara", tmp20_)
			VECTOR_PUSH(modelNames, "fbi_variantf", tmp21)
			VECTOR_PUSH(modelNames, "fbi_variantg", tmp22)
			VECTOR_PUSH(modelNames, "fbi_varianth", tmp23)
			VECTOR_PUSH(modelNames, "sas_variantf", tmp24)
			VECTOR_PUSH(modelNames, "st6_variante", tmp25)
			VECTOR_PUSH(modelNames, "st6_variantg", tmp26)
			VECTOR_PUSH(modelNames, "st6_varianti", tmp27)
			VECTOR_PUSH(modelNames, "st6_variantk", tmp28)
			VECTOR_PUSH(modelNames, "st6_variantm", tmp29)
			VECTOR_PUSH(modelNames, "balkan_variantf", tmp31)
			VECTOR_PUSH(modelNames, "balkan_variantg", tmp32)
			VECTOR_PUSH(modelNames, "balkan_varianth", tmp33)
			VECTOR_PUSH(modelNames, "balkan_varianti", tmp34)
			VECTOR_PUSH(modelNames, "balkan_variantj", tmp35)
			VECTOR_PUSH(modelNames, "leet_variantf", tmp36)
			VECTOR_PUSH(modelNames, "leet_variantg", tmp37)
			VECTOR_PUSH(modelNames, "leet_varianth", tmp38)
			VECTOR_PUSH(modelNames, "leet_varianti", tmp39)
			VECTOR_PUSH(modelNames, "phoenix_variantf", tmp40)
			VECTOR_PUSH(modelNames, "phoenix_variantg", tmp41)
			VECTOR_PUSH(modelNames, "phoenix_varianth", tmp42)

			VECTOR_PUSH(modelNames, "st6_variantj", tmp43)
			VECTOR_PUSH(modelNames, "st6_variantl", tmp44)
			VECTOR_PUSH(modelNames, "swat_variante", tmp45)
			VECTOR_PUSH(modelNames, "swat_variantf", tmp46)
			VECTOR_PUSH(modelNames, "swat_variantg", tmp47)
			VECTOR_PUSH(modelNames, "swat_varianth", tmp48)
			VECTOR_PUSH(modelNames, "swat_varianti", tmp49)
			VECTOR_PUSH(modelNames, "swat_variantj", tmp50)
			VECTOR_PUSH(modelNames, "balkan_variantk", tmp51)
			VECTOR_PUSH(modelNames, "balkan_variantl", tmp52)
			VECTOR_PUSH(modelNames, "phoenix_varianti", tmp53)
			VECTOR_PUSH(modelNames, "professional_varf", tmp54)
			VECTOR_PUSH(modelNames, "professional_varf1", tmp55)
			VECTOR_PUSH(modelNames, "professional_varf2", tmp56)
			VECTOR_PUSH(modelNames, "professional_varf3", tmp57)
			VECTOR_PUSH(modelNames, "professional_varf4", tmp58)
			VECTOR_PUSH(modelNames, "professional_varg", tmp59)
			VECTOR_PUSH(modelNames, "professional_varh", tmp60)
			VECTOR_PUSH(modelNames, "professional_vari", tmp61)
			VECTOR_PUSH(modelNames, "professional_varj", tmp62)
						*/

#ifdef _DEBUG
		common::ps(XorStr("menu::init : done"));
#endif
		VMProtectEnd();
	}

	void skinUpdateCallback() {

	}

	void toggle()
	{
		VMProtectBeginMutation("menu::toggle");

		bool inIntro = currentFrame < startSleep + (15 * 2) + wait;

		if (!inIntro && input::get_key_info(VK_INSERT).m_state == input::PRESSED)
		{
			inTransition = !inTransition;

			visible = !visible;
		}

		VMProtectEnd();
	}

	bool playIntro = false;

	void draw()
	{
		VMProtectBeginMutation("menu::draw");

		if (currentFrame == MAXUINT32)
			currentFrame = 0;
		else
			currentFrame++;

		if (startSleep > 0)
		{
			startSleep--;
			return;
		}

		inIntro = currentFrame < startSleep + (15 * 2) + wait;

		if (currentFrame == startSleep + (15 * 2) + wait + 1)
			visible = false;

		if (inIntro)
		{
			if (!playIntro && currentFrame < startSleep + 7)
			{
				playIntro = true;
			}

			visible = inIntro;

			moduleAlpha();

			drawIntro();
		}
		else {

			if (visible)
			{
				menu::alphaBackground = 255;

				drawBackground();

				lightTop = Color(134, 44, 63, menu::alphaBackground);
				lightBottom = Color(150, 51, 126, menu::alphaBackground);

				mainTop = Color(115, 3, 26, menu::alphaBackground);
				mainBottom = Color(124, 0, 93, menu::alphaBackground);

				mainTabLight = Color(104, 51, 76, menu::alphaBackground);
				mainTab = Color(69, 0, 32, menu::alphaBackground);

				highContrast = Color(48, 0, 15, menu::alphaBackground);
			}

			// is triggered by key
			drawMenu();
		}

		VMProtectEnd();
	}

	void moduleAlpha()
	{
		VMProtectBeginMutation("menu::moduleAlpha");

		int* alpha = &alphaBackground;
		int max = 255;
		int value = 15;

		if (inIntro)
		{
			alpha = &alphaIntro;
			max = 200;
			value = 10;
		}

		if (!inTransition)
		{
			if (*alpha < max)
			{
				*alpha += value;
			}
			else if (*alpha >= max)
			{
				*alpha = max;
			}
		}
		else
		{
			if (*alpha > -1)
			{
				*alpha -= value;
			}
			else if (*alpha <= 0)
			{
				*alpha = 0;
			}
		}

		VMProtectEnd();
	}

	void drawBackground() {

		VMProtectBeginMutation("menu::drawBackground");

		int screenX, screenY;

		interfaces::engineClient->GetScreenSize(screenX, screenY);

		interfaces::surface->DrawSetColor(Color(0, 0, 0));
		interfaces::surface->DrawFilledRectFade(0, 0, screenX, screenY, 0, alphaBackground, false);

		VMProtectEnd();
	}

	void drawIntro() {

		VMProtectBeginMutation("menu::drawIntro");

		int screenX, screenY;

		interfaces::engineClient->GetScreenSize(screenX, screenY);

		interfaces::surface->DrawSetColor(Color(0, 0, 0, alphaIntro));
		interfaces::surface->DrawFilledRect(0, 0, screenX, screenY);

		logo.m_bgColor.SetAlpha(alphaIntro);

		float scale = 1;

		logo.Draw((screenX / 2) - (206 * scale / 2), (screenY / 2) - (36 * scale / 2), scale);

		VMProtectEnd();
	}

	void drawMenu() {

		VMProtectBeginMutation("menu::drawMenu");

		zgui::poll_input(XorStr("Valve001"));

		if (zgui::begin_window("", { (float)sizeX, (float)sizeY }, render::font, zgui::zgui_window_flags_none))
		{
			if (zgui::buttonWithPosition(XorStr("#showTab1"), { 74, 74 }, { (float)(spaceSize + tabIconX + lineSize ), (float)(spaceSize + lineSize )})) {
				currentTabDrawFunction = &drawSkinTab;
			}

			if (zgui::buttonWithPosition(XorStr("#showTab2"), { 74, 74 }, { (float)(spaceSize + tabIconX + lineSize + (74 * 1)), (float)(spaceSize + lineSize )})) {
				currentTabDrawFunction = &drawVisualTab;
			}

			if (zgui::buttonWithPosition(XorStr("#showTab3"), { 74, 74 }, { (float)(spaceSize + tabIconX + lineSize + (74 * 2)), (float)(spaceSize + lineSize )})) {
				currentTabDrawFunction = &drawSound;
			}

			if (zgui::buttonWithPosition(XorStr("#showTab4"), { 74, 74 }, { (float)(spaceSize + tabIconX + lineSize + (74 * 3)), (float)(spaceSize + lineSize) })) {
				currentTabDrawFunction = &drawMiscTab;
			}

			// reset pos

			zgui::setMousePos((float)menu::spaceSize + 20.0f, (float)(menu::spaceSize + menu::tabSpaceSize) + 22.0f);

			__asm {
				call currentTabDrawFunction
			}

			zgui::end_window();
		}

		VMProtectEnd();
	}


	void drawVisualTab() {

		VMProtectBeginMutation("menu::drawVisualTab");

		// esp

		float x = (float)menu::spaceSize + 20.0f;
		float y = (float)(menu::spaceSize + menu::tabSpaceSize) + 22.0f;

		zgui::checkbox(XorStr("Show box#useEsp"), config::visual.enemyEsp.showBox);

		zgui::setMousePos(x + 100, y);

		zgui::color espColor = zgui::color();

		espColor.r = config::visual.enemyEsp.espColor.r();
		espColor.g = config::visual.enemyEsp.espColor.g();
		espColor.b = config::visual.enemyEsp.espColor.b();
		espColor.a = config::visual.enemyEsp.espColor.a();

		if(zgui::colorpicker(XorStr("Esp color#espColor"), espColor))

			config::visual.enemyEsp.espColor.SetColor(espColor.r, espColor.g, espColor.b, espColor.a);

		zgui::setMousePos(x + 200, y);

		zgui::checkbox(XorStr("Show if dead#useEspif"), config::visual.enemyEsp.showOnlyIsDead);

		zgui::setMousePos(x + 300, y);

		zgui::checkbox(XorStr("Show life#useEspLife"), config::visual.enemyEsp.showLife);

		zgui::setMousePos(x + 400, y);

		zgui::checkbox(XorStr("Show name#useEspName"), config::visual.enemyEsp.showName);

		zgui::setMousePos(x, y + 50);

		zgui::multi_combobox(XorStr("Show indicators#useEspIndicators"), espIndicators);

		zgui::setMousePos(x + 100, y + 50);

		zgui::checkbox(XorStr("Show icons#useEspicon"), config::visual.enemyEsp.showIcons);

		zgui::setMousePos(x + 200, y + 50);

		zgui::checkbox(XorStr("Show weapon name#swn"), config::visual.enemyEsp.showWeaponName);

		zgui::setMousePos(x + 300, y + 50);

		zgui::checkbox(XorStr("Show weapon icon#swi"), config::visual.enemyEsp.showWeaponIcon);


		// chams

		zgui::setMousePos(x, y + 100);

		zgui::checkbox(XorStr("Show chams#useChams"), config::visual.enemyChamsVisible.enable);

		zgui::setMousePos(x + 100, y + 100);

		zgui::color chamsColor = zgui::color();

		chamsColor.r = config::visual.enemyChamsVisible.color.r();
		chamsColor.g = config::visual.enemyChamsVisible.color.g();
		chamsColor.b = config::visual.enemyChamsVisible.color.b();
		chamsColor.a = config::visual.enemyChamsVisible.color.a();

		if(zgui::colorpicker(XorStr("Chams color#chamsColor"), chamsColor))
			config::visual.enemyChamsVisible.color.SetColor(chamsColor.r, chamsColor.g, chamsColor.b, chamsColor.a);

		zgui::setMousePos(x + 200, y + 100);

		zgui::combobox(XorStr("Material#material"), materialsNames, config::visual.enemyChamsVisible.material);

		zgui::setMousePos(x + 300, y + 100);

		zgui::checkbox(XorStr("Use rainbow color#rainbow"), config::visual.enemyChamsVisible.rainbowColor);

		zgui::setMousePos(x + 400, y + 100);

		zgui::checkbox(XorStr("Through wall#throughWall"), config::visual.enemyChamsVisible.throughWall);

		zgui::setMousePos(x + 500, y + 100);

		zgui::checkbox(XorStr("Through wall only if dead#throughWallonlyifdead"), config::visual.enemyChamsVisible.throughWallOnlyIfDead);

		// overlay chams

		zgui::setMousePos(x, y + 150);

		zgui::checkbox(XorStr("Show overlay#useChamsoverlay"), config::visual.enemyChamsVisible.enableOverlay);

		zgui::setMousePos(x + 100, y + 150);

		zgui::color overlaychamsColor = zgui::color();

		overlaychamsColor.r = config::visual.enemyChamsVisible.overlayColor.r();
		overlaychamsColor.g = config::visual.enemyChamsVisible.overlayColor.g();
		overlaychamsColor.b = config::visual.enemyChamsVisible.overlayColor.b();
		overlaychamsColor.a = config::visual.enemyChamsVisible.overlayColor.a();

		if (zgui::colorpicker(XorStr("Overlay color#chamsColorOverlay"), overlaychamsColor))
			config::visual.enemyChamsVisible.overlayColor.SetColor(overlaychamsColor.r, overlaychamsColor.g, overlaychamsColor.b, overlaychamsColor.a);

		zgui::setMousePos(x + 200, y + 150);

		zgui::combobox(XorStr("Material#materialOverlay"), materialsNames, config::visual.enemyChamsVisible.overlayMaterial);

		zgui::setMousePos(x + 300, y + 150);

		zgui::checkbox(XorStr("Use rainbow color#rainbowOverlay"), config::visual.enemyChamsVisible.overlayRainbowColor);





		// glow

		zgui::setMousePos(x, y + 200);

		zgui::checkbox(XorStr("Show glow#useGlow"), config::visual.glow.enable);

		zgui::setMousePos(x + 100, y + 200);

		zgui::color glowColor = zgui::color();

		glowColor.r = config::visual.glow.glowColor.r();
		glowColor.g = config::visual.glow.glowColor.g();
		glowColor.b = config::visual.glow.glowColor.b();
		glowColor.a = config::visual.glow.glowColor.a();

		if(zgui::colorpicker(XorStr("Glow color#glowColor"), glowColor))
			config::visual.glow.glowColor.SetColor(glowColor.r, glowColor.g, glowColor.b, glowColor.a);

		zgui::setMousePos(x + 200, y + 200);

		zgui::checkbox(XorStr("Show if dead#useGlowIfDead"), config::visual.glow.onlyIfDead);

		zgui::setMousePos(x + 300, y + 200);

		zgui::slider_float(XorStr("Bloom#glowBloom"), 0, 1, config::visual.glow.bloom);

		// hands

		zgui::setMousePos(x, y + 250);

		zgui::checkbox(XorStr("Hand chams#useChamsHand"), config::visual.handChams.enable);

		zgui::setMousePos(x + 100, y + 250);

		zgui::color chamsColor2 = zgui::color();

		chamsColor2.r = config::visual.handChams.color.r();
		chamsColor2.g = config::visual.handChams.color.g();
		chamsColor2.b = config::visual.handChams.color.b();
		chamsColor2.a = config::visual.handChams.color.a();

		if(zgui::colorpicker(XorStr("Chams color#chamsColorHand"), chamsColor2))
			config::visual.handChams.color.SetColor(chamsColor2.r, chamsColor2.g, chamsColor2.b, chamsColor2.a);

		zgui::setMousePos(x + 200, y + 250);

		zgui::combobox(XorStr("Material#materialHand"), materialsNames, config::visual.handChams.material);


		// overlay hand

		zgui::setMousePos(x, y + 300);

		zgui::checkbox(XorStr("Show overlay#useChamsoverlayHand"), config::visual.handChams.enableOverlay);

		zgui::setMousePos(x + 100, y + 300);

		zgui::color chamsColorHand = zgui::color();

		chamsColorHand.r = config::visual.handChams.overlayColor.r();
		chamsColorHand.g = config::visual.handChams.overlayColor.g();
		chamsColorHand.b = config::visual.handChams.overlayColor.b();
		chamsColorHand.a = config::visual.handChams.overlayColor.a();

		if (zgui::colorpicker(XorStr("Overlay color#chamsColorOverlayHand"), chamsColorHand))
			config::visual.handChams.overlayColor.SetColor(chamsColorHand.r, chamsColorHand.g, chamsColorHand.b, chamsColorHand.a);

		zgui::setMousePos(x + 200, y + 300);

		zgui::combobox(XorStr("Material#materialHandOverlay"), materialsNames, config::visual.handChams.overlayMaterial);

		zgui::setMousePos(x + 300, y + 300);

		zgui::checkbox(XorStr("Use rainbow color#rainbowOverlayHand"), config::visual.handChams.overlayRainbowColor);



		// Steeve


		zgui::setMousePos(x, y + 350);

		zgui::checkbox(XorStr("Steeves chams#useSteeves"), config::visual.sleeveChams.enable);

		zgui::setMousePos(x + 100, y + 350);

		zgui::color chamsColor3 = zgui::color();

		chamsColor3.r = config::visual.sleeveChams.color.r();
		chamsColor3.g = config::visual.sleeveChams.color.g();
		chamsColor3.b = config::visual.sleeveChams.color.b();
		chamsColor3.a = config::visual.sleeveChams.color.a();

		if (zgui::colorpicker(XorStr("Chams color#chamsColorSteeves"), chamsColor3))
			config::visual.sleeveChams.color.SetColor(chamsColor3.r, chamsColor3.g, chamsColor3.b, chamsColor3.a);

		zgui::setMousePos(x + 200, y + 350);

		zgui::combobox(XorStr("Material#materialSteeves"), materialsNames, config::visual.sleeveChams.material);

		// overlay Steeve

		zgui::setMousePos(x, y + 400);

		zgui::checkbox(XorStr("Show overlay#useChamsovSteeve"), config::visual.sleeveChams.enableOverlay);

		zgui::setMousePos(x + 100, y + 400);

		zgui::color chamsColorSteeve = zgui::color();

		chamsColorSteeve.r = config::visual.sleeveChams.overlayColor.r();
		chamsColorSteeve.g = config::visual.sleeveChams.overlayColor.g();
		chamsColorSteeve.b = config::visual.sleeveChams.overlayColor.b();
		chamsColorSteeve.a = config::visual.sleeveChams.overlayColor.a();

		if (zgui::colorpicker(XorStr("Overlay color#chamsColorOverSteeve"), chamsColorSteeve))
			config::visual.sleeveChams.overlayColor.SetColor(chamsColorSteeve.r, chamsColorSteeve.g, chamsColorSteeve.b, chamsColorSteeve.a);

		zgui::setMousePos(x + 200, y + 400);

		zgui::combobox(XorStr("Material#materialSteeveOverlay"), materialsNames, config::visual.sleeveChams.overlayMaterial);

		zgui::setMousePos(x + 300, y + 400);

		zgui::checkbox(XorStr("Use rainbow color#rainbowOverSteeve"), config::visual.sleeveChams.overlayRainbowColor);





		// backtrack chams

		zgui::setMousePos(x, y + 450);

		zgui::checkbox(XorStr("Show backtrack#useChamsbacktrack"), config::visual.enemyChamsBacktrack.enable);

		zgui::setMousePos(x + 100, y + 450);

		zgui::color chamsColor5 = zgui::color();

		chamsColor5.r = config::visual.enemyChamsBacktrack.color.r();
		chamsColor5.g = config::visual.enemyChamsBacktrack.color.g();
		chamsColor5.b = config::visual.enemyChamsBacktrack.color.b();
		chamsColor5.a = config::visual.enemyChamsBacktrack.color.a();

		if (zgui::colorpicker(XorStr("Chams color#chamsColorbacktrack"), chamsColor5))
			config::visual.enemyChamsBacktrack.color.SetColor(chamsColor5.r, chamsColor5.g, chamsColor5.b, chamsColor5.a);

		zgui::setMousePos(x + 200, y + 450);

		zgui::combobox(XorStr("Material#materialbacktrack"), materialsNames, config::visual.enemyChamsBacktrack.material);

		zgui::setMousePos(x + 300, y + 450);

		zgui::checkbox(XorStr("Use rainbow color#rainbowbacktrack"), config::visual.enemyChamsBacktrack.rainbowColor);

		// overlay chams

		zgui::setMousePos(x, y + 500);

		zgui::checkbox(XorStr("Show overlay#useChamsoverlaybacktrack"), config::visual.enemyChamsBacktrack.enableOverlay);

		zgui::setMousePos(x + 100, y + 500);

		zgui::color overlaychamsColor7 = zgui::color();

		overlaychamsColor7.r = config::visual.enemyChamsBacktrack.overlayColor.r();
		overlaychamsColor7.g = config::visual.enemyChamsBacktrack.overlayColor.g();
		overlaychamsColor7.b = config::visual.enemyChamsBacktrack.overlayColor.b();
		overlaychamsColor7.a = config::visual.enemyChamsBacktrack.overlayColor.a();

		if (zgui::colorpicker(XorStr("Overlay color#chamsColorbacktrackOverlay"), overlaychamsColor7))
			config::visual.enemyChamsBacktrack.overlayColor.SetColor(overlaychamsColor7.r, overlaychamsColor7.g, overlaychamsColor7.b, overlaychamsColor7.a);

		zgui::setMousePos(x + 200, y + 500);

		zgui::combobox(XorStr("Material#materialOverlaybacktrack"), materialsNames, config::visual.enemyChamsBacktrack.overlayMaterial);

		zgui::setMousePos(x + 300, y + 500);

		zgui::checkbox(XorStr("Use rainbow color#rainbowOverlaybacktrack"), config::visual.enemyChamsBacktrack.overlayRainbowColor);




		VMProtectEnd();
	}

	void drawMiscTab() {

		VMProtectBeginMutation("menu::drawMiscTab");

		float x = (float)menu::spaceSize + 20.0f;
		float y = (float)(menu::spaceSize + menu::tabSpaceSize) + 22.0f;

		zgui::checkbox(XorStr("Show spread circle"), config::visual.spreadCircle.enable);
		
		zgui::setMousePos(x + 150, y);

		zgui::checkbox(XorStr("Show grenade prediction"), config::visual.showGrenadePred);

		zgui::setMousePos(x + 270, y);

		zgui::checkbox(XorStr("Show spectators"), config::visual.showSpectators);

		zgui::setMousePos(x + 350, y);

		zgui::checkbox(XorStr("Show radar"), config::visual.showRadar);

		zgui::setMousePos(x + 420, y);

		zgui::checkbox(XorStr("Fast stop"), config::cheats.fastStop);



		zgui::setMousePos(x + 520, y);

		zgui::checkbox(XorStr("Silent walk"), config::cheats.silentWalk);


		zgui::setMousePos(x + 620, y);

		zgui::checkbox(XorStr("Optimize"), config::cheats.optimization);


		zgui::setMousePos(x, y + 100);

		zgui::multi_combobox(XorStr("Indicators#worldIndicators"), worldIndicator);

		zgui::setMousePos(x, y + 50);

		zgui::slider_float(XorStr("Spread minimun#spreadCicleminimun"), 0, 100, config::visual.spreadCircle.min);


		zgui::setMousePos(x, y + 170);

		zgui::checkbox(XorStr("Infinit Duck"), config::cheats.infinitDuck);

		zgui::setMousePos(x + 150, y + 170);

		if (zgui::checkbox(XorStr("Volume ESP"), config::cheats.volumeEsp)) {

			// make sure to exec after zgui::checkbox
			if (!config::cheats.volumeEsp) {
				soundEsp::remove();
			}
		}

		zgui::setMousePos(x + 200, y + 170);

		if (zgui::button(XorStr("Copy clear cheat exploit#sgsd0grdsgdshsdhsh"), { 150, 20 })) {
			misc::copyClipboardExploit();
		}


		zgui::setMousePos(x + 360, y + 170);

		if (zgui::button(XorStr("Hide name from vote#sgsd0grdsqsfqfqsfqdhsh"), { 150, 20 })) {
			misc::hideVoteName();
		}

		zgui::setMousePos(x + 520, y + 170);

		//zgui::text_input(XorStr("Fake ban#qgqsegqsggqee00"), pseudo, 30);

		//zgui::setMousePos(x + 450, y + 170);

		//if (zgui::button(XorStr("Apply#edsgqsgg44"), { 100, 20 })) {
		//	misc::fakeMessage(pseudo);
		//}

		if (zgui::button(XorStr("Stop microphone#qsfqfsqfqf"), { 100, 20 })) {
			voice::stop();
		}

		zgui::setMousePos(x, y + 200);

		zgui::checkbox(XorStr("Backtrack"), config::cheats.backtrack);

		zgui::setMousePos(x + 100, y + 200);

		zgui::slider_float(XorStr("Backtrack time#Backtracktime"), 0, 200, config::cheats.backtrackTime);

		zgui::setMousePos(x + 300, y + 200);

		zgui::slider_float(XorStr("Backtrack visibility#Backtrackvisibility"), 0, 100, config::cheats.backtrackVisibility);





		zgui::setMousePos(x, y + 300);

		if (zgui::button(XorStr("Load visual config#dfsfsdfdsfs"), { 100, 20 })) {
			config::openVisualConfig(XorStr("config.json"));
		}

		zgui::setMousePos(x + 120, y + 300);

		if (zgui::button(XorStr("Save visual config#sdgsgesgers"), { 100, 20 })) {
			config::saveVisualConfig(XorStr("config.json"));

			config::saveCheatConfig(XorStr("config.cheat.json"));
		}

		zgui::setMousePos(x + 240, y + 300);

		if (zgui::button(XorStr("Load cheat config#dfsfsddddfdsfs"), { 100, 20 })) {
			config::openCheatConfig(XorStr("config.cheat.json"));
		}

		zgui::setMousePos(x + 360, y + 300);

		if (zgui::button(XorStr("Save cheat config#sdgsgdddesgers"), { 100, 20 })) {
			config::saveCheatConfig(XorStr("config.cheat.json"));
		}

		VMProtectEnd();
	}

	void drawSound() {

		VMProtectBeginMutation("menu::drawSound");

		float x = (float)menu::spaceSize + 20.0f;
		float y = (float)(menu::spaceSize + menu::tabSpaceSize) + 22.0f;

		zgui::checkbox(XorStr("Enable sounds#soundsEnable"), config::visual.sounds.enable);

		zgui::setMousePos(x + 100, y);

		zgui::combobox(XorStr("Hitmarker#HitmarkerSound"), sound::sounds_short, config::visual.sounds.hitmarkerSound.index);

		zgui::setMousePos(x + 100, y + 50);

		zgui::checkbox(XorStr("Random#HitmarkerSoundRandom"), config::visual.sounds.hitmarkerSound.random);

		zgui::setMousePos(x + 100, y + 75);

		zgui::checkbox(XorStr("Through mic#4524674747"), config::visual.sounds.hitmarkerSound.through_mic);



		zgui::setMousePos(x + 200, y);

		zgui::combobox(XorStr("Headshot#HeadshotrSound"), sound::sounds_short, config::visual.sounds.headShootSound.index);

		zgui::setMousePos(x + 200, y + 50);

		zgui::checkbox(XorStr("Random#RandomHeadshotrSound"), config::visual.sounds.headShootSound.random);

		zgui::setMousePos(x + 200, y + 75);

		zgui::checkbox(XorStr("Through mic#563746464"), config::visual.sounds.headShootSound.through_mic);



		zgui::setMousePos(x + 300, y);

		zgui::combobox(XorStr("Bomb Planted#BombSound"), sound::sounds_short, config::visual.sounds.bombPlantedSound.index);

		zgui::setMousePos(x + 300, y + 50);

		zgui::checkbox(XorStr("Random#BombSoundRandom"), config::visual.sounds.bombPlantedSound.random);

		zgui::setMousePos(x + 300, y + 75);

		zgui::checkbox(XorStr("Through mic#54678634524"), config::visual.sounds.bombPlantedSound.through_mic);



		zgui::setMousePos(x + 400, y);

		zgui::combobox(XorStr("Round Lost#RoundLostSound"), sound::sounds_short, config::visual.sounds.roundEndLostSound.index);

		zgui::setMousePos(x + 400, y + 50);

		zgui::checkbox(XorStr("Random#RandomRoundLostSound"), config::visual.sounds.roundEndLostSound.random);


		zgui::setMousePos(x + 400, y + 75);

		zgui::checkbox(XorStr("Through mic#54678676746"), config::visual.sounds.roundEndLostSound.through_mic);



		zgui::setMousePos(x + 500, y);

		zgui::combobox(XorStr("Round Won#RoundWonSound"), sound::sounds_short, config::visual.sounds.roundEndWonSound.index);

		zgui::setMousePos(x + 500, y + 50);

		zgui::checkbox(XorStr("Random#RandomRoundWonSound"), config::visual.sounds.roundEndWonSound.random);

		zgui::setMousePos(x + 500, y + 75);

		zgui::checkbox(XorStr("Through mic#RanThroughundWonSound"), config::visual.sounds.roundEndWonSound.through_mic);




		zgui::setMousePos(x + 600, y);

		zgui::combobox(XorStr("Round Start#RoundStartSound"), sound::sounds_short, config::visual.sounds.roundStartSound.index);

		zgui::setMousePos(x + 600, y + 50);

		zgui::checkbox(XorStr("Random#RandomRoundStartSound"), config::visual.sounds.roundStartSound.random);

		zgui::setMousePos(x + 600, y + 75);

		zgui::checkbox(XorStr("Through mic#57456h78645"), config::visual.sounds.roundStartSound.through_mic);



		zgui::setMousePos(x, y + 200);

		zgui::checkbox(XorStr("Enable Team Model#EnableTeamModel"), config::visual.teamMateModel.enable);




		zgui::setMousePos(x + 100, y + 200);

		zgui::combobox(XorStr("Model#Model__"), modelNames, config::visual.teamMateModel.id);

		zgui::setMousePos(x, y + 300);

		if (zgui::checkbox(XorStr("World Modulation#dfshdshdeshsdhsds"), config::visual.world.enable)) {
			world::worldModulation();
		}

		zgui::setMousePos(x + 100, y + 300);

		zgui::color worldColor = zgui::color();

		worldColor.r = config::visual.world.worldColor.r();
		worldColor.g = config::visual.world.worldColor.g();
		worldColor.b = config::visual.world.worldColor.b();
		worldColor.a = config::visual.world.worldColor.a();

		if (zgui::colorpicker(XorStr("World Color#WorlddColor"), worldColor)) {
			config::visual.world.worldColor.SetColor(worldColor.r, worldColor.g, worldColor.b, worldColor.a);
			world::worldModulation();
		}

		zgui::setMousePos(x + 200, y + 300);

		zgui::color proposColor = zgui::color();

		proposColor.r = config::visual.world.propsColor.r();
		proposColor.g = config::visual.world.propsColor.g();
		proposColor.b = config::visual.world.propsColor.b();
		proposColor.a = config::visual.world.propsColor.a();

		if (zgui::colorpicker(XorStr("Props Color#PropssdColor"), proposColor)) {
			config::visual.world.propsColor.SetColor(proposColor.r, proposColor.g, proposColor.b, proposColor.a);
			world::worldModulation();
		}

		zgui::setMousePos(x + 300, y + 300);

		if (zgui::checkbox(XorStr("Sky Changer#ChangerSKy"), config::visual.sky.enable)) {
			world::changeWorldSky();
		}

		zgui::setMousePos(x + 400, y + 300);

		if (zgui::combobox(XorStr("Sky#dfshgdshsdhds"), world::skyboxs, config::visual.sky.sky)) {
			world::changeWorldSky();
		}


		VMProtectEnd();
	}

	std::string inputSkin = "";
	std::string inputKnifeSkin = "";
	std::string inputWear = "";
	std::string inputSeed = "";

	std::string inputSticker1 = "";
	std::string inputSticker2 = "";
	std::string inputSticker3 = "";
	std::string inputSticker4 = "";

	bool parseInt(std::string text, int* i) {

		VMProtectBeginMutation("menu::parseInt");

		std::stringstream ss(text);

		bool process = ((ss >> *i).fail());
		bool check = (ss >> std::ws).eof();

		VMProtectEnd();

		return (!process && check);
	}

	void loadConfig() {

		VMProtectBeginMutation("menu::loadConfig");

		auto currentSkinObject = currentSide ? tSkins : ctSkins;

		LOAD_CONFIG(inputSkin, paint)
			LOAD_CONFIG(inputWear, wear)
			LOAD_CONFIG(inputSeed, seed)
			LOAD_CONFIG(inputSticker1, sticker1)
			LOAD_CONFIG(inputSticker2, sticker2)
			LOAD_CONFIG(inputSticker3, sticker3)
			LOAD_CONFIG(inputSticker4, sticker4)
			
			inputKnifeSkin = std::to_string(currentSide ? config::visual.skins.tSkins.knifePaint : config::visual.skins.ctSkins.knifePaint);


		if(config::visual.world.enable)
			world::worldModulation();

		if (config::visual.sky.enable)
			world::changeWorldSky();

		VMProtectEnd();
	}


	void updateMenuSkin() {

		VMProtectBeginMutation("menu::updateMenuSkin");

		auto currentSkinObject = currentSide ? tSkins : ctSkins;

		UPDATE_CONFIG(inputSkin, paint, tmp1)
			UPDATE_CONFIG(inputWear, wear, tmp2)
			UPDATE_CONFIG(inputSeed, seed, tmp3)
			UPDATE_CONFIG(inputSticker1, sticker1, tmp4)
			UPDATE_CONFIG(inputSticker2, sticker2, tmp5)
			UPDATE_CONFIG(inputSticker3, sticker3, tmp6)
			UPDATE_CONFIG(inputSticker4, sticker4, tmp7)

			int knifeId = 0;
		if (parseInt(inputKnifeSkin, &knifeId))
			currentSide ? config::visual.skins.tSkins.knifePaint = knifeId : config::visual.skins.ctSkins.knifePaint = knifeId;

		VMProtectEnd();
	}

	void updateSkins() {

		VMProtectBeginMutation("menu::updateSkins");

		updateMenuSkin();

		skinchanger::updateSkin = true;

		// wait that "skin" thread refresh id's
		//while (skinchanger::updateSkin);

		interfaces::forceUpdate();
		
		VMProtectEnd();
	}

	void drawSkinTab() {

		VMProtectBeginMutation("menu::drawSkinTab");

		float x = (float)menu::spaceSize + 20.0f;
		float y = (float)(menu::spaceSize + menu::tabSpaceSize) + 22.0f;

		float paddingSlider = 120;

		// weapon skins

		auto currentSkinObject = currentSide ? tSkins : ctSkins;

		zgui::checkbox(XorStr("Enable skins#useSkin"), config::visual.skins.enable);

		zgui::setMousePos(x + 100, y);

		if (zgui::combobox(XorStr("Skin side#skinSide"), sides, currentSide)) {
			loadConfig();
		}

		zgui::setMousePos(x + 200, y);

		if (zgui::combobox(XorStr("Weapon#skinWeapon"), weaponNames, currentSkin)) {
			loadConfig();
		}

		zgui::setMousePos(x + 300, y);

		if (zgui::button(XorStr("Update#updateSkin"), { 75, 20 })) {
			//updateSkins();
		}

		zgui::setMousePos(x + 400, y);

		if (zgui::button(XorStr("Force Update#updateSkinUpdate"), { 75, 20 })) {
			updateMenuSkin();
			updateSkins();
		}

		zgui::setMousePos(x, y + 50);

		//zgui::combobox("Skins#skinCollection", skinsName, currentSkinObject[currentSkin]->paint);

		//zgui::slider_int(XorStr("Skins#skinCollection"), 0, 1200, currentSkinObject[currentSkin]->paint);
		if (zgui::text_input(XorStr("Skins#skinCollection"), inputSkin, 6)) {
			updateMenuSkin();
		}

		zgui::setMousePos(x, y + 100);

		//zgui::slider_int(XorStr("Sticker1#sSticker1"), 0, 5500, currentSkinObject[currentSkin]->sticker1);

		if (zgui::text_input(XorStr("Sticker1#sSticker1"), inputSticker1, 6)) {
		updateMenuSkin();
		}

		zgui::setMousePos(x + (paddingSlider), y + 100);

		if (zgui::text_input(XorStr("Sticker2#sSticker2"), inputSticker2, 6)) {
		updateMenuSkin();
		}
		//zgui::slider_int(XorStr("Sticker2#sSticker2"), 0, 5500, currentSkinObject[currentSkin]->sticker2);

		zgui::setMousePos(x + (paddingSlider * 2), y + 100);

		if (zgui::text_input(XorStr("Sticker3#sSticker3"), inputSticker3, 6)) {
		updateMenuSkin();
		}
		//zgui::slider_int(XorStr("Sticker3#sSticker3"), 0, 5500, currentSkinObject[currentSkin]->sticker3);

		zgui::setMousePos(x + (paddingSlider * 3), y + 100);

		if (zgui::text_input(XorStr("Sticker4#sSticker4"), inputSticker4, 6)) {
		updateMenuSkin();
		}
		//zgui::slider_int(XorStr("Sticker4#sSticker4"), 0, 5500, currentSkinObject[currentSkin]->sticker4);

		zgui::setMousePos(x, y + 200);

		// can't do it because of compilation optimization
		//auto knifeId = currentSide ? config::visual.skins.tSkins.knifeId : config::visual.skins.ctSkins.knifeId;

		if(currentSide)
			zgui::combobox(XorStr("Knife model#knifeModel"), knifeNames, config::visual.skins.tSkins.knifeId);
		else 
			zgui::combobox(XorStr("Knife model#knifeModel"), knifeNames, config::visual.skins.ctSkins.knifeId);

		zgui::setMousePos(x + 100, y + 200);

		//auto knifeSkin = currentSide ? config::visual.skins.tSkins.knifePaint : config::visual.skins.ctSkins.knifePaint;

		if (zgui::text_input(XorStr("Knife skin#skinKnife"), inputKnifeSkin, 6)) {
		updateMenuSkin();
		}

		//if (currentSide)
			//zgui::slider_int(XorStr("Knife skin#skinKnife"), 0, 1000, config::visual.skins.tSkins.knifePaint);
		//else
			//zgui::slider_int(XorStr("Knife skin#skinKnife"), 0, 1000, config::visual.skins.ctSkins.knifePaint);

		// model 

		zgui::setMousePos(x + 200, y + 200);

		zgui::checkbox(XorStr("Enable model changer#useModgdsg"), config::visual.playerModel.enable);

		zgui::setMousePos(x + 400, y + 200);

		zgui::combobox(XorStr("Model#modelDD"), modelNames, config::visual.playerModel.id);

		VMProtectEnd();
	}
}