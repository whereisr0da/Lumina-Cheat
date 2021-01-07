#include "visualMisc.h"

#include "../../common/includes.h"
#include "../../common/config.h"
#include "../../sdk/interfaces.h"
#include "../../ui/render.h"
#include "../../ui/menu.h"
#include "../../common/game.h"
#include "../../common/common.h"

namespace visualMisc {

	void init() {

	}

	void watermark()
	{
		VMProtectBeginMutation("visualMisc::watermark");

		// from aristois

		int width, height;
		interfaces::engineClient->GetScreenSize(width, height);

		static int fps, old_tick_count;

		if ((interfaces::globals->tickcount - old_tick_count) > 50) {
			fps = static_cast<int>(1.f / interfaces::globals->frametime);
			old_tick_count = interfaces::globals->tickcount;
		}

		std::string barText;

		INetChannelInfo* netChannel = interfaces::engineClient->GetNetChannelInfo();

		auto localPlayer = game::getLocalPlayer();

		std::string outgoing = localPlayer ? std::to_string((int)(netChannel->GetLatency(FLOW_OUTGOING) * 1000)) : "0";

		barText.append(XorStr("Lumina"));

		if (game::isEnvironmentValid() && localPlayer) {

			ConVar* hostname = (ConVar*)interfaces::console->get_convar(XorStr("hostname"));

			if (hostname) {

				barText.append(XorStr(" | "));
				barText.append(netChannel->GetName());
				//barText.append(XorStr(" | "));
				//barText.append(interfaces::steamGameServer->BSecure() ? XorStr("VAC") : "UNPROTECTED");
			}
		}

		barText.append(XorStr(" | FPS : "));
		barText.append(std::to_string(fps));
		barText.append(XorStr(" | UP : "));
		barText.append(outgoing);
		barText.append(XorStr(" m/s"));

		int lineSize = 1;

		render::drawGradiant(width - 200, 4, 195, 20, menu::lightTop, menu::lightBottom, 255, false);
		render::drawGradiant(width - 200 + lineSize, 4 + lineSize, 195 - (lineSize * 2), 20 - (lineSize * 2), menu::mainTop, menu::mainBottom, 255, false);

		render::drawText(width - 195, 7, render::fontLight, barText.c_str(), false, Color(255, 255, 255, 255));

		VMProtectEnd();
	}
	
	int drawSpectators() {

		VMProtectBeginMutation("visualMisc::drawSpectators");

		if (!config::visual.showSpectators)
			return 0;

		auto local_player = game::getLocalPlayer();

		if (!local_player->isAlive())
			return 0;

		int spectator_index = 0;

		std::string playerList[100];

		int playerCount = 0;

		for (int i = 0; i < interfaces::globals->maxClients; i++) {

			auto entity = reinterpret_cast<Entity*>(interfaces::clientEntityList->GetClientEntity(i));

			if (!entity)
				continue;

			if (entity->m_bDormant() || entity == local_player || entity->isAlive() || !entity->isPlayer())
				continue;

			player_info_t info;
			
			interfaces::engineClient->GetPlayerInfo(i, &info);

			auto target = entity->m_hObserverTarget();

			if(!target)
				continue;

			auto spectatorTarget = reinterpret_cast<Entity*>(interfaces::clientEntityList->GetClientEntityFromHandle((uintptr_t)target));

			if(!spectatorTarget || spectatorTarget != local_player)
				continue;

			std::string name = info.name;

			if ((int)name.length() > 15) {
				name = name.substr(0, 15);
				name += "...";
			}

			playerList[playerCount++] = name;
		}

		if (playerCount == (0)) return 0;

		int width, height;

		interfaces::engineClient->GetScreenSize(width, height);

		int lineSize = 1;

		render::drawGradiant(width - 150, height / 2 - 10, 150, 10, menu::mainTop, menu::mainBottom, 255, false);

		//render::drawGradiant(width - 150 + lineSize, (height / 2 - 10) + lineSize, 150 - (lineSize * 2), 10 - (lineSize * 2), menu::mainTop, menu::mainBottom, 255, false);

		for (int i = 0; i < playerCount; i++)
		{
			std::transform(playerList[i].begin(), playerList[i].end(), playerList[i].begin(), ::tolower);

			player_info_t spectator_info;

			interfaces::engineClient->GetPlayerInfo(i, &spectator_info);

			render::drawRectangle(width - 150, height / 2 + (10 * spectator_index), 150, 10, Color(0, 0, 0, 100));

			render::drawText(width - 80, height / 2 + (10 * spectator_index), render::fontLight, playerList[i].c_str(), true, Color(255, 255, 255, 255));

			spectator_index++;
		}

		// lol ghetto
		render::drawRectangle(width - 150, height / 2 + (10 * spectator_index), 150, 4, Color(0, 0, 0, 100));
		render::drawGradiant(width - 150, height / 2 + (10 * spectator_index) + 4, 150, 3, menu::mainTop, menu::mainBottom, 255, false);

		VMProtectEnd();

		return 0;
	}

	void drawGrenadePrediction() {

		VMProtectBeginMutation("visualMisc::drawGrenadePrediction");

		if (!game::getLocalPlayer())
			return;

		static ConVar* cl_grenadepreview = (ConVar*)interfaces::console->get_convar(XorStr("cl_grenadepreview"));

		*(int*)((DWORD)&cl_grenadepreview->fnChangeCallbacks + 0xC) = NULL;

		cl_grenadepreview->set_value(config::visual.showGrenadePred);

		VMProtectEnd();
	}

	void maintainCrosshair() {

		VMProtectBeginMutation("visualMisc::maintainCrosshair");

		Entity* localPlayer = game::getLocalPlayer();

		if (localPlayer && localPlayer->isAlive()) {

			static ConVar* weapon_debug_spread_show = (ConVar*)interfaces::console->get_convar(XorStr("weapon_debug_spread_show"));

			*(int*)((DWORD)&weapon_debug_spread_show->fnChangeCallbacks + 0xC) = NULL;

			weapon_debug_spread_show->set_value(localPlayer->m_bIsScoped() || !config::visual.spreadCircle.enable ? 0 : 3);
		}

		VMProtectEnd();
	}

	void drawSpreadCircle() {

		VMProtectBeginMutation("visualMisc::drawSpreadCircle");

		if (!config::visual.spreadCircle.enable)
			return;

		Entity* localPlayer = game::getLocalPlayer();

		if (!localPlayer->isAlive())
			return;

		auto weapon = localPlayer->getWeapon();

		if (!weapon)
			return;

		auto playerFov = localPlayer->fov();

		int w, h;

		interfaces::engineClient->GetScreenSize(w, h);

		float spreadDist = ((weapon->get_inaccuracy() + weapon->get_spread()) * 320.f) / std::tan(DEG2RAD(playerFov == 0 ? 90 : playerFov) * 0.5f);
		
		float spreadRadius = spreadDist * (h / 480.f);

		float max = config::visual.spreadCircle.min;

		float alpha = ((spreadRadius / max) * 255);

		if (spreadRadius < max && (255 - alpha) > 0)
			render::drawCircle(w / 2, h / 2, static_cast<int>((spreadRadius)), 240, Color(255, 255, 255, 255 - alpha));

		VMProtectEnd();
	}

	void drawHitmarker() {

		VMProtectBeginMutation("visualMisc::drawHitmarker");

		if (!config::visual.sounds.enable || common::hitmarkerTime <= 0)
			return;

		int width, height;

		interfaces::engineClient->GetScreenSize(width, height);

		int w = width / 2;
		int h = height / 2;

		int size_x = 8;
		int size_y = 4;

		Color c = Color(255, 255, 255, common::hitmarkerTime);

		render::drawLine(w + size_x, h + size_x, w + size_y, h + size_y, c);
		render::drawLine(w - size_x, h + size_x, w - size_y, h + size_y, c);
		render::drawLine(w + size_x, h - size_x, w + size_y, h - size_y, c);
		render::drawLine(w - size_x, h - size_x, w - size_y, h - size_y, c);

		common::hitmarkerTime -= 2;

		std::string damage = std::to_string(common::hitmarkerDamage);

		render::drawText(w + 20, h + 20, render::fontBigger, damage.c_str(), true, c);

		VMProtectEnd();
	}

	void drawFlashTimer() {

		VMProtectBeginMutation("visualMisc::drawFlashTimer");

		if (!config::visual.indicators.showFlashDuration)
			return;

		Entity* localPlayer = game::getLocalPlayer();

		if (!localPlayer)
			return;

		if (!localPlayer->m_flFlashDuration() || !localPlayer->isAlive())
			return;

		float factor = localPlayer->m_flFlashAlpha() / localPlayer->m_flFlashMaxAlpha();

		int w, h;

		Color c = Color(255, 255, 255, factor * 255);

		interfaces::engineClient->GetScreenSize(w, h);

		std::string flash = XorStr("FLASHED FOR ");
		flash.append(std::to_string(factor));
		flash.append(XorStr(" SECONDES"));

		render::drawText(w / 2, (h / 2) + 25, render::fontBigger, flash.c_str(), true, c);

		int barSizeX = 150;
		int barSizeY = 10;

		int barSizeCurrent = factor * barSizeX;

		render::drawRectangle((w / 2) - (barSizeX / 2), (h / 2) + 60, barSizeCurrent, barSizeY, Color(0, 0, 0, factor * 255));

		VMProtectEnd();
	}
}
