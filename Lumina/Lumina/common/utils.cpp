#include "utils.h"

#include "../sdk/interfaces.h"
#include "common.h"
//#include "includes.h"

#include <algorithm>
#include <xutility>

std::vector<paint_kit> utils::getSkinsInfo() {

	// from : aristoise

	std::vector<paint_kit> skins = std::vector<paint_kit>();
	/*
	const auto V_UCS2ToUTF8 = static_cast<int(*)(const wchar_t* ucs2, char* utf8, int len)>( interfaces::UCS2ToUTF8 );
	const auto sig_address = (DWORD*)interfaces::itemSchema;
	const auto item_system_offset = *reinterpret_cast<std::int32_t*>(sig_address + 1);
	const auto item_system_fn = reinterpret_cast<CCStrike15ItemSystem * (*)()>(sig_address + 5 + item_system_offset);
	
	const auto item_schema = (CCStrike15ItemSchema*)(uintptr_t(item_system_fn()) + sizeof(void*));
	{
		const auto get_paint_kit_definition_offset = *(int*)(sig_address + 11 + 1);
		//const auto get_paint_kit_definition_fn = reinterpret_cast<paint_kit_t * (__thiscall*)(CCStrike15ItemSchema*, int)>(sig_address + 11 + 5 + get_paint_kit_definition_offset);
		//const auto start_element_offset = *reinterpret_cast<std::intptr_t*>(std::uintptr_t(get_paint_kit_definition_fn) + 8 + 2);
		//const auto head_offset = start_element_offset - 12;
		//const auto map_head = reinterpret_cast<head_t<int, paint_kit_t*>*>(std::uintptr_t(item_schema) + head_offset);
		
		
		for (auto i = 0; i <= map_head->last_element; ++i) {
			
			const auto paint_kit = map_head->memory[i].value;
			
			if (paint_kit->id == 9001)
				continue;
			
			const auto wide_name = interfaces::localize->Find(paint_kit->item_name.buffer + 1);
			char name[256];

			V_UCS2ToUTF8(wide_name, name, sizeof(name));

			if (paint_kit->id < 10000)
				skins.push_back({ paint_kit->id, name });

		}
		
		std::sort(skins.begin(), skins.end());
	}*/

	return skins;
}

bool utils::precacheModel(const char* szModelName)
{
	VMProtectBeginMutation("utils::precacheModel");

	// thx to : https://www.unknowncheats.me/forum/counterstrike-global-offensive/214919-precache-models.html

	INetworkStringTable* m_pModelPrecacheTable = interfaces::clientStringTableContainer->FindTable(XorStr("modelprecache"));

	if (m_pModelPrecacheTable)
	{
		interfaces::modelInfo->FindOrLoadModel(szModelName);

		int idx = m_pModelPrecacheTable->AddString(false, szModelName);

		if (idx == -1)
			return false;
	}

	VMProtectEnd();

	return true;
}

bool utils::getEntityBox(Entity* ent, box& in) {

	VMProtectBeginMutation("utils::getEntityBox");

	// from : aristoise

	Vector origin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	origin = ent->getAbsoluteOrigin();
	min = ((ICollideable*)ent->GetCollideable())->OBBMins() + origin;
	max = ((ICollideable*)ent->GetCollideable())->OBBMaxs() + origin;

	Vector points[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	if (!interfaces::debugOverlay->WorldToScreen(points[3], flb) || !interfaces::debugOverlay->WorldToScreen(points[5], brt)
		|| !interfaces::debugOverlay->WorldToScreen(points[0], blb) || !interfaces::debugOverlay->WorldToScreen(points[4], frt)
		|| !interfaces::debugOverlay->WorldToScreen(points[2], frb) || !interfaces::debugOverlay->WorldToScreen(points[1], brb)
		|| !interfaces::debugOverlay->WorldToScreen(points[6], blt) || !interfaces::debugOverlay->WorldToScreen(points[7], flt))
		return false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	for (int i = 1; i < 8; i++) {
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	in.x = (int)left;
	in.y = (int)top;
	in.w = int(right - left);
	in.h = int(bottom - top);

	VMProtectEnd();

	return true;
}