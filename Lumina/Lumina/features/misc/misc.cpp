#include "misc.h"

#include "../../common/includes.h"
#include "../../sdk/interfaces.h"
#include "../visuals/skinchanger.h"
#include "../../ui/sound.h"
#include "../../common/game.h"
#include "../../common/common.h"
#include "../../common/events.h"

void misc::hitmarkerSound(void* event, void* eventInfo) {

	VMProtectBeginMutation("misc::hitmarkerSound");

	if (!config::visual.sounds.enable)
		return;

	auto pEvent = (IGameEvent*)event;

	if (!pEvent)
		return;

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

		interfaces::surface->PlaySound(sound::sounds[config::visual.sounds.hitmarkerSound].c_str());
		common::hitmarkerTime = 255;
		common::hitmarkerDamage = pEvent->GetInt(XorStr("dmg_health"));
	}

	VMProtectEnd();
}

void misc::fixSkin(void* event, void* eventInfo) {

	VMProtectBeginMutation("misc::fixSkin");

	auto pEvent = (IGameEvent*)event;

	auto localPlayer = game::getLocalPlayer();

	if (!localPlayer)
		return;

	int spawnedUserId = pEvent->GetInt(XorStr("userid"), -1);

	if (spawnedUserId == -1)
		return;

	auto spawnedPlayerId = interfaces::engineClient->GetPlayerForUserID(spawnedUserId);

	if (!spawnedPlayerId)
		return;

	auto spawnedPlayer = (Entity*)(interfaces::clientEntityList->GetClientEntity(spawnedPlayerId));

	if (!spawnedPlayer)
		return;

	// localPlayer is spawning
	if (spawnedPlayer == localPlayer) {

		skinchanger::updateSkin = true;

		// wait that "skin" thread refresh id's
		//while (skinchanger::updateSkin);

		//interfaces::forceUpdate();
	}

	VMProtectEnd();
}

void misc::silentWalk(void* cmd_)
{
	VMProtectBeginMutation("silentWalk");

	if (!config::cheats.silentWalk)
		return;

	CUserCmd* cmd = (CUserCmd*)cmd_;

	Vector moveDir = Vector(0.f, 0.f, 0.f);

	float maxSpeed = 130.f; //can be 134 but sometimes I make a sound, 130 works perfectly

	Entity* localPlayer = game::getLocalPlayer();

	int movetype = localPlayer->m_nMoveType();

	bool InAir = !(localPlayer->m_fFlags() & FL_ONGROUND);

	if (movetype == MOVETYPE_FLY || movetype == MOVETYPE_NOCLIP || InAir || cmd->buttons & IN_DUCK || !(cmd->buttons & IN_SPEED) /* When holding knife or bomb*/) // IN_WALK doesnt work
		return;

	moveDir.x = cmd->sidemove;
	moveDir.y = cmd->forwardmove;
	moveDir = math::ClampMagnitude(moveDir, maxSpeed);

	cmd->sidemove = moveDir.x;
	cmd->forwardmove = moveDir.y;

	if (!(localPlayer->m_vecVelocity().Length2D() > maxSpeed + 1))
		cmd->buttons &= ~IN_SPEED;

	VMProtectEnd();
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

		if (winner == team)
		{
			interfaces::surface->PlaySound(sound::sounds[config::visual.sounds.roundEndWonSound].c_str());
		}
		else if (winner != team)
		{
			interfaces::surface->PlaySound(sound::sounds[config::visual.sounds.roundEndLostSound].c_str());
		}
	}

	else if (((eventInfo*)eventInfo_)->hash == HASH("round_start")) {

		interfaces::surface->PlaySound(sound::sounds[config::visual.sounds.roundStartSound].c_str());
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

		interfaces::surface->PlaySound(sound::sounds[config::visual.sounds.headShootSound].c_str());
	}

	VMProtectEnd();
}