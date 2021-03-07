#include "Entity.h"

#include "../interfaces.h"

bool Entity::hasC4() {
	
	return interfaces::hasC4(this);

	/*
	using is_c4_owner_fn = bool(__thiscall*)(Entity*);

	// cast from memory
	static auto is_c4_owner = reinterpret_cast<is_c4_owner_fn>(interfaces::baseClientDll + 0x3ADAD0);

	for (auto i = 0; i < interfaces::globals->maxClients; i++)
	{
		Entity* entity = (Entity*)interfaces::clientEntityList->GetClientEntity(i);

		if (!entity)
			continue;

		if (!entity->isPlayer())
			continue;

		if (!entity->isAlive())
			continue;

		if ((*interfaces::playerResource)->get_c4_player() == entity->index())
			return true;
	}
	return false;*/
}

bool Entity::is(hash32_t hash) {

	auto client_class = interfaces::baseClientDll->GetAllClasses();

	while (client_class) {

		const char* pszName = client_class->m_pRecvTable->table_name;

		if (FNV1a::get(pszName) == hash) 
			return client_class->m_ClassID == (this->Class() ? this->Class()->m_ClassID : -1);
		
		client_class = client_class->m_pNext;
	}

	return false;
}

C_BaseCombatWeapon* Entity::getWeapon() {

	if (!this->m_hActiveWeapon())
		return nullptr;

	auto handle = (*(DWORD*)this->m_hActiveWeapon()) & 0xFFF;

	if (!handle)
		return nullptr;

	return reinterpret_cast<C_BaseCombatWeapon*>(interfaces::clientEntityList->GetClientEntity((int)handle));
}

bool C_BaseCombatWeapon::IsKnife() {

	return getWeaponData()->iWeaponType == WEAPONTYPE_KNIFE && *((C_BaseAttributableItem*)this)->m_iItemDefinitionIndex() != WEAPON_TASER;
}