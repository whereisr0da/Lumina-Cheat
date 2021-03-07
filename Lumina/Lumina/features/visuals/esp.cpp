#include "esp.h"
#include "../../sdk/interfaces.h"
#include "../../common/common.h"
#include "../../ui/render.h"
#include "../../ui/texture.h"

#include "../../ui/image.h"

namespace esp {

	float dormantHistory[1024];

	texture* flashedLogo = nullptr;
	texture* reloadLogo = nullptr;
	texture* scopingLogo = nullptr;

	void init() {

	}

	void paintTraverse() {

		playerEsp();
	}

	void playerEsp() {

		VMProtectBeginMutation("esp::playerEsp");

		Entity* localPlayer = game::getLocalPlayer();
		
		for (auto i = 0; i < interfaces::globals->maxClients; i++)
		{
			Entity* entity = (Entity*)interfaces::clientEntityList->GetClientEntity(i);

			// keep the order
			if (!entity)
				continue;
			// escape localplayer and non player
			if(!entity->isPlayer() || entity == localPlayer)
				continue;
			// esp only on enemies
			if(!entity->isAlive() || entity->m_iTeamNum() == localPlayer->m_iTeamNum())
				continue;
			// increase the opacity because it's dormant
			if (entity->m_bDormant() && dormantHistory[entity->index()] > 0.0f)
				dormantHistory[entity->index()] -= 4.0f;
			// reset the opacity because not dormant
			else if (!entity->m_bDormant())
				dormantHistory[entity->index()] = 255.0f;
			// don't draw the esp if opacity is null
			if (dormantHistory[entity->index()] <= 0.0f)
				continue;

			if (config::visual.enemyEsp.showOnlyIsDead && localPlayer->isAlive())
				continue;

			if (config::visual.enemyEsp.showBox)
				render::drawEntityBox(entity, config::visual.enemyEsp.espColor);

			renderEsp(entity);
		}
	
		VMProtectEnd();
	}

	void renderEsp(Entity* player) {

		VMProtectBeginMutation("esp::renderEsp");

		box playerBox;

		// get the screen box around the player
		if (!utils::getEntityBox(player, playerBox))
			return;

		int space = 5;
		int hearthBarSize = 3;
		int indicatorPadding = 14;

		std::vector<std::string> indicators = std::vector<std::string>();
		std::vector<texture*> indicatorsLogo = std::vector<texture*>();

		// setup icon textures
		if (!flashedLogo)
			flashedLogo = new texture(images::flashingData, 14, 14);
		if (!reloadLogo)
			reloadLogo = new texture(images::reloadData, 14, 14);
		if (!scopingLogo)
			scopingLogo = new texture(images::scopingData, 14, 14);

		// set esp color in function of dormant history
		config::visual.enemyEsp.espColor.SetAlpha((int)dormantHistory[player->index()]);

		if (config::visual.enemyEsp.showBox) {
			render::drawOutlinedBox(playerBox.x, playerBox.y, playerBox.w, playerBox.h, config::visual.enemyEsp.espColor);
		}

		if (config::visual.enemyEsp.showName) {

			// allocate the struct
			player_info_t* playerInfo = new player_info_t();

			if (!interfaces::engineClient->GetPlayerInfo(player->index(), playerInfo))
				goto ret;

			std::string playerName = playerInfo->name;

			if (playerName.size() > 12)
			{
				playerName.resize(12);
				playerName.append(XorStr("..."));
			}

			// detect UTF 16
			//wchar_t buffer[128];
			//wsprintfW(buffer, L"%S", playerInfo.name);
			//if (MultiByteToWideChar(CP_UTF8, 0, playerInfo.name, -1, buffer, 128) > 0)

			int nameBoxSize = 20;

			//render::drawRectangle(playerBox.x, playerBox.y - (nameBoxSize - space), playerBox.w, nameBoxSize - (space * 2), config::visual.enemyEsp.espColor);

			render::drawText(playerBox.x, playerBox.y - nameBoxSize + space, render::font, playerName, false, config::visual.enemyEsp.espColor);

			delete playerInfo;
		}

		ret:

		if (config::visual.enemyEsp.showLife) {

			if (player->m_iMaxHealth() > 0 && player->m_iHealth() > 0) {

				int factor = player->m_iHealth() / player->m_iMaxHealth();

				int maxI = 256;

				Color green = Color(0, 255, 0);

				/*

				Color red = Color(255, 0, 0);
				
				Color currentColor = Color(0, 0, 0);
				
				int r = (green.r() + ((factor / 255.0) * (red.r() - green.r())));
				int g = (green.g() + ((factor / 255.0) * (red.g() - green.g())));
				int b = (green.b() + ((factor / 255.0) * (red.b() - green.b())));

				
				currentColor.SetColor(r, g, b);*/

				render::drawRectangle(playerBox.x - space - hearthBarSize, playerBox.y, hearthBarSize, playerBox.h * factor, green);

				render::drawOutlinedBox(playerBox.x - space - hearthBarSize, playerBox.y, hearthBarSize, playerBox.h, Color(config::visual.enemyEsp.espColor, 50));
			}
		}

		if (config::visual.enemyEsp.showWeaponIcon) {

			auto weapon = (C_BaseAttributableItem*)player->getWeapon();

			if (weapon) {

				if (*weapon->m_iItemDefinitionIndex() > 0 && *weapon->m_iItemDefinitionIndex() < 50) {

					//char indexChar[1] = { (char)(weapon->itemDefinitionIndex() & 0xFF) };

					std::string icon = "";
					icon.push_back(0x7);
					icon.push_back(0x0);

					render::drawText(playerBox.x, playerBox.y + playerBox.h + space, render::icons, icon, false, config::visual.enemyEsp.espColor);
				}
			}
		}

		if (config::visual.enemyEsp.showFlashed)
		{
			if (player->m_flFlashDuration() > 0.0f)
			{
				if (config::visual.enemyEsp.showIcons)
				{
					indicatorsLogo.push_back(flashedLogo);
				}

				indicators.push_back(XorStr("FLASHED"));
			}
		}
	
		if (config::visual.enemyEsp.showScopping)
		{
			if (player->m_bIsScoped())
			{
				if (config::visual.enemyEsp.showIcons)
				{
					indicatorsLogo.push_back(scopingLogo);
				}

				indicators.push_back(XorStr("SCOPING"));
			}
		}

		if (config::visual.enemyEsp.showReload)
		{
			/*
			if (entity->getWeapon())
			{
				if (!entity->getWeapon()->m_bReloadVisuallyComplete())
				{
					if (config::visual.enemyEsp.showIcons)
					{
						drawIcons = true;
						indicatorsLogo.push_back(reloadLogo);
					}

					indicators.push_back(XorStr("RELOADING"));
				}
			}*/
		}

		if (config::visual.enemyEsp.showHasDefuser)
		{
			if (player->m_bHasDefuser())
			{
				if (config::visual.enemyEsp.showIcons)
				{

				}

				indicators.push_back(XorStr("HAS DEFUSER"));
			}
		}

		if (config::visual.enemyEsp.showPlanting)
		{
			auto weapon = (C_BaseAttributableItem*)player->getWeapon();

			if (weapon)
			{
				if (*weapon->m_iItemDefinitionIndex() == WEAPON_C4) {

					auto c4 = (DT_WeaponC4*)weapon;

					if (c4->m_bStartedArming()) {

						if (config::visual.enemyEsp.showIcons)
						{

						}

						indicators.push_back(XorStr("PLANTING"));
					}
				}
			}
		}

		if (config::visual.enemyEsp.showDefusing)
		{
			if (player->m_bIsDefusing())
			{
				if (config::visual.enemyEsp.showIcons)
				{

				}

				indicators.push_back(XorStr("DEFUSING"));
			}
		}

		if (config::visual.enemyEsp.showBomb)
		{
			if (player->hasC4())
			{
				if (config::visual.enemyEsp.showIcons)
				{

				}

				indicators.push_back(XorStr("HAS BOMB"));
			}
		}
		/*
		if (config::visual.enemyEsp.showWeaponName)
		{
			if (player->weaponData)
			{
				std::string weaponName = player->weaponData->szWeaponName;

				// remove the weapon_ string
				weaponName.erase(0, 7);

				render::drawText(playerBox.x, playerBox.y + playerBox.h + space, render::font, weaponName.c_str(), false, config::visual.enemyEsp.espColor);
			}
		}*/

		int startXTextIndicators = playerBox.x + playerBox.w + space;

		// if there are icons
		if (indicatorsLogo.size() > 0)
			startXTextIndicators += space + indicatorPadding;

		// draw indicator icons
		for (size_t i = 0; i < indicatorsLogo.size(); i++)
		{
			indicatorsLogo[i]->m_bgColor.SetAlpha((int)dormantHistory[player->index()]);
			indicatorsLogo[i]->Draw(playerBox.x + playerBox.w + space, playerBox.y + ((space + indicatorPadding) * i));
		}

		if (config::visual.enemyEsp.showIconsOnly)
			return;

		// draw indicator text
		for (size_t i = 0; i < indicators.size(); i++)
			render::drawText(startXTextIndicators, playerBox.y + ((indicatorPadding + space) * i), render::font, indicators[i], false, config::visual.enemyEsp.espColor);
	
		VMProtectEnd();
	}
}