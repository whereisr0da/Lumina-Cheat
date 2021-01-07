#include "misc.h"

#include "../../common/includes.h"
#include "../../sdk/interfaces.h"
#include "../visuals/skinchanger.h"
#include "../../ui/sound.h"
#include "../../common/game.h"
#include "../../common/common.h"

void misc::hitmarkerSound(void* event) {

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

void misc::fixSkin(void* event) {

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

float Magnitude(Vector a)
{
	return sqrt((a.x * a.x) + (a.y * a.y));
}
Vector Normalize(Vector value)
{
	float num = Magnitude(value);
	if (num != 0.f)
		return value / num;
	return Vector(0.f, 0.f, 0.f);
}
Vector ClampMagnitude(Vector vector, float maxLength)
{
	if (Magnitude(vector) > maxLength)
		return Vector(Normalize(vector).x * maxLength, Normalize(vector).y * maxLength, 0);
	return vector;
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
	moveDir = ClampMagnitude(moveDir, maxSpeed);

	cmd->sidemove = moveDir.x;
	cmd->forwardmove = moveDir.y;

	if (!(localPlayer->m_vecVelocity().Length2D() > maxSpeed + 1))
		cmd->buttons &= ~IN_SPEED;

	VMProtectEnd();
}

void vector_angles(const Vector& forward, Vector& angles)
{
	VMProtectBeginMutation("vector_angles");

	Vector view;

	if (!forward[0] && !forward[1])
	{
		view[0] = 0.0f;
		view[1] = 0.0f;
	}
	else
	{
		view[1] = atan2(forward[1], forward[0]) * 180.0f / M_PI;

		if (view[1] < 0.0f)
			view[1] += 360.0f;

		view[2] = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		view[0] = atan2(forward[2], view[2]) * 180.0f / M_PI;
	}

	angles[0] = -view[0];
	angles[1] = view[1];
	angles[2] = 0.f;

	VMProtectEnd();
}

void angle_vectors(const Vector& angles, Vector& forward)
{
	VMProtectBeginMutation("angle_vectors");

	float sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;

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

	vector_angles(velocity, direction);

	direction.y = real_view.y - direction.y;

	Vector forward;

	angle_vectors(direction, forward);


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


void misc::roundSounds(void* event) {

	VMProtectBeginMutation("misc::roundSounds");

	if (!config::visual.sounds.enable)
		return;

	auto pEvent = (IGameEvent*)event;

	if (strstr(pEvent->GetName(), XorStr("round_end"))) {

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

	else if (strstr(pEvent->GetName(), XorStr("round_start"))) {

		interfaces::surface->PlaySound(sound::sounds[config::visual.sounds.roundStartSound].c_str());
	}

	VMProtectEnd();
}

void misc::headShoot(void* event) {

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