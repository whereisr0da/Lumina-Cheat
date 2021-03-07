#pragma once

#ifndef Entity_h

#define Entity_h

#include <Windows.h>

#include "../../common/vfunc.h"
#include "../netvars.h"
#include "../math/Vector.h"
#include "../math/QAngle.h"
#include "../../sdk/structs/misc.h"
#include "datamap.h"
#include "../structs/IClientEntity.h"
#include "../structs/structs.h"

#include "../../security/hash.h"

class C_BaseViewModel
{
public:

	void SendViewModelMatchingSequence(int sequence)
	{
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)this)[241](this, sequence);
	}

	void setModelIndex(int value)
	{
		*(int*)(uintptr_t(this) + 0x258) = value;
	}

	inline void setWeaponModel(const char* Filename, IClientUnknown* Weapon) {

		using original_fn = void(__thiscall*)(void*, const char*, IClientUnknown*);
		return (*(original_fn**)this)[243](this, Filename, Weapon);
	}

	OFFSET(int, m_nModelIndex, 0x258);
	OFFSET(CBaseHandle, m_hWeapon, 0x29C8);
	OFFSET(int, m_nSequence, 0x28BC);
};


class CCSWeaponData
{
public:

	virtual	~CCSWeaponData() {};

	//char		pad_vtable[ 0x4 ];		// 0x0
	char*		consoleName;			// 0x4
	char		pad_0[0xc];			// 0x8
	int32_t		iMaxClip1;				// 0x14
	int32_t		iMaxClip2;				// 0x18
	int32_t		iDefaultClip1;			// 0x1c
	int32_t		iDefaultClip2;			// 0x20
	int32_t		iPrimaryReserveAmmoMax; // 0x24
	int32_t		iSecondaryReserveAmmoMax; // 0x28
	char*		szWorldModel;			// 0x2c
	char*		szViewModel;			// 0x30
	char*		szDroppedModel;			// 0x34
	char		pad_9[0x50];			// 0x38
	char*		szHudName;				// 0x88
	char*		szWeaponName;			// 0x8c
	char		pad_11[0x2];			// 0x90
	bool		bIsMeleeWeapon;			// 0x92
	char		pad_12[0x9];			// 0x93
	float_t		flWeaponWeight;			// 0x9c
	char		pad_13[0x2c];			// 0xa0
	int32_t		iWeaponType;			// 0xcc
	int32_t		iWeaponPrice;			// 0xd0
	int32_t		iKillAward;				// 0xd4
	char		pad_16[0x4];			// 0xd8
	float_t		flCycleTime;			// 0xdc
	float_t		flCycleTimeAlt;			// 0xe0
	char		pad_18[0x8];			// 0xe4
	bool		bFullAuto;				// 0xec
	char		pad_19[0x3];			// 0xed
	int32_t		iDamage;				// 0xf0
	float_t		flArmorRatio;			// 0xf4
	int32_t		iBullets;				// 0xf8
	float_t		flPenetration;			// 0xfc
	char		pad_23[0x8];			// 0x100
	float_t		flWeaponRange;			// 0x108
	float_t		flRangeModifier;		// 0x10c
	float_t		flThrowVelocity;		// 0x110
	char		pad_26[0xc];			// 0x114
	bool		bHasSilencer;			// 0x120
	char		pad_27[0xb];			// 0x121
	char*		szBulletType;			// 0x12c
	float_t		flMaxSpeed;				// 0x130
	float_t		flMaxSpeedAlt;			// 0x134
	float		flSpread;				// 0x138
	float		flSpreadAlt;			// 0x13C
	float		flInaccuracyCrouch;		// 0x140
	float		flInaccuracyCrouchAlt;	// 0x144
	float		flInaccuracyStand;		// 0x148
	float		flInaccuracyStandAlt;	// 0x14C
	char		pad_29[0x34];			// 0x150
	int32_t		iRecoilSeed;			// 0x184
};

class DT_WeaponC4 {
public:
	bool m_bStartedArming()
	{
		return *(bool*)(uintptr_t(this) + 0x33F0);
	}
};

class C_BaseCombatWeapon // : public C_WeaponCSBase
{
public:

	//NETVAR("DT_WeaponCSBase", "m_bReloadVisuallyComplete", m_bReloadVisuallyComplete, bool);


	//NETVAR( get_next_primary_attack, float, "CBaseCombatWeapon->m_flNextPrimaryAttack" )
	//NETVAR( get_postpone_fire_ready_time, float, "CWeaponCSBase->m_flPostponeFireReadyTime" )
	//NETVAR( get_clip1, int, "CBaseCombatWeapon->m_iClip1" )
	//NETVAR( get_max_clip, int, "CBaseCombatWeapon->m_iPrimaryReserveAmmoCount" )
	//OFFSET(bool, in_reload, 0x32A5)
		//NETVAR( get_throw_time, float, "CBaseCSGrenade->m_fThrowTime" )
		//NETVAR( get_pin_pulled, bool, "CBaseCSGrenade->m_bPinPulled" )
		//NETVAR( get_world_model_handle, CBaseHandle, "CBaseCombatWeapon->m_hWeaponWorldModel" )
		//NETVAR( get_last_shot_time, float, "CWeaponCSBase->m_fLastShotTime" )	
		VFUNC(452, get_spread(), float(__thiscall*)(void*))()
		VFUNC(482, get_inaccuracy(), float(__thiscall*)(void*))()
		//VFUNC( 480, update_accuracy(), void( __thiscall* )( void* ) )( )
		VFUNC(460, getWeaponData(), CCSWeaponData*(__thiscall*)(void*))()

		bool IsKnife();

		void setViewModelIndex(int value)
		{
			*(int*)(uintptr_t(this) + 0x3234) = value;
		}

		void setWorldModelIndex(int value)
		{
			*(int*)(uintptr_t(this) + 0x3244) = value;
		}

		POFFSET(int, m_nSequence, 0x28BC);
		POFFSET(float, m_flCycle, 0xA14);

		/*
		bool is_grenade();
		int get_weapon_id();
		int get_weapon_type();
		bool is_knife();
		bool is_being_thrown();

		CCSWeaponData* get_wpn_data_safe();

		C_EconItemView* get_econ_item_view()
		{
			static auto Address = sig( "client_panorama.dll", "E8 ? ? ? ? 89 44 24 28 85 C0 0F 84 ? ? ? ? 8B C8" );
			static auto fnGetEconItemView = reinterpret_cast< C_EconItemView*( __thiscall* )( void* ) >( *reinterpret_cast< uintptr_t* >( Address + 1 ) + Address + 5 );

			return fnGetEconItemView( this );
		}*/
};


class Entity {

public:
	
	//NETVAR("DT_CSPlayer", "m_bHasDefuser", m_bHasDefuser, bool)
	//NETVAR("DT_BasePlayer", "m_vecOrigin", origin, Vector);
	NETVAR("DT_CSPlayer", "m_flSimulationTime", simulation_time, float);
	//NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", view_offset, Vector);
	NETVAR("DT_PlantedC4", "m_bBombTicking", c4_is_ticking, bool);
	NETVAR("DT_PlantedC4", "m_bBombDefused", c4_is_defused, bool);
	NETVAR("DT_PlantedC4", "m_hBombDefuser", c4_gets_defused, float);
	NETVAR("DT_PlantedC4", "m_flC4Blow", c4_blow_time, float);
	NETVAR("DT_PlantedC4", "m_flDefuseCountDown", c4_defuse_countdown, float);
	//NETVAR("CBaseEntity", "m_nModelIndex", modelIndex, unsigned)
	NETVAR("DT_CSPlayer", "m_nTickBase", get_tick_base, int);
	NETVAR("DT_CSPlayer", "m_bGunGameImmunity", m_bGunGameImmunity, bool);
	//NETVAR("DT_BasePlayer", "m_lifeState", m_lifeState, int32_t);
	//NETVAR(CHandle<c_base_combat_weapon>, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	NETVAR("DT_CSPlayer", "m_bHasHelmet", m_bHasHelmet, bool);
	NETVAR("DT_CSPlayer", "m_bHasHeavyArmor", m_bHasHeavyArmor, bool);
	NETVAR("DT_CSPlayer", "m_ArmorValue", m_ArmorValue, int);
	//NETVAR(int, m_MoveType, "DT_CSPlayer", "m_MoveType");
	//NETVAR(Vector, m_vecViewOffset, "DT_BasePlayer", "m_vecViewOffset[0]");
	//NETVAR("DT_CSPlayer", "m_bIsScoped", m_bIsScoped, bool);

	OFFSET(int, m_iHealth, 0x100);
	OFFSET(int, m_iMaxHealth, 0x29F8);

	OFFSET(Vector, m_vecOrigin, 0x138);
	OFFSET(Vector, m_vecViewOffset, 0x108);

	OFFSET(int, get_take_damage, 0x27C);
	OFFSET(bool, m_bDormant, 0xED);
	OFFSET(unsigned, m_nModelIndex, 0x258);
	OFFSET(int, m_hViewModel, 0x32F8);

	OFFSET(float, m_flFlashDuration, 0xA420);
	OFFSET(float, m_flFlashAlpha, 0xA41C - 0x8);
	OFFSET(float, m_flFlashMaxAlpha, 0xA41C);

	OFFSET(int, m_fFlags, 0x104);

	OFFSET(Vector, m_vecVelocity, 0x114);

	OFFSET(int, m_nMoveType, 0x25C);

	//NETVAR("DT_CSPlayer", "m_hObserverTarget", m_hObserverTarget, int);

	void setSpotted(bool spot)
	{
		*reinterpret_cast<bool*>(uintptr_t(this) + 0x93D) = spot;
	}

	void setModelIndex(int index)
	{
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)this)[75](this, index);
	}

	CBaseHandle m_hRagdoll() {
		return (*(DWORD*)(uintptr_t(this) + 0xA3EC)) & 0xFFF;
	}

	//NETVAR(int32_t, m_bDidSmokeEffect, "DT_BaseCSGrenadeProjectile", "m_bDidSmokeEffect");
	//NETVAR(int32_t, m_nSmokeEffectTickBegin, "DT_BaseCSGrenadeProjectile", "m_nSmokeEffectTickBegin");
	//NETVAR(Vector, m_viewPunchAngle, "DT_BasePlayer", "m_viewPunchAngle");
	//NETVAR(Vector, m_aimPunchAngle, "DT_BasePlayer", "m_aimPunchAngle");
	//NETVAR(bool, m_bUseCustomAutoExposureMin, "DT_EnvTonemapController", "m_bUseCustomAutoExposureMin");
	//NETVAR(bool, m_bUseCustomAutoExposureMax, "DT_EnvTonemapController", "m_bUseCustomAutoExposureMax");
	//NETVAR(float, m_flCustomAutoExposureMin, "DT_EnvTonemapController", "m_flCustomAutoExposureMin");
	//NETVAR(float, m_flCustomAutoExposureMax, "DT_EnvTonemapController", "m_flCustomAutoExposureMax");
	//NETVAR(float, m_flCustomBloomScale, "DT_EnvTonemapController", "m_flCustomBloomScale");
	//NETVAR("DT_CSPlayer", "m_flFlashDuration", m_flFlashDuration, float);
	//NETVAR(float, m_flFlashMaxAlpha, "DT_CSPlayer", "m_flFlashMaxAlpha");
	//NETVAR(float, m_flDuckSpeed, "DT_BaseEntity", "m_flDuckSpeed");
	//NETVAR(float, m_flDuckAmount, "DT_BaseEntity", "m_flDuckAmount");
	//NETVAR(int32_t, m_fFlags, "DT_BasePlayer", "m_fFlags");
	//NETVAR(Vector, m_vecVelocity, "DT_BasePlayer", "m_vecVelocity[0]");
	//NETVAR(int32_t, m_nTickBase, "DT_BasePlayer", "m_nTickBase");
	//NETVAR(float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime");
	//NETVAR(Vector, m_angAbsAngles, "DT_BaseEntity", "m_angAbsAngles");
	//NETVAR(float, m_lby, "DT_CSPlayer", "m_flLowerBodyYawTarget");
	//NETVAR(Vector, m_angEyeAngles, "DT_CSPlayer", "m_angEyeAngles[0]");
	//NETVAR(int, m_fEffects, "DT_BaseEntity", "m_fEffects");
	//NETVAR(float, m_flNextAttack, "CBaseCombatCharacter", "m_flNextAttack");
	
	
	unsigned long m_hObserverTarget() {
		return (*reinterpret_cast<unsigned long*>(uintptr_t(this) + 0x338C));
	}

	bool m_bIsDefusing() {
		return (*reinterpret_cast<bool*>(uintptr_t(this) + 0x3930));
	}

	bool m_bHasDefuser() {
		return (*reinterpret_cast<bool*>(uintptr_t(this) + 0xB388));
	}

	bool m_bIsScoped() {
		return (*reinterpret_cast<bool*>(uintptr_t(this) + 0x3928));
	}

	bool hasC4();
	bool is(hash32_t hash);

	CBaseHandle m_hActiveWeapon() {

		return (CBaseHandle)(uintptr_t(this) + 0x2EF8);
		//auto active_weapon = *(reinterpret_cast<DWORD*>(uintptr_t(this) + 0x2EF8)) & 0xFFF;
		//return reinterpret_cast<weapon_t*>(interfaces::clientEntityList->getClientEntity(active_weapon));
	}
	
	int* myWeapons() {
		return (reinterpret_cast<int*>(uintptr_t(this) + 0x2DE8));
	}


	C_BaseCombatWeapon* getWeapon();

	void* animation() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x4);
	}

	void* networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}

	ClientClass* Class() {
		using original_fn = ClientClass * (__thiscall*)(void*);
		return (*(original_fn**)networkable())[2](networkable());
	}


	Vector get_eye_pos() {
		return m_vecOrigin() + m_vecViewOffset();
	}

	void* GetCollideable() {
		using original_fn = void * (__thiscall*)(void*);
		return (*(original_fn**)this)[3](this);
	}

	Vector getAbsoluteOrigin() {
		__asm {
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX]
			CALL DWORD PTR DS : [EAX + 0x28]
		}
	}

	model_t* model() {
		using original_fn = model_t * (__thiscall*)(void*);
		return (*(original_fn**)animation())[8](animation());
	}


	int fov()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + 0x31E4);
	}

	bool setup_bones(matrix3x4_t* out, int max_bones, int mask, float time) {

		if (!this) {
			return false;
		}

		using original_fn = bool(__thiscall*)(void*, matrix3x4_t*, int, int, float);
		return (*(original_fn**)animation())[13](animation(), out, max_bones, mask, time);
	}

	Vector get_bone_position(int bone) {

		matrix3x4_t bone_matrices[128];

		Vector result;

		if (setup_bones(bone_matrices, 128, 256, 0.0f))
			result = Vector{ bone_matrices[bone][0][3], bone_matrices[bone][1][3], bone_matrices[bone][2][3] };
		else
			result = Vector{ };

		return result;
	}

	/*
	bool isDormant() {
		return *reinterpret_cast<bool*>(uintptr_t(this) + offset::DT_BaseEntity::m_bDormant);
	}*/

	int m_lifeState() {
		return (*reinterpret_cast<int*>(uintptr_t(this) + 0x25F));
	}

	int m_iTeamNum() {
		return (*reinterpret_cast<int*>(uintptr_t(this) + 0xF4));
	}

	bool isAlive() {
		return m_lifeState() == 0;
	}

	bool isPlayer() {

		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[157](this);
	}

	int index() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)networkable())[10](networkable());
	}

	/*
	float m_flSimulationTime() {
		return *reinterpret_cast<float*>(uintptr_t(this) + 0x268);
	}

	// from alphauc sdk : https://github.com/alphauc/sdk

	clientClass_t* clientClass() {
		using original_fn = clientClass_t * (__thiscall*)(void*);
		return (*(original_fn**)networkable())[2](networkable());
	}



	model_t* model() {
		using original_fn = model_t * (__thiscall*)(void*);
		return (*(original_fn**)animation())[8](animation());
	}

	int drawModel(int flags, uint8_t alpha) {
		using original_fn = int(__thiscall*)(void*, int, uint8_t);
		return (*(original_fn**)animation())[9](animation(), flags, alpha);
	}

	bool setup_bones(matrix_t* out, int max_bones, int mask, float time) {

		if (!this) {
			return false;
		}

		using original_fn = bool(__thiscall*)(void*, matrix_t*, int, int, float);
		return (*(original_fn**)animation())[13](animation(), out, max_bones, mask, time);
	}*/
};

/*
class Weapon {
public:
	VFUNC(457, get_wpn_data(), CCSWeaponData*(__thiscall*)(void*))()
};*/

/*
class C_BaseEntity //: public IClientEntity
{
public:
		VFUNC( 17, get_pred_desc_map(), datamap_t*( __thiscall * )( void* ) )( )

		NETVAR( get_team, int, "CBaseEntity->m_iTeamNum" )
		NETVAR( get_origin, Vector, "CBaseEntity->m_vecOrigin" )
		NETVARA( get_oldorigin, Vector, "CBaseEntity->m_vecOrigin", 0x274 )
		NETVAR( get_simtime, float, "CBaseEntity->m_flSimulationTime" )
		NETVARA( get_oldsimtime, float, "CBaseEntity->m_flSimulationTime", 4 )
		NETVAR( get_spotted, bool, "CBaseEntity->m_bSpotted" )
		NETVAR( get_model_idx, unsigned, "CBaseEntity->m_nModelIndex" )
		NETVAR( get_owner_ent, uint32, "CBaseEntity->m_hOwnerEntity" )
		NETVAR( get_rotation, QAngle, "CBaseEntity->m_angRotation" )
		OFFSET( get_take_damage, int, 0x27C )
		DATAMAPVAR( get_effects, int, "m_fEffects" )
		DATAMAPVAR( get_duck_amt, float, "m_flDuckAmount" )
		DATAMAPVAR( get_eflags, int, "m_iEFlags" )
		DATAMAPVAR( get_abs_velocity, Vector, "m_vecAbsVelocity" )
		DATAMAPVAR( get_abs_rotation, Vector, "m_angAbsRotation" )
		DATAMAPVAR( get_abs_origin, Vector, "m_vecAbsOrigin" )
		//MFUNC( set_abs_origin( Vector origin ), void( __thiscall* )( void*, const Vector& ), offsets::set_abs_origin )( origin )
		//MFUNC( is_breakable_entity(), bool( __thiscall* )( void* ), offsets::is_breakable_entity )( )
		VFUNC( 75, set_model_idx( int index ), void( __thiscall* )( void*, int ) )( index )
		NETPROP( get_rotation_prop, "CBaseEntity->m_angRotation" )


		//model_t* get_model();
	//IClientRenderable* get_renderable();
};


class C_BaseCombatCharacter : public C_BaseEntity
{
public:
	PNETVAR( get_weapons, CBaseHandle, "CBaseCombatCharacter->m_hMyWeapons" )
	PNETVAR( get_wearables, CBaseHandle, "CBaseCombatCharacter->m_hMyWearables" )
	PNETVAR( get_active_weapon, CBaseHandle, "CBaseCombatCharacter->m_hActiveWeapon" )
};

class CEconItemDefinition;
*/

class C_BaseAttributableItem
{
public:

	void PreDataUpdate(DataUpdateType_t update_type) {

		IClientNetworkable* net = (IClientNetworkable*)((Entity*)this)->networkable();
		return net->PreDataUpdate(update_type);

		//using original_fn = void(__thiscall*)(void*, int);
		//return (*(original_fn * *)e->networkable())[6](e->networkable(), update_type);
	}

	void PostDataUpdate(DataUpdateType_t update_type) {

		IClientNetworkable* net = (IClientNetworkable*)((Entity*)this)->networkable();
		return net->PostDataUpdate(update_type);
	}

	void OnDataChanged(DataUpdateType_t update_type) {

		IClientNetworkable* net = (IClientNetworkable*)((Entity*)this)->networkable();
		return net->OnDataChanged(update_type);
	}

	bool IsBaseCombatWeapon() {
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[166](this);
	}

	POFFSET(int, m_nFallbackPaintKit, 0x31C8)
	POFFSET(int, m_iAccountID, 0x2FC8)
	POFFSET(int, m_OriginalOwnerXuidHigh, 0x31C4)
	POFFSET(int, m_OriginalOwnerXuidLow, 0x31C0)
	POFFSET(int, m_hOwner, 0x29CC)
	POFFSET(int, m_flFallbackWear, 0x31D0)
	POFFSET(int, m_nFallbackSeed, 0x31CC)
	POFFSET(int, m_iEntityQuality, 0x2FAC)
	POFFSET(int, m_nModelIndex, 0x258)
	POFFSET(int, m_iViewModelIndex, 0x3240)
	OFFSET(uintptr_t, m_hWeaponWorldModel, 0x3254)
	POFFSET(int, m_iItemIDHigh, 0x2FC0)
	POFFSET(int, m_iItemDefinitionIndex, 0x2FAA)

	/*
	int getViewModelIndex()
	{
		return *(int*)(uintptr_t(this) + 0x3220);
	}

	uintptr_t WeaponWorldModel() {
		return *(uintptr_t*)(uintptr_t(this) + 0x31F4);
	}*/
};

/*
class C_BaseWeaponWorldModel : public C_BaseEntity {};


class CEconItemDefinition
{
public:
	virtual const char * get_definition_index() = 0;
	virtual const char * get_prefab_name() = 0;
	virtual const char * get_item_base_name() = 0;
	virtual const char * get_item_type_name() = 0;
	virtual const char * get_item_desc() = 0;
	virtual const char * get_inventory_image() = 0;
	int GetEquippedPosition()
	{
		return *reinterpret_cast< int* >( ( uintptr_t )this + 0x24C );
	}
};

class IRefCounted;
class CEconItem;

class C_EconItemView
{
public:
	/ *
	CEconItemDefinition * get_static_data()
	{
		static auto fnGetStaticData = reinterpret_cast< CEconItemDefinition*( __thiscall* )( void* ) >( sig( "client_panorama.dll", "55 8B EC 51 56 57 8B F1 E8 ? ? ? ? 0F B7 8E" ) );
		return fnGetStaticData( this );
	}
	CEconItem* GetSOCData()
	{
		static auto fnGetSOCData = reinterpret_cast< CEconItem*( __thiscall* )( C_EconItemView* ) >( sig( "client_panorama.dll", "55 8B EC 83 E4 F0 83 EC 18 56 8B F1 57 8B 86" ) );

		return fnGetSOCData( this );
	}
	int InitializeAttributes()
	{
		static auto fnInitializeAttributes = reinterpret_cast< int( __thiscall* )( void* ) >( sig( "client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 0C 53 56 8B F1 8B 86" ) );

		return fnInitializeAttributes( this );
	}* /

	char _pad_0x0000[ 0x14 ];
	CUtlVector<IRefCounted*>	m_CustomMaterials; //0x0014
	char _pad_0x0034[ 0x160 ];
	__int32                     m_iItemDefinitionIndex; //0x0194 
	__int32                     m_iEntityQuality; //0x0198 
	__int32                     m_iEntityLevel; //0x019C 
	char _pad_0x01A0[ 0x8 ]; //0x01A0
	__int32                     m_iItemIDHigh; //0x01A8 
	__int32                     m_iItemIDLow; //0x01AC 
	__int32                     m_iAccountID; //0x01B0 
	char pad_0x01B4[ 0x8 ]; //0x01B4
	unsigned char               m_bInitialized; //0x01BC 
	char pad_0x01BD[ 0x63 ]; //0x01BD
	CUtlVector<IRefCounted*>    m_VisualsDataProcessors; //0x0220
};

class C_AttributeManager
{
public:
	char	_pad_0x0000[ 0x18 ];
	__int32						m_iReapplyProvisionParity; //0x0018 
	DWORD						m_hOuter; //0x001C 
	char	_pad_0x0020[ 0x4 ];
	__int32						m_ProviderType; //0x0024 
	char	_pad_0x0028[ 0x18 ];
	C_EconItemView				m_Item; //0x0040 
};

class C_WeaponCSBase : public C_BaseAttributableItem
{
public:
	char	_pad_0x0000[ 0x09CC ];
	CUtlVector<IRefCounted*>	m_CustomMaterials; //0x09DC
	char	_pad_0x09F0[ 0x2380 ];
	C_AttributeManager			m_AttributeManager; //0x2D70
	char	_pad_0x2D84[ 0x2F9 ];
	bool						m_bCustomMaterialInitialized; //0x32DD
};*/

/*
class C_BasePlayer : public C_BaseCombatCharacter
{
public:
	NETVAR( get_lifestate, LifeState, "CBasePlayer->m_lifeState" )
	NETVAR( get_health, int, "CBasePlayer->m_iHealth" )
	NETVAR( get_flags, int, "CBasePlayer->m_fFlags" )
	NETVAR( get_tickbase, int, "CBasePlayer->m_nTickBase" )
	NETVAR( get_velocity, Vector, "CBasePlayer->m_vecVelocity[0]" )
	NETVAR( get_aim_punch, QAngle, "CBasePlayer->m_aimPunchAngle" )
	NETVAR( get_view_punch, QAngle, "CBasePlayer->m_viewPunchAngle" )
	NETVAR( get_observer_mode, int, "CBasePlayer->m_iObserverMode" )
	NETVAR( get_observer_target, CBaseHandle, "CBasePlayer->m_hObserverTarget" )
	NETVAR( get_view_model, CBaseHandle, "CBasePlayer->m_hViewModel[0]" )
	DATAMAPVAR( get_move_type, int, "m_MoveType" )
	DATAMAPVAR( get_next_attack, float, "m_flNextAttack" )
	OFFSET( get_spawn_time, float, 0xA360)
	//VFUNC( 11, get_abs_angles(), QAngle&( __thiscall* )( void* ) )( )
	//MFUNC( set_abs_angles( QAngle ang ), void( __thiscall* )( void*, const QAngle& ), offsets::set_abs_angles )( ang )
	//MFUNC( invalidate_physics_recursive( int physbit ), void( __thiscall* )( void*, int ), offsets::invalidate_physics_recursive )( physbit )

		/ *
	bool get_alive();
	Vector get_eye_pos();
	bool is_enemy();
	player_info_t get_player_info() const;
	std::string get_name() const;
	C_CSPlayer* get_observer(); * /
};

class CBoneAccessor;
class CBoneCache;
class CStudioHdr;
class CThreadFastMutex;
class C_BaseAnimating : public C_BasePlayer
{
public:
	NETVAR( get_hitbox_set, int, "CBaseAnimating->m_nHitboxSet" )
	//ANETVAR( get_pose_params, float, 24, "CBaseAnimating->m_flPoseParameter" )
	NETVAR( get_model_scale, float, "CBaseAnimating->m_flModelScale" )
	NETVAR( get_clientside_animation, bool, "CBaseAnimating->m_bClientSideAnimation" )
	DATAMAPVAR( get_playback_rate, int, "m_flPlaybackRate" )
	//OFFSET( get_model_ptr, CStudioHdr*, 0x294C)
	//OFFSET( get_enable_invalidate_bone_cache, bool, offsets::enable_invalidate_bone_cache )
	OFFSET( get_writable_bones, int, 0x26B0);
	//POFFSET( get_bone_accessor, CBoneAccessor, 0x26A8 )
	//POFFSET( get_bone_cache, CBoneCache, 0x2910) 
	NETVAR( get_force_bone, int, "CBaseAnimating->m_nForceBone" );
};

class CCSGOPlayerAnimState;
class QuaternionAligned;
class Quaternion;
class C_AnimationLayer;
class CIKContext;
struct studiohdr_t;

class C_CSPlayer : public C_BaseAnimating
{
public:
	//NETVAR( get_lby, float, "CCSPlayer->m_flLowerBodyYawTarget" )
	NETVAR( get_helmet, bool, "CCSPlayer->m_bHasHelmet" )
	NETVAR( get_armor, int, "CCSPlayer->m_ArmorValue" )
	NETVAR( get_heavy_armor, bool, "CCSPlayer->m_bHasHeavyArmor" )
	//NETVAR( get_eye_angles, QAngle, "CCSPlayer->m_angEyeAngles" )
	//NETVAR( get_flash_alpha, float, "CCSPlayer->m_flFlashMaxAlpha" )
	NETVAR( get_scoped, bool, "CCSPlayer->m_bIsScoped" )
	//NETVAR( get_immunity, bool, "CCSPlayer->m_bGunGameImmunity" )
	NETVAR( has_defuser, bool, "CCSPlayer->m_bHasDefuser" )
	//NETVAR( get_tp_angle, QAngle, "CCSPlayer->deadflag" )
	//OFFSET( get_visual_angles, QAngle, 0x31D8) // CCSPlayer->deadflag + 0x4
	//OFFSET( get_context, CIKContext*, 0x266C + 0x4 )
	//OFFSET( get_occlusion_flags, int, 0xA28 )
	//APOFFSET( get_anim_layers, C_AnimationLayer, 15, 0x2980)
	//OFFSET( get_anim_layer_count, int, 0x2980 + 12 )
	//OFFSET( get_anim_state, CCSGOPlayerAnimState*, 0x3900)
	//FUNC( create_anim_state( CCSGOPlayerAnimState* state ), void( __thiscall* )( CCSGOPlayerAnimState*, C_BasePlayer* ), offsets::create_anim_state )( state, this )
	//VFUNC( 189, build_transformations( CStudioHdr* hdr, Vector* vec, Quaternion* q, matrix3x4_t& transform, const int mask, uint8_t* computed ), void( __thiscall* )( void*, CStudioHdr*, Vector*, Quaternion*, matrix3x4_t const&, int, uint8_t* ) )( hdr, vec, q, transform, mask, computed )
	//VFUNC( 205, standard_blending_rules( CStudioHdr* hdr, Vector* vec, Quaternion* q, const float time, const int mask ), void( __thiscall* )( void*, CStudioHdr*, Vector*, Quaternion*, float, int ) )( hdr, vec, q, time, mask )
	//VFUNC( 223, update_clientside_anim(), void( __thiscall* )( void* ) )( )
		/ *
	NETPROP( get_lby_prop, "CCSPlayer->m_flLowerBodyYawTarget" )
	NETPROP( get_eye_angles0_prop, "CCSPlayer->m_angEyeAngles[0]" )
	NETPROP( get_eye_angles1_prop, "CCSPlayer->m_angEyeAngles[1]" )

	
	static bool setup_bones( lag_record_t& record, int boneMask, matrix3x4_t* pBoneToWorldOut );
	void set_anim_layers( std::array<C_AnimationLayer, 15>& layers );
	void set_pose_params( std::array<float, 24>& params );
	void set_pose_params_scaled( std::array<float, 24>& params );
	void set_pose_param( int param, float value );
	int get_sequence_act( int sequence );
	float  GetDesyncDelta();* /
};

class C_PlantedC4 : public C_BaseEntity
{
public:
	NETVAR( get_defuser, int32, "CPlantedC4->m_hBombDefuser" )
	NETVAR( get_defused, bool, "CPlantedC4->m_bBombDefused" )
	NETVAR( get_ticking, bool, "CPlantedC4->m_bBombTicking" )
	NETVAR( get_timer, float, "CPlantedC4->m_flC4Blow" )
};

class CSmokeGrenadeProjectile
{
public:
	//NETPROP( get_smoke_effect_prop, "CSmokeGrenadeProjectile->m_bDidSmokeEffect" )
};



class C_locPlayer
{
	friend bool operator==( const C_locPlayer& lhs, void* rhs ) { return *lhs.m_loc == rhs; }
public:
	C_locPlayer() : m_loc( nullptr ) {}

	operator bool() const { return *m_loc != nullptr; }
	operator C_CSPlayer*( ) const { return *m_loc; }

	C_CSPlayer* operator->() const { return *m_loc; }

private:
	C_CSPlayer * *m_loc;
}; */

#endif // !Entity_h

