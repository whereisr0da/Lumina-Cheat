#include "misc.h"

#include "../../common/includes.h"
#include "../../sdk/interfaces.h"
#include "../visuals/skinchanger.h"
#include "../../ui/sound.h"
#include "../../common/game.h"
#include "../../common/common.h"
#include "../../common/events.h"
#include "voice.h"

bool misc::nameChanged = false;

void misc::hitmarkerSound(void* event, void* eventInfo) {

	VMProtectBeginMutation("misc::hitmarkerSound");

	if (!config::visual.sounds.enable)
		return;

	auto pEvent = (IGameEvent*)event;
	auto localPlayer = game::getLocalPlayer();

	if (!localPlayer || !game::isEnvironmentValid())
		return;

	int userIdAttacker = pEvent->GetInt(XorStr("attacker"), -1);

	if (userIdAttacker == -1)
		return;

	auto id = interfaces::engineClient->GetPlayerForUserID(userIdAttacker);

	if (!id)
		return;

	auto attacker = (Entity*)interfaces::clientEntityList->GetClientEntity(id);

	if (!attacker)
		return;

	if (!attacker->isPlayer())
		return;

	int userIdVictime = pEvent->GetInt(XorStr("userid"), -1);

	if (userIdVictime == -1)
		return;

	auto id2 = interfaces::engineClient->GetPlayerForUserID(userIdVictime);

	if (!id2)
		return;

	auto victime = (Entity*)(interfaces::clientEntityList->GetClientEntity(id2));

	if (!victime)
		return;

	if (!victime->isPlayer())
		return;

	if (victime == localPlayer)
		return;

	if (attacker == localPlayer) {

		int sound_index = config::visual.sounds.hitmarkerSound.index;

		if (config::visual.sounds.hitmarkerSound.random)
			sound_index = rand() % sound::sounds_short.size();

		sound::playSoundShort(sound_index);

		if (config::visual.sounds.hitmarkerSound.through_mic)
			voice::play(sound_index);

		common::hitmarkerTime = 255;
		common::hitmarkerDamage = pEvent->GetInt(XorStr("dmg_health"));
	}

	VMProtectEnd();
}

//void misc::fixSkin(void* event, void* eventInfo) {
//
//	VMProtectBeginMutation("misc::fixSkin");
//
//	auto pEvent = (IGameEvent*)event;
//
//	auto localPlayer = game::getLocalPlayer();
//
//	if (!localPlayer)
//		return;
//
//	int spawnedUserId = pEvent->GetInt(XorStr("userid"), -1);
//
//	if (spawnedUserId == -1)
//		return;
//
//	auto spawnedPlayerId = interfaces::engineClient->GetPlayerForUserID(spawnedUserId);
//
//	if (!spawnedPlayerId)
//		return;
//
//	auto spawnedPlayer = (Entity*)(interfaces::clientEntityList->GetClientEntity(spawnedPlayerId));
//
//	if (!spawnedPlayer)
//		return;
//
//	// localPlayer is spawning
//	if (spawnedPlayer == localPlayer) {
//
//		skinchanger::updateSkin = true;
//
//		// wait that "skin" thread refresh id's
//		//while (skinchanger::updateSkin);
//
//		//interfaces::forceUpdate();
//	}
//
//	VMProtectEnd();
//}

void misc::silentWalk(void* cmd_)
{
	//VMProtectBeginMutation("misc::silentWalk");

	//if (!config::cheats.silentWalk)
	//	return;

	//CUserCmd* cmd = (CUserCmd*)cmd_;

	//Vector moveDir = Vector(0.f, 0.f, 0.f);

	//float maxSpeed = 130.f; //can be 134 but sometimes I make a sound, 130 works perfectly

	//Entity* localPlayer = game::getLocalPlayer();

	//int movetype = localPlayer->m_nMoveType();

	//bool InAir = !(localPlayer->m_fFlags() & FL_ONGROUND);

	//if (movetype == MOVETYPE_FLY || movetype == MOVETYPE_NOCLIP || InAir || cmd->buttons & IN_DUCK || !(cmd->buttons & IN_SPEED) /* When holding knife or bomb*/) // IN_WALK doesnt work
	//	return;

	//moveDir.x = cmd->sidemove;
	//moveDir.y = cmd->forwardmove;
	//moveDir = math::ClampMagnitude(moveDir, maxSpeed);

	//cmd->sidemove = moveDir.x;
	//cmd->forwardmove = moveDir.y;

	//if (!(localPlayer->m_vecVelocity().Length2D() > maxSpeed + 1))
	//	cmd->buttons &= ~IN_SPEED;

	//VMProtectEnd();
}

void misc::fastStop(void* cmd)
{
	VMProtectBeginMutation("misc::fastStop");

	// code modded from legandware

	if (!config::cheats.fastStop)
		return;

	CUserCmd* m_pcmd = (CUserCmd*)cmd;

	Entity* localPlayer = game::getLocalPlayer();

	if (!(localPlayer->m_fFlags() & FL_ONGROUND))
		return;

	auto pressed_move_key = m_pcmd->buttons & IN_FORWARD || m_pcmd->buttons & IN_MOVELEFT || m_pcmd->buttons & IN_BACK || m_pcmd->buttons & IN_MOVERIGHT || m_pcmd->buttons & IN_JUMP;

	if (pressed_move_key)
		return;

	if (localPlayer->m_nMoveType() == MOVETYPE_NOCLIP || localPlayer->m_nMoveType() == MOVETYPE_LADDER)
		return;

	auto velocity = localPlayer->m_vecVelocity();

	if (!(!(m_pcmd->buttons & IN_ATTACK) && !(m_pcmd->buttons & IN_ATTACK2)) && velocity.Length2D() > 20.0f)
		goto execute;
	else if (velocity.Length2D() > 20.0f)
		goto execute;
	else
	{
		auto speed = 1.01f;

		static auto switch_move = false;

		if (switch_move)
			m_pcmd->sidemove += speed;
		else
			m_pcmd->sidemove -= speed;

		switch_move = !switch_move;

		return;
	}

execute:
	Vector direction;
	QAngle real_view = m_pcmd->viewangles;

	math::vector_angles(velocity, direction);

	direction.y = real_view.y - direction.y;

	Vector forward;

	math::angle_vectors(direction, forward);


	static auto cl_forwardspeed = (ConVar*)interfaces::console->get_convar(XorStr("cl_forwardspeed"));
	static auto cl_sidespeed = (ConVar*)interfaces::console->get_convar(XorStr("cl_sidespeed"));

	auto negative_forward_speed = -cl_forwardspeed->get_float();
	auto negative_side_speed = -cl_sidespeed->get_float();

	auto negative_forward_direction = forward * negative_forward_speed;
	auto negative_side_direction = forward * negative_side_speed;

	m_pcmd->forwardmove = negative_forward_direction.x;
	m_pcmd->sidemove = negative_side_direction.y;

	VMProtectEnd();
}

void misc::roundSounds(void* event, void* eventInfo_) {

	VMProtectBeginMutation("misc::roundSounds");

	if (!config::visual.sounds.enable)
		return;

	auto pEvent = (IGameEvent*)event;

	int sound_index = 0;

	if (((eventInfo*)eventInfo_)->hash == HASH("round_end")) {

		auto localPlayer = game::getLocalPlayer();

		if (!localPlayer)
			return;

		if (!localPlayer->m_iTeamNum())
			return;

		int team = localPlayer->m_iTeamNum();

		int winner = pEvent->GetInt(XorStr("winner"), -1);

		if (winner == -1)
			return;

		//sound_index = winner == team ? config::visual.sounds.roundEndWonSound.index : config::visual.sounds.roundEndLostSound.index;
		
		// TODO : clear this garbadge
		if (winner == team) {

			sound_index = config::visual.sounds.roundEndWonSound.index;

			if (config::visual.sounds.roundEndWonSound.random)
				sound_index = rand() % sound::sounds_short.size();

			sound::playSoundShort(sound_index);

			if (config::visual.sounds.roundEndWonSound.through_mic)
				voice::play(sound_index);
		}

		// NOTE : idk why but there is a case between winner == team and winner != team
		else if (winner != team)
		{
			sound_index = config::visual.sounds.roundEndLostSound.index;

			if (config::visual.sounds.roundEndLostSound.random)
				sound_index = rand() % sound::sounds_short.size();

			sound::playSoundShort(sound_index);

			if (config::visual.sounds.roundEndLostSound.through_mic)
				voice::play(sound_index);
		}
	}

	else if (((eventInfo*)eventInfo_)->hash == HASH("round_start")) {

		sound_index = config::visual.sounds.roundStartSound.index;

		if (config::visual.sounds.roundStartSound.random)
			sound_index = rand() % sound::sounds_short.size();

		sound::playSoundShort(sound_index);

		if (config::visual.sounds.roundStartSound.through_mic)
			voice::play(sound_index);
	}

	VMProtectEnd();
}

void misc::infiniteDuck(void* cmd)
{
	VMProtectBeginMutation("misc::infiniteDuck");

	if (!config::cheats.infinitDuck)
		return;

	((CUserCmd*)cmd)->buttons |= IN_BULLRUSH;

	VMProtectEnd();
}

void misc::hideVoteName() {

	VMProtectBeginMutation("misc::hideVoteName");

	static std::string player_name = "";
	static ConVar* name = game::getConvarNullCallback(XorStr("name"));

	if (!misc::nameChanged) {

		player_name.append(name->strString);

		name->set_value(XorStr("\n\xAD\xAD\xAD"));
		name->set_value(XorStr("MonsieurMisterMasterDrDetective"));

		misc::nameChanged = true;
	}

	else {

		name->set_value(XorStr("\n\xAD\xAD\xAD"));
		name->set_value(player_name.c_str());

		player_name.clear();

		misc::nameChanged = false;
	}

	VMProtectEnd();
}

void misc::fakeMessage(std::string mes) {

	//VMProtectBeginMutation("misc::fakeMessage");

	//static std::string player_name = "";
	//static ConVar* name = game::getConvarNullCallback(XorStr("name"));

	//if (!misc::nameChanged) {

	//	player_name.append(name->strString);

	//	name->set_value(XorStr("\n\xAD\xAD\xAD"));

	//	std::string message = XorStr("\x16\x02\x02\x09\x0A\x02\x07");

	//	message.append(mes.c_str());
	//	message.append(XorStr(" has been permanently banned from official CS:GO servers.\x01"));

	//	message.append(XorStr("\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x00"));

	//	name->set_value(message.c_str());

	//	misc::nameChanged = true;
	//}

	//else {

	//	name->set_value(XorStr("\n\xAD\xAD\xAD"));
	//	name->set_value(player_name.c_str());

	//	player_name.clear();

	//	misc::nameChanged = false;
	//}

	//VMProtectEnd();
}

void misc::copyClipboardExploit() {

	VMProtectBeginMutation("misc::copyClipboardExploit");

	const wchar_t* strData = L"﷽﷽ ﷽﷽﷽ ﷽﷽﷽ ﷽ ﷽﷽ ﷽﷽﷽ ﷽﷽﷽ ﷽ ﷽﷽ ﷽﷽ ﷽﷽﷽ ﷽﷽﷽ ﷽ ﷽﷽ ﷽﷽﷽ ﷽﷽";

	// from stackoverflow

	if (OpenClipboard(0)) {

		EmptyClipboard();
		HGLOBAL hClipboardData;
		hClipboardData = GlobalAlloc(GMEM_DDESHARE, 2 * (wcslen(strData) + 1));
		WCHAR* pchData;
		pchData = (WCHAR*)GlobalLock(hClipboardData);
		wcscpy(pchData, strData);
		GlobalUnlock(hClipboardData);
		SetClipboardData(CF_UNICODETEXT, hClipboardData);
		CloseClipboard();
	}

	VMProtectEnd();
}

void misc::voteRealer(void* event, void* eventInfo_) {

	VMProtectBeginMutation("misc::voteRealer");

	auto pEvent = (IGameEvent*)event;

	auto localPlayer = game::getLocalPlayer();

	if (!localPlayer)
		return;

	if (((eventInfo*)eventInfo_)->hash == HASH("vote_cast")) {

		int vote = pEvent->GetInt(XorStr("vote_option"));
		int id = pEvent->GetInt(XorStr("entityid"));
		int team = pEvent->GetInt(XorStr("team"));

		player_info_t player;
		interfaces::engineClient->GetPlayerInfo(id, &player);

		if (interfaces::hudChat && player.name) {

			interfaces::hudChat->ChatPrintf(0, 0, std::string("[").
				append(XorStr("\x0A")). //Light Blue
				append(localPlayer->m_iTeamNum() == team ? XorStr("Team-mates") : XorStr("Enemy")).
				append(XorStr("\x01")). //Default Color
				append(XorStr("] ")).
				append(XorStr("Voted")).
				append((vote == 0 ? std::string(XorStr(" \x04")).append(XorStr("YES")) : std::string(XorStr(" \x02")).append(XorStr("NO")))).
				append(XorStr("\x01")). //Default Color
				append(XorStr(" : [")).
				append(XorStr("\x0A")). //Light Blue
				append(player.name).
				append(XorStr("\x01")). //Default Color
				append(XorStr("]")).c_str());

			int sound_index = config::visual.sounds.voteChangedSound.index;

			if (config::visual.sounds.voteChangedSound.random)
				sound_index = rand() % sound::sounds_short.size();

			sound::playSoundShort(sound_index);

			if (config::visual.sounds.voteChangedSound.through_mic)
				voice::play(sound_index);
		}
	}

	if (((eventInfo*)eventInfo_)->hash == HASH("vote_started")) {

		int initiator = pEvent->GetInt(XorStr("initiator"));
		int team = pEvent->GetInt(XorStr("team"));
		const char* param1 = pEvent->GetString(XorStr("param1"));
		const char* issue = pEvent->GetString(XorStr("issue"));

		auto initiator_id = interfaces::engineClient->GetPlayerForUserID(initiator);

		if (!initiator_id)
			return;

		player_info_t initiator_info;
		interfaces::engineClient->GetPlayerInfo(initiator_id, &initiator_info);
		
		if (interfaces::hudChat && initiator_info.name) {

			interfaces::hudChat->ChatPrintf(0, 0, std::string("[").
				append(XorStr("\x0A")). //Light Blue
				append(localPlayer->m_iTeamNum() == team ? XorStr("Team-mates") : XorStr("Enemy")).
				append(XorStr("\x01")). //Default Color
				append(XorStr("] [")).
				append(XorStr("\x0A")). //Light Blue
				append(initiator_info.name).
				append(XorStr("\x01")). //Default Color
				append(XorStr("] Started a vote [")).
				append(XorStr("\x04")).
				append(param1).
				append(XorStr("\x01")).
				append(XorStr("] [")).
				append(issue).
				append(XorStr("]")).c_str());
		}
	}

	VMProtectEnd();
}

void misc::headShoot(void* event, void* eventInfo) {

	VMProtectBeginMutation("misc::headShoot");

	if (!config::visual.sounds.enable)
		return;

	auto pEvent = (IGameEvent*)event;

	auto localPlayer = game::getLocalPlayer();

	if (!localPlayer)
		return;

	int userIdAttacker = pEvent->GetInt(XorStr("attacker"), -1);

	if (userIdAttacker == -1)
		return;

	auto id = interfaces::engineClient->GetPlayerForUserID(userIdAttacker);

	if (!id)
		return;

	auto attacker = (Entity*)interfaces::clientEntityList->GetClientEntity(id);

	if (!attacker)
		return;

	int headshot = pEvent->GetInt(XorStr("headshot"), -1);

	if (headshot == -1)
		return;

	if (attacker == localPlayer && headshot) {

		int sound_index = config::visual.sounds.headShootSound.index;

		if (config::visual.sounds.headShootSound.random)
			sound_index = rand() % sound::sounds_short.size();

		sound::playSoundShort(sound_index);

		if (config::visual.sounds.headShootSound.through_mic)
			voice::play(sound_index);
	}

	VMProtectEnd();
}