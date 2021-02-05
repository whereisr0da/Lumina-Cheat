#include "skinchanger.h"

#include "../../sdk/interfaces.h"
#include "../../common/includes.h"
#include "../../common/config.h"
#include "../../common/common.h"

/*
#define SKIN_SLOT(id,side,weapon,weaponObject) \
	case (int)id: \
		weaponObject->setFallbackPaintKit(config::visual.skins.side.weapon.paint); \
		weaponObject->setFallbackWear(config::visual.skins.side.weapon.wear); \
		weaponObject->setFallbackSeed(config::visual.skins.side.weapon.seed); \
		weaponObject->setEntityQuality(config::visual.skins.side.weapon.quality); \
		if(config::visual.skins.side.weapon.stattrack) { \
			weaponObject->setFallbackStatTrak(config::visual.skins.side.weapon.stattrackCount); \
			weaponObject->setEntityQuality(9); \
		} \
		weaponObject->setAccountID(info.xuidlow); \
		weaponObject->setItemIDHigh(-1); \
	break; \
*/

#define SKIN_SLOT(id,side,weapon,weaponObject) \
	case (int)id: \
		 applySkin(itemDefinitionIndex, weaponObject, &(config::visual.skins.side.weapon), &info); \
	break; \

		//

/*
weaponObject->setFallbackPaintKit(config::visual.skins.side.weapon.paint); \
		weaponObject->setFallbackWear(0); \
		weaponObject->setFallbackSeed(0); \
		weaponObject->setAccountID(info.xuidlow); \
		if (updateSkin) { \
			itemIDHighOriginals[itemDefinitionIndex] = weaponObject->getItemIDHigh(); \
			weaponObject->setItemIDHigh(-1); \
		} \
		else if (weaponObject->getItemIDHigh() != itemIDHighOriginals[itemDefinitionIndex]) { \
			weaponObject->setItemIDHigh(itemIDHighOriginals[itemDefinitionIndex]); \
		} \

*/

#define STICKER_SLOT(id,side,weapon,slot) \
	case (int)id: \
		switch (slot) \
		{\
		case 0:\
			return config::visual.skins.side.weapon.sticker1;\
		case 1:\
			return config::visual.skins.side.weapon.sticker2;\
		case 2:\
			return config::visual.skins.side.weapon.sticker3;\
		case 3:\
			return config::visual.skins.side.weapon.sticker4;\
		case 4:\
			return config::visual.skins.side.weapon.sticker4;\
		default:\
			break;\
		}\
	break;\

#define STICKER_GROUPE(side,slot) \
	STICKER_SLOT(WEAPON_AK47,side,ak47Skin,slot) \
	STICKER_SLOT(WEAPON_AWP,side,awpSkin,slot) \
	STICKER_SLOT(WEAPON_USP_SILENCER,side,uspSkin,slot) \
	STICKER_SLOT(WEAPON_DEAGLE,side,deagleSkin,slot) \
	STICKER_SLOT(WEAPON_SSG08,side, ssg08Skin,slot) \
	STICKER_SLOT(WEAPON_SCAR20,side, scarSkin,slot) \
	STICKER_SLOT(WEAPON_M4A1, side, m4a1Skin,slot) \
	STICKER_SLOT(WEAPON_FAMAS, side, famasSkin, slot) \
	STICKER_SLOT(WEAPON_G3SG1, side, g3sg1Skin, slot) \
	STICKER_SLOT(WEAPON_M4A1_SILENCER, side, m4a1s1Skin, slot) \
	STICKER_SLOT(WEAPON_SG556, side, sg553Skin, slot) \
	STICKER_SLOT(WEAPON_AUG, side, augSkin, slot) \
	STICKER_SLOT(WEAPON_GALILAR, side, galilSkin, slot) \
	STICKER_SLOT(WEAPON_MAC10, side, mac10Skin, slot) \
	STICKER_SLOT(WEAPON_MP5SD, side, mp5Skin, slot) \
	STICKER_SLOT(WEAPON_MP7, side, mp7Skin, slot) \
	STICKER_SLOT(WEAPON_MP9, side, mp9Skin, slot) \
	STICKER_SLOT(WEAPON_BIZON, side, ppbizonSkin, slot) \
	STICKER_SLOT(WEAPON_P90, side, p90Skin, slot) \
	STICKER_SLOT(WEAPON_UMP45, side, umpSkin, slot) \
	STICKER_SLOT(WEAPON_CZ75A, side, cz75Skin, slot) \
	STICKER_SLOT(WEAPON_ELITE, side, dualberttaSkin, slot) \
	STICKER_SLOT(WEAPON_FIVESEVEN, side, fiveSevenSkin, slot) \
	STICKER_SLOT(WEAPON_GLOCK, side, glockSkin, slot) \
	STICKER_SLOT(WEAPON_P250, side, p250Skin, slot) \
	STICKER_SLOT(WEAPON_TEC9, side, tec9Skin, slot) \
	STICKER_SLOT(WEAPON_REVOLVER, side, revolverSkin, slot) \

	//default: 
	//	return reinterpret_cast<decltype(hooked_uint_fn)*>(o_uint_fn)(thisptr, nullptr, slot, attribute, fl); 
	//break; 

/*

	case (int)WEAPON_KNIFE: \
		switch (slot) \
		{\
		case 0:\
			return 0;\
		case 1:\
			return 0;\
		case 2:\
			return 0;\
		case 3:\
			return 0;\
		case 4:\
			return 0;\
		default:\
			break;\
		}\
	break;\
	case (int)WEAPON_KNIFE_T: \
		switch (slot) \
		{\
		case 0:\
			return 0;\
		case 1:\
			return 0;\
		case 2:\
			return 0;\
		case 3:\
			return 0;\
		case 4:\
			return 0;\
		default:\
			break;\
		}\
	break;\
*/

// don't know why, but EU csgo version has two usp and cz id
#define SKIN_GROUPE(side,weaponObject) \
	SKIN_SLOT(WEAPON_AK47,side,ak47Skin,weaponObject) \
	SKIN_SLOT(WEAPON_AWP,side,awpSkin,weaponObject) \
	SKIN_SLOT(WEAPON_USP_SILENCER,side,uspSkin,weaponObject) \
	SKIN_SLOT(262205,side,uspSkin,weaponObject) \
	SKIN_SLOT(WEAPON_DEAGLE,side,deagleSkin,weaponObject) \
	SKIN_SLOT(WEAPON_SSG08,side, ssg08Skin,weaponObject) \
	SKIN_SLOT(WEAPON_SCAR20,side, scarSkin,weaponObject) \
	SKIN_SLOT(WEAPON_M4A1, side, m4a1Skin, weaponObject) \
	SKIN_SLOT(WEAPON_FAMAS, side, famasSkin, weaponObject) \
	SKIN_SLOT(WEAPON_G3SG1, side, g3sg1Skin, weaponObject) \
	SKIN_SLOT(WEAPON_M4A1_SILENCER, side, m4a1s1Skin, weaponObject) \
	SKIN_SLOT(WEAPON_SG556, side, sg553Skin, weaponObject) \
	SKIN_SLOT(WEAPON_AUG, side, augSkin, weaponObject) \
	SKIN_SLOT(WEAPON_GALILAR, side, galilSkin, weaponObject) \
	SKIN_SLOT(WEAPON_MAC10, side, mac10Skin, weaponObject) \
	SKIN_SLOT(WEAPON_MP5SD, side, mp5Skin, weaponObject) \
	SKIN_SLOT(WEAPON_MP7, side, mp7Skin, weaponObject) \
	SKIN_SLOT(WEAPON_MP9, side, mp9Skin, weaponObject) \
	SKIN_SLOT(WEAPON_BIZON, side, ppbizonSkin, weaponObject) \
	SKIN_SLOT(WEAPON_P90, side, p90Skin, weaponObject) \
	SKIN_SLOT(WEAPON_UMP45, side, umpSkin, weaponObject) \
	SKIN_SLOT(WEAPON_CZ75A, side, cz75Skin, weaponObject) \
	SKIN_SLOT(262207, side, cz75Skin, weaponObject) \
	SKIN_SLOT(WEAPON_ELITE, side, dualberttaSkin, weaponObject) \
	SKIN_SLOT(WEAPON_FIVESEVEN, side, fiveSevenSkin, weaponObject) \
	SKIN_SLOT(WEAPON_GLOCK, side, glockSkin, weaponObject) \
	SKIN_SLOT(WEAPON_P250, side, p250Skin, weaponObject) \
	SKIN_SLOT(WEAPON_TEC9, side, tec9Skin, weaponObject) \
	SKIN_SLOT(WEAPON_REVOLVER, side, revolverSkin, weaponObject) \


//SKIN_SLOT(262205,side,uspSkin,weaponObject) 
//SKIN_SLOT(262207, side, cz75Skin, weaponObject) 
/*
using recv_var_proxy_fn_ = void(*)(const c_recv_proxy_data_* data, void* struct_ptr, void* out_ptr);
using array_length_recv_proxy_fn_ = void(*)(void* struct_ptr, int object_id, int current_array_length);
using data_table_recv_var_proxy_fn_ = void(*)(const recv_prop_* prop, void** out_ptr, void* data_ptr, int object_id);

recv_var_proxy_fn_ sequenceOrginalFn = nullptr;
recv_var_proxy_fn_ recvModelIndex;
*/

/*
#define KNIFE_SKIN(side) \
	int knifeModelId = interfaces::modelInfo->GetModelIndex(knifeModelNames[config::visual.skins.side.knifeId]); \
	int knifeDefinitionId = getKnifeDefinitionIndex(config::visual.skins.side.knifeId); \
	currentWeapon->setItemDefinitionIndex(knifeDefinitionId); \
	currentWeapon->setFallbackPaintKit(config::visual.skins.side.knifePaint); \
	currentWeapon->setEntityQuality(3); \
	currentWeapon->setFallbackWear(0); \
	currentWeapon->setFallbackSeed(0); \
	currentWeapon->setModelIndex(knifeModelId); \
	currentWeaponBase->setViewModelIndex(knifeModelId); \
	if (!localPlayer->m_hViewModel()) { continue; }\
	auto viewModel = (C_BaseViewModel*)(interfaces::clientEntityList->GetClientEntityFromHandle(localPlayer->m_hViewModel())); \
	if (!viewModel) { continue; } \
	auto viewModelWeaponHandle = viewModel->m_hWeapon(); \
	if (!viewModelWeaponHandle) { continue; } \
	auto currentPlayerWeapon = (C_BaseAttributableItem*)(interfaces::clientEntityList->GetClientEntityFromHandle(viewModelWeaponHandle)); \
	if (currentPlayerWeapon->itemDefinitionIndex() != knifeDefinitionId) { continue; } \
	viewModel->setModelIndex(knifeModelId); \
	currentWeapon->setItemIDHigh(-1); \
*/

namespace skinchanger {

	/*
	const char* playerModels[] = {
		"models/player/custom_player/legacy/ctm_fbi_variantb.mdl",
		"models/player/custom_player/legacy/ctm_fbi_variantf.mdl",
		"models/player/custom_player/legacy/ctm_fbi_variantg.mdl",
		"models/player/custom_player/legacy/ctm_fbi_varianth.mdl",
		"models/player/custom_player/legacy/ctm_sas_variantf.mdl",
		"models/player/custom_player/legacy/ctm_st6_variante.mdl",
		"models/player/custom_player/legacy/ctm_st6_variantg.mdl",
		"models/player/custom_player/legacy/ctm_st6_varianti.mdl",
		"models/player/custom_player/legacy/ctm_st6_variantk.mdl",
		"models/player/custom_player/legacy/ctm_st6_variantm.mdl",
		"models/player/custom_player/legacy/tm_balkan_variantf.mdl",
		"models/player/custom_player/legacy/tm_balkan_variantg.mdl",
		"models/player/custom_player/legacy/tm_balkan_varianth.mdl",
		"models/player/custom_player/legacy/tm_balkan_varianti.mdl",
		"models/player/custom_player/legacy/tm_balkan_variantj.mdl",
		"models/player/custom_player/legacy/tm_leet_variantf.mdl",
		"models/player/custom_player/legacy/tm_leet_variantg.mdl",
		"models/player/custom_player/legacy/tm_leet_varianth.mdl",
		"models/player/custom_player/legacy/tm_leet_varianti.mdl",
		"models/player/custom_player/legacy/tm_phoenix_variantf.mdl",
		"models/player/custom_player/legacy/tm_phoenix_variantg.mdl",
		"models/player/custom_player/legacy/tm_phoenix_varianth.mdl"
	};*/

	std::vector<std::string> knifeModelNames = {};
	std::vector<std::string> playerModels = {};
	std::vector<std::string> armsModels = {};

	// init to the highest item index possible
	static int itemIDHighOriginals[GLOVE_HYDRA];

	static uint16_t s_iwoff = 0;

	static void* o_uint_fn;

	bool updateSkin = true;

	int getKnifeDefinitionIndex(int si)
	{
		switch (si)
		{
		case 0:
			return WEAPON_KNIFE;
		case 1:
			return WEAPON_KNIFE_T;
		case 2:
			return WEAPON_BAYONET;
		case 3:
			return WEAPON_KNIFE_M9_BAYONET;
		case 4:
			return WEAPON_KNIFE_KARAMBIT;
		case 5:
			return WEAPON_KNIFE_SURVIVAL_BOWIE;
		case 6:
			return WEAPON_KNIFE_BUTTERFLY;
		case 7:
			return WEAPON_KNIFE_FALCHION;
		case 8:
			return WEAPON_KNIFE_FLIP;
		case 9:
			return WEAPON_KNIFE_GUT;
		case 10:
			return WEAPON_KNIFE_TACTICAL;
		case 11:
			return WEAPON_KNIFE_PUSH;
		case 12:
			return WEAPON_KNIFE_GYPSY_JACKKNIFE;
		case 13:
			return WEAPON_KNIFE_STILETTO;
		case 14:
			return WEAPON_KNIFE_WIDOWMAKER;
		case 15:
			return WEAPON_KNIFE_URSUS;
		case 16:
			return 525;
		case 17:
			return 521;
		case 18:
			return 518;
		case 19:
			return 517;
		case 20:
			return 503;
		default:
			return -1;
		}
	}

	/*
	const char* knifeModelNames[] = {
		"models/weapons/v_knife_default_t.mdl",
		"models/weapons/v_knife_default_ct.mdl",
		"models/weapons/v_knife_bayonet.mdl",
		"models/weapons/v_knife_m9_bay.mdl",
		"models/weapons/v_knife_karam.mdl",
		"models/weapons/v_knife_survival_bowie.mdl",
		"models/weapons/v_knife_butterfly.mdl",
		"models/weapons/v_knife_falchion_advanced.mdl",
		"models/weapons/v_knife_flip.mdl",
		"models/weapons/v_knife_gut.mdl",
		"models/weapons/v_knife_tactical.mdl",
		"models/weapons/v_knife_push.mdl",
		"models/weapons/v_knife_gypsy_jackknife.mdl",
		"models/weapons/v_knife_stiletto.mdl",
		"models/weapons/v_knife_widowmaker.mdl",
		"models/weapons/v_knife_ursus.mdl",
		"models/weapons/v_knife_skeleton.mdl", //skeleton knife
		"models/weapons/v_knife_outdoor.mdl", //nomad knife
		"models/weapons/v_knife_canis.mdl", //survivak knife
		"models/weapons/v_knife_cord.mdl", //paracord knife
		"models/weapons/v_knife_css.mdl"
	};*/

	void init() {

		VMProtectBeginMutation("skinchanger::init");

		ZeroMemory(itemIDHighOriginals, GLOVE_HYDRA);

		VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_default_t.mdl", tmp0)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_default_ct.mdl", tmp1)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_bayonet.mdl", tmp2)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_m9_bay.mdl", tmp3)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_karam.mdl", tmp4)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_survival_bowie.mdl", tmp4_)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_butterfly.mdl", tmp5)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_falchion_advanced.mdl", tmp6)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_flip.mdl", tmp7)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_gut.mdl", tmp8)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_tactical.mdl", tmp9)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_push.mdl", tmp10)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_gypsy_jackknife.mdl", tmp11)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_stiletto.mdl", tmp12)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_widowmaker.mdl", tmp13)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_ursus.mdl", tmp14)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_skeleton.mdl", tmp15)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_outdoor.mdl", tmp16)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_canis.mdl", tmp17)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_cord.mdl", tmp18)
			VECTOR_PUSH(knifeModelNames, "models/weapons/v_knife_css.mdl", tmp19)

			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_fbi_variantb.mdl", tmp20)
			VECTOR_PUSH(playerModels, "models/player/custom_player/nf/lara/lara.mdl", tmp20_)
			VECTOR_PUSH(playerModels, "models/player/custom_player/voikanaa/halo4/cortana.mdl", tmp21)
			VECTOR_PUSH(playerModels, "models/player/samus/samus.mdl", tmp22)
			VECTOR_PUSH(playerModels, "models/player/custom_player/kodua/goku/goku.mdl", tmp23)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/cuddleleader.mdl", tmp24)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/gxp/valorant_viper/viper_v1f.mdl", tmp25)
			VECTOR_PUSH(playerModels, "models/player/custom_player/kuristaja/cso2/sas/sas.mdl", tmp26)
			VECTOR_PUSH(playerModels, "models/player/custom_player/kuristaja/cso2/lincoln/lincoln.mdl", tmp27)
			VECTOR_PUSH(playerModels, "models/player/custom_player/kuristaja/cso2/karachenko/karachenko.mdl", tmp28)
			VECTOR_PUSH(playerModels, "models/player/custom_player/kuristaja/cso2/gign/gign.mdl", tmp29)
			VECTOR_PUSH(playerModels, "models/player/custom_player/kuristaja/cso2/carrie/carrie.mdl", tmp30)
			VECTOR_PUSH(playerModels, "models/player/custom_player/kuristaja/cso2/707/707.mdl", tmp31)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_phoenix_variantf.mdl", tmp40)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_phoenix_variantg.mdl", tmp41)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_phoenix_varianth.mdl", tmp42)

			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_fbi_variantf.mdl", tmp21_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_fbi_variantg.mdl", tmp22_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_fbi_varianth.mdl", tmp23_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_sas_variantf.mdl", tmp24_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_st6_variante.mdl", tmp25_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_st6_variantg.mdl", tmp26_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_st6_varianti.mdl", tmp27_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_st6_variantk.mdl", tmp28_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_st6_variantm.mdl", tmp29_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_balkan_variantf.mdl", tmp31_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_balkan_variantg.mdl", tmp32_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_balkan_varianth.mdl", tmp33_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_balkan_varianti.mdl", tmp34_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_balkan_variantj.mdl", tmp35_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_leet_variantf.mdl", tmp36_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_leet_variantg.mdl", tmp37_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_leet_varianth.mdl", tmp38_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_leet_varianti.mdl", tmp39_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_phoenix_variantf.mdl", tmp40_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_phoenix_variantg.mdl", tmp41_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_phoenix_varianth.mdl", tmp42_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_st6_variantj.mdl", tmp43_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_st6_variantl.mdl", tmp44_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_swat_variante.mdl", tmp45_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_swat_variantf.mdl", tmp46_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_swat_variantg.mdl", tmp47_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_swat_varianth.mdl", tmp48_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_swat_varianti.mdl", tmp49_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_swat_variantj.mdl", tmp50_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_balkan_variantk.mdl", tmp51_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_balkan_variantl.mdl", tmp52_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_phoenix_varianti.mdl", tmp53_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_varf.mdl", tmp54_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_varf1.mdl", tmp55_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_varf2.mdl", tmp56_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_varf3.mdl", tmp57_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_varf4.mdl", tmp58_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_varg.mdl", tmp59_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_varh.mdl", tmp60_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_vari.mdl", tmp61_)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_professional_varj.mdl", tmp62_)

			/*
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/ctm_fbi_variantb.mdl", tmp50)
			VECTOR_PUSH(armsModels, "models/player/custom_player/nf/lara/lara_arms.mdl", tmp51)
			VECTOR_PUSH(armsModels, "models/player/custom_player/voikanaa/halo4/cortana.mdl", tmp52)
			VECTOR_PUSH(armsModels, "models/player/samus/samus.mdl", tmp53)
			VECTOR_PUSH(armsModels, "models/player/custom_player/kodua/goku/goku_arms.mdl", tmp54)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/cuddleleader.mdl", tmp55)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/gxp/valorant_viper/viper_arm_v1.mdl", tmp56)
			VECTOR_PUSH(armsModels, "models/player/custom_player/kuristaja/cso2/sas/sas_arms.mdl", tmp57)
			VECTOR_PUSH(armsModels, "models/player/custom_player/kuristaja/cso2/lincoln/lincoln_arms.mdl", tmp58)
			VECTOR_PUSH(armsModels, "models/player/custom_player/kuristaja/cso2/karachenko/karachenko_arms.mdl", tmp59)
			VECTOR_PUSH(armsModels, "models/player/custom_player/kuristaja/cso2/gign/gign_arms.mdl", tmp60)
			VECTOR_PUSH(armsModels, "models/player/custom_player/kuristaja/cso2/carrie/carrie_arms.mdl", tmp61)
			VECTOR_PUSH(armsModels, "models/player/custom_player/kuristaja/cso2/707/707_arms.mdl", tmp62)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_phoenix_variantf.mdl", tmp63)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_phoenix_variantg.mdl", tmp64)
			VECTOR_PUSH(armsModels, "models/player/custom_player/legacy/tm_phoenix_varianth.mdl", tmp65)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_fbi_variantf.mdl", tmp21)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_fbi_variantg.mdl", tmp22)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_fbi_varianth.mdl", tmp23)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_sas_variantf.mdl", tmp24)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_st6_variante.mdl", tmp25)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_st6_variantg.mdl", tmp26)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_st6_varianti.mdl", tmp27)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_st6_variantk.mdl", tmp28)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_st6_variantm.mdl", tmp29)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_balkan_variantf.mdl", tmp31)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_balkan_variantg.mdl", tmp32)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_balkan_varianth.mdl", tmp33)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_balkan_varianti.mdl", tmp34)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_balkan_variantj.mdl", tmp35)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_leet_variantf.mdl", tmp36)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_leet_variantg.mdl", tmp37)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_leet_varianth.mdl", tmp38)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_leet_varianti.mdl", tmp39)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_phoenix_variantf.mdl", tmp40)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_phoenix_variantg.mdl", tmp41)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_phoenix_varianth.mdl", tmp42)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_st6_variantj.mdl", tmp43)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_st6_variantl.mdl", tmp44)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_swat_variante.mdl", tmp45)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_swat_variantf.mdl", tmp46)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_swat_variantg.mdl", tmp47)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_swat_varianth.mdl", tmp48)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_swat_varianti.mdl", tmp49)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/ctm_swat_variantj.mdl", tmp50)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_balkan_variantk.mdl", tmp51)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_balkan_variantl.mdl", tmp52)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_phoenix_varianti.mdl", tmp53)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_varf.mdl", tmp54)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_varf1.mdl", tmp55)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_varf2.mdl", tmp56)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_varf3.mdl", tmp57)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_varf4.mdl", tmp58)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_varg.mdl", tmp59)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_varh.mdl", tmp60)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_vari.mdl", tmp61)
			VECTOR_PUSH(playerModels, "models/player/custom_player/legacy/tm_professional_varj.mdl", tmp62)
			*/



			//setupAnimations();

			VMProtectEnd();
	}

	static unsigned int __fastcall hooked_uint_fn(void* thisptr, void*, int slot, EStickerAttributeType attribute, unsigned fl)
	{
		VMProtectBeginMutation("skinchanger::hooked_uint_fn");

		auto item = reinterpret_cast<C_BaseAttributableItem*>(uintptr_t(thisptr) - s_iwoff);

		if(!item)
			return reinterpret_cast<decltype(hooked_uint_fn)*>(o_uint_fn)(thisptr, nullptr, slot, attribute, fl);

		auto localPlayer = game::getLocalPlayer();

		if (!localPlayer->isAlive())
			return reinterpret_cast<decltype(hooked_uint_fn)*>(o_uint_fn)(thisptr, nullptr, slot, attribute, fl);

		int team = localPlayer->m_iTeamNum();

		if (attribute == EStickerAttributeType::Index)
		{
			if (!item->IsBaseCombatWeapon() || ((C_BaseCombatWeapon*)item)->IsKnife())
				return reinterpret_cast<decltype(hooked_uint_fn)*>(o_uint_fn)(thisptr, nullptr, slot, attribute, fl);

			if(*item->m_iItemDefinitionIndex() == WEAPON_KNIFE || *item->m_iItemDefinitionIndex() == WEAPON_KNIFE_T)
				return reinterpret_cast<decltype(hooked_uint_fn)*>(o_uint_fn)(thisptr, nullptr, slot, attribute, fl);

			if (team == TEAM_COUNTER_TERRORIST) // CT
			{
				switch (*item->m_iItemDefinitionIndex())
				{
					STICKER_GROUPE(ctSkins, slot)
				}
			}
			else if (team == TEAM_TERRORIST) // T
			{
				switch (*item->m_iItemDefinitionIndex())
				{
					STICKER_GROUPE(tSkins, slot)
				}
			}
		}

		VMProtectEnd();

		return reinterpret_cast<decltype(hooked_uint_fn)*>(o_uint_fn)(thisptr, nullptr, slot, attribute, fl);
	}

	int applyStickerHooks(int* item)
	{
		VMProtectBeginMutation("skinchanger::initStickerHooks");

		// thx to a guy from ukc

		if (!s_iwoff)
			s_iwoff = 0x2DC0 + 0xC; //m_Item

		void**& iw_vt = *reinterpret_cast<void***>(uintptr_t(item) + s_iwoff);

		static void** iw_hook_vt = nullptr;

		if (!iw_hook_vt)
		{
			size_t len = 0;

			for (; iw_vt[len]; ++len);

			iw_hook_vt = new void*[len];

			memcpy(iw_hook_vt, iw_vt, len * sizeof(void*));

			o_uint_fn = iw_hook_vt[5];

			iw_hook_vt[5] = &hooked_uint_fn;
		}

		iw_vt = iw_hook_vt;

		VMProtectEnd();

		return 0;
	}

	void applyPlayerModel(int frameStage) {

		VMProtectBeginMutation("skinchanger::applyPlayerModel");

		auto localPlayer = game::getLocalPlayer();

		static int originalIdx = 0;

		if (!localPlayer) {
			originalIdx = 0;
			return;
		}

		if (!localPlayer->isAlive()) {
			originalIdx = 0;
			return;
		}

		auto modelPath = playerModels.at(config::visual.playerModel.id).c_str();

		if (frameStage == FRAME_RENDER_START)
			originalIdx = localPlayer->m_nModelIndex();

		int modelIndex = frameStage == FRAME_RENDER_END && originalIdx ? originalIdx : interfaces::modelInfo->GetModelIndex(modelPath);

		// if a custom model is not loaded
		if (modelIndex == -1) {
			// load it
			if (!utils::precacheModel(modelPath)) {

#ifdef _DEBUG
				common::ps(XorStr("skinchanger::applyPlayerModel : fail to precacheModel"));
#endif
			}
			// retry to get its id
			else {
				modelIndex = frameStage == FRAME_RENDER_END && originalIdx ? originalIdx : interfaces::modelInfo->GetModelIndex(modelPath);
			}
		}

		auto armsModelPath = armsModels.at(config::visual.playerModel.id).c_str();

		// checks if loaded or not
		int armsModelId = interfaces::modelInfo->GetModelIndex(armsModelPath);

		// if a custom model arms is not loaded
		if (armsModelId == -1) {
			// load it
			if (!utils::precacheModel(armsModelPath)) {

#ifdef _DEBUG
				common::ps(XorStr("skinchanger::applyPlayerModel : fail to precacheModel arms"));
#endif
			}
		}

		localPlayer->setModelIndex(modelIndex);

		auto ragdoll = (Entity*)interfaces::clientEntityList->GetClientEntityFromHandle(localPlayer->m_hRagdoll());

		if (ragdoll)
			ragdoll->setModelIndex(modelIndex);

		VMProtectEnd();
	}

	void applyTeamMateModel(Entity* e, int frameStage) {

		VMProtectBeginMutation("skinchanger::applyTeamMateModel");

		auto modelPath = playerModels.at(config::visual.teamMateModel.id).c_str();

		int modelIndex = interfaces::modelInfo->GetModelIndex(modelPath);

		// if a custom model is not loaded
		if (modelIndex == -1) {
			// load it
			if (!utils::precacheModel(modelPath)) {

#ifdef _DEBUG
				common::ps(XorStr("skinchanger::applyTeamMateModel : fail to precacheModel"));
#endif
				return;
			}
			// retry to get its id
			else {
				modelIndex = interfaces::modelInfo->GetModelIndex(modelPath);
			}
		}

		e->setModelIndex(modelIndex);

		auto ragdoll = (Entity*)interfaces::clientEntityList->GetClientEntityFromHandle(e->m_hRagdoll());

		if (ragdoll)
			ragdoll->setModelIndex(modelIndex);

		VMProtectEnd();
	}

	void entityLoop(int frameStage) {

		VMProtectBeginMutation("skinchanger::entityLoop");

		auto localPlayer = game::getLocalPlayer();

		if (!localPlayer)
			return;

		// loop about entities
		for (int i = 0; i < interfaces::clientEntityList->GetHighestEntityIndex(); i++) {

			auto entity = (Entity*)(interfaces::clientEntityList->GetClientEntity(i));

			if (!entity)
				continue;

			if (!entity->isPlayer() || entity == localPlayer)
				continue;

			// if team mates
			if (config::visual.teamMateModel.enable && entity->m_iTeamNum() == localPlayer->m_iTeamNum())
			{
				applyTeamMateModel(entity, frameStage);
			}
			else if (entity->m_iTeamNum() != localPlayer->m_iTeamNum()) {
				// radar
				entity->setSpotted(config::visual.showRadar);
			}
		}

		VMProtectEnd();
	}

	/*
	int getSequenceActivityWorker(C_BaseViewModel* viewModel, int sequence) {

		auto localPlayer = (Entity*)(interfaces::clientEntityList->GetClientEntity(interfaces::engineClient->GetLocalPlayer()));

		if (!localPlayer)
			return -1;

		if (!localPlayer->model())
			return -1;

		auto hdr = interfaces::modelInfo->GetStudioModel(localPlayer->model());

		if (!hdr)
			return -1;

		return interfaces::getSequenceActivity(viewModel, hdr, sequence);
	}

	void hookedRecvproxyViewmodel(c_recv_proxy_data_* p_data, void *p_struct, void *p_out) {

		std::vector<long> modelIndexs = {};

		for (std::string model : knifeModelNames) 
			modelIndexs.push_back((long)interfaces::modelInfo->GetModelIndex(model.c_str()));
		
		auto localPlayer = reinterpret_cast<Entity*>(interfaces::clientEntityList->GetClientEntity(interfaces::engineClient->GetLocalPlayer()));

		if (!localPlayer)
			return;

		if (!localPlayer->isAlive())
			return;

		// if the viewModel contains a knife
		if (std::find(modelIndexs.begin(), modelIndexs.end(), p_data->value.m_int) != modelIndexs.end())
		{
			int knifeId = localPlayer->m_iTeamNum() == TEAM_COUNTER_TERRORIST ? config::visual.skins.ctSkins.knifeId : config::visual.skins.tSkins.knifeId;

			p_data->value.m_int = interfaces::modelInfo->GetModelIndex(knifeModelNames.at(knifeId).c_str());
		}
		
		if (recvModelIndex)
			recvModelIndex(p_data, p_struct, p_out);
	}

	void setViewModelSequence(const c_recv_proxy_data_* pDataConst, void *p_struct, void *p_out) {

		c_recv_proxy_data_* p_data = const_cast<c_recv_proxy_data_*>(pDataConst);

		C_BaseAttributableItem* player_view_model = static_cast<C_BaseAttributableItem*>(p_struct);

		C_BaseViewModel* pViewModel = (C_BaseViewModel*)p_struct;

		if (player_view_model) {

			auto local_player = reinterpret_cast<Entity*>(interfaces::clientEntityList->GetClientEntity(interfaces::engineClient->GetLocalPlayer()));

			Entity* p_owner = (Entity*)(interfaces::clientEntityList->GetClientEntity(player_view_model->m_hOwner() & 0xFFF));

			if (p_owner == local_player) {

				int m_nSequence = p_data->value.m_int;

				/*
				int originalActivity = getSequenceActivityWorker(pViewModel, m_nSequence); // Get the original sequence activity

				// thanks oneshot : https://www.unknowncheats.me/forum/counterstrike-global-offensive/326785-automated-sequence-fix-knife-model-changer.html

				int newActivity = 1;
				int num = 0;

				for (size_t i = 0; i < 20; i++) // compare activity with original activity and save new activity // havent seen a sequence above 14 but using 20 if theres is :D
				{
					int tempActitivity = getSequenceActivityWorker(pViewModel, i);
					if (originalActivity != -1 && originalActivity == tempActitivity || originalActivity == -1 && tempActitivity == 213)
					{
						newActivity = i;
						for (size_t t = 0; t < 4; t++)
							if (getSequenceActivityWorker(pViewModel, i + t) == tempActitivity)
								num++;
						break;
					}
				}

				if (originalActivity == -1 && newActivity == 1)
					newActivity = m_nSequence;
				if (!num)
					m_nSequence = newActivity;
				else
					m_nSequence = RandomInt(newActivity, newActivity + num - 1);

				//pViewModel->SendViewModelMatchingSequence(m_nSequence); // this sets the sequence and resets the sequence timings.
				

				std::string sz_model = interfaces::modelInfo->GetModelName(interfaces::modelInfo->GetModel(player_view_model->getModelIndex()));

				if (sz_model == XorStr("models/weapons/v_knife_butterfly.mdl")) {
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_DRAW:
						m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
						break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
						break;
					default:
						m_nSequence++;
					}
				}
				else if (sz_model == XorStr("models/weapons/v_knife_falchion_advanced.mdl")) {
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
						m_nSequence = RandomInt(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
						break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomInt(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
						break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					default:
						m_nSequence--;
					}
				}
				else if (sz_model == XorStr("models/weapons/v_knife_push.mdl")) {
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
					case SEQUENCE_DEFAULT_LIGHT_MISS1:
					case SEQUENCE_DEFAULT_LIGHT_MISS2:
						m_nSequence = RandomInt(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
						break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
						m_nSequence = RandomInt(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
						break;
					case SEQUENCE_DEFAULT_HEAVY_HIT1:
					case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence += 3; break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					default:
						m_nSequence += 2;
					}
				}
				else if (sz_model == XorStr("models/weapons/v_knife_survival_bowie.mdl")) {
					switch (m_nSequence)
					{
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_BOWIE_IDLE1;
						break;
					default:
						m_nSequence--;
					}
				}
				else if (sz_model == XorStr("models/weapons/v_knife_ursus.mdl")) {
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_DRAW:
						m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
						break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
						break;
					default:
						m_nSequence++;
						break;
					}
				}
				else if (sz_model == XorStr("models/weapons/v_knife_stiletto.mdl")) {
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomInt(12, 13);
						break;
					}
				}
				else if (sz_model == XorStr("models/weapons/v_knife_widowmaker.mdl")) {
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomInt(14, 15);
						break;
					}
				}
				else if (sz_model == XorStr("models/weapons/v_knife_cord.mdl")
					|| sz_model == XorStr("models/weapons/v_knife_canis.mdl")
					|| sz_model == XorStr("models/weapons/v_knife_outdoor.mdl")
					|| sz_model == XorStr("models/weapons/v_knife_skeleton.mdl"))
				{
					switch (m_nSequence)
					{
					case SEQUENCE_DEFAULT_DRAW:
						m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
					default:
						m_nSequence = m_nSequence + 1;
					}
				}


				p_data->value.m_int = m_nSequence;
			}
		}

		sequenceOrginalFn(p_data, p_struct, p_out);
	}

	void setupAnimations() {

		for (auto client_class = interfaces::baseClientDll->GetAllClasses(); client_class; client_class = client_class->m_pNext) {

			if (!strcmp(client_class->m_pNetworkName, XorStr("CBaseViewModel"))) {
				const auto table = reinterpret_cast<recv_table_*>(client_class->m_pRecvTable);
				for (int nIndex = 0; nIndex < table->props_count; nIndex++) {
					recv_prop_* pProp = &table->props[nIndex];
					if (!pProp || strcmp(pProp->prop_name, XorStr("m_nSequence")))
						continue;
					sequenceOrginalFn = static_cast<recv_var_proxy_fn_>(pProp->proxy_fn);
					pProp->proxy_fn = static_cast<recv_var_proxy_fn_>(setViewModelSequence);
					break;
				}
				break;
			}
		}

		auto client_class = interfaces::baseClientDll->GetAllClasses();

		while (client_class) {
			const char *pszName = client_class->m_pRecvTable->table_name;
			if (!strcmp(pszName, XorStr("DT_SmokeGrenadeProjectile"))) {
				for (int i = 0; i < client_class->m_pRecvTable->props_count; i++) {
					recv_prop_ *pProp = &(client_class->m_pRecvTable->props[i]);
					const char *name = pProp->prop_name;
					if (!strcmp(name, XorStr("m_bDidSmokeEffect"))) {
					}
				}
			}
			else if (!strcmp(pszName, XorStr("DT_BaseViewModel"))) {
				for (int i = 0; i < client_class->m_pRecvTable->props_count; i++) {
					recv_prop_ *pProp = &(client_class->m_pRecvTable->props[i]);
					const char *name = pProp->prop_name;
					if (!strcmp(name, XorStr("m_nModelIndex"))) {
						recvModelIndex = (recv_var_proxy_fn_)pProp->proxy_fn;
						pProp->proxy_fn = (recv_var_proxy_fn_)hookedRecvproxyViewmodel;
					}
				}
			}
			client_class = client_class->m_pNext;
		}
	}
	*/

	void changeViewModel(C_BaseAttributableItem* pCurrentWeapon) {

		VMProtectBeginMutation("skinchanger::changeViewModel");

		auto localPlayer = game::getLocalPlayer();

		if (!localPlayer->m_hViewModel())
			return;

		C_BaseViewModel* pViewModel = (C_BaseViewModel*)interfaces::clientEntityList->GetClientEntityFromHandle((CBaseHandle)localPlayer->m_hViewModel());

		if (!pViewModel)
			return;

		DWORD hViewModelWeapon = pViewModel->m_hWeapon();

		if (!hViewModelWeapon)
			return;

		C_BaseAttributableItem* pViewModelWeapon = (C_BaseAttributableItem*)interfaces::clientEntityList->GetClientEntityFromHandle((CBaseHandle)hViewModelWeapon);

		// if the weapon is the current weapon of the player
		if (!pViewModelWeapon || pViewModelWeapon != pCurrentWeapon)
			localPlayer;

		auto pViewModelWeaponInfo = (C_BaseCombatWeapon*)pViewModelWeapon;

		// if it's not a knife
		if (!pViewModelWeaponInfo->IsKnife())
			return;

		int team = localPlayer->m_iTeamNum();

		int knifeId = team == TEAM_COUNTER_TERRORIST ? config::visual.skins.ctSkins.knifeId : config::visual.skins.tSkins.knifeId;

		auto pViewModelWeaponBase = (C_BaseViewModel*)pViewModelWeapon;

		pViewModel->setModelIndex(interfaces::modelInfo->GetModelIndex(knifeModelNames.at(knifeId).c_str()));

		VMProtectEnd();
	}

	void applyKnifeSkin(int itemDefinitionIndex, C_BaseAttributableItem* weaponObject, player_info_t* info) {

		VMProtectBeginMutation("skinchanger::applyKnifeSkin");

		int team = game::getLocalPlayer()->m_iTeamNum();

		int knifeId = team == TEAM_COUNTER_TERRORIST ? config::visual.skins.ctSkins.knifeId : config::visual.skins.tSkins.knifeId;
		int knifePaint = team == TEAM_COUNTER_TERRORIST ? config::visual.skins.ctSkins.knifePaint : config::visual.skins.tSkins.knifePaint;

		// update only if I change its paint
		if (knifePaint == 0)
			return;

		int knifeModelId = interfaces::modelInfo->GetModelIndex(knifeModelNames.at(knifeId).c_str());
		int knifeDefinitionId = getKnifeDefinitionIndex(knifeId);

		if (itemDefinitionIndex == WEAPON_KNIFE ||
			itemDefinitionIndex == WEAPON_KNIFE_T ||
			itemDefinitionIndex == knifeDefinitionId)
		{
			/*
			if (updateSkin) {
				// save it to restore it latter
				itemIDHighOriginals[itemDefinitionIndex] = *weaponObject->m_iItemIDHigh();
				// force csgo to use callbacks
				*weaponObject->m_iItemIDHigh() = -1;

				// live update ...
				//weaponObject->PostDataUpdate(DATA_UPDATE_CREATED);
				//weaponObject->OnDataChanged(DATA_UPDATE_CREATED);
			}
			else if (*weaponObject->m_iItemIDHigh() != itemIDHighOriginals[itemDefinitionIndex]) {
				// restore the original ID High
				*weaponObject->m_iItemIDHigh() = itemIDHighOriginals[itemDefinitionIndex];
			}
			*/

			*weaponObject->m_iItemDefinitionIndex() = knifeDefinitionId;
			*weaponObject->m_nModelIndex() = knifeModelId;

			((C_BaseCombatWeapon*)weaponObject)->setViewModelIndex(knifeModelId);

			*weaponObject->m_nFallbackPaintKit() = knifePaint;
			*weaponObject->m_iEntityQuality() = 3;
			*weaponObject->m_flFallbackWear() = 0;
			*weaponObject->m_nFallbackSeed() = 0;

			*weaponObject->m_iItemIDHigh() = -1;
		}

		VMProtectEnd();
	}

	void applySkin(int itemDefinitionIndex, C_BaseAttributableItem* weaponObject, skin* s, player_info_t* info) {

		VMProtectBeginMutation("skinchanger::applySkin");

		// update only if I change its paint
		if (s->paint == 0)
			return;

		// it's not my weapon
		if (info->xuidlow != *weaponObject->m_OriginalOwnerXuidLow() || info->xuidhigh != *weaponObject->m_OriginalOwnerXuidHigh())
			return;

		/*
		if (updateSkin) {
			// save it to restore it latter
			itemIDHighOriginals[itemDefinitionIndex] = *weaponObject->m_iItemIDHigh();
			// force csgo to use callbacks
			*weaponObject->m_iItemIDHigh() = -1;

			// live update ...
			//weaponObject->PostDataUpdate(DATA_UPDATE_CREATED);
			//weaponObject->OnDataChanged(DATA_UPDATE_CREATED);
		}
		else if (*weaponObject->m_iItemIDHigh() != itemIDHighOriginals[itemDefinitionIndex]) {
			// restore the original ID High
			*weaponObject->m_iItemIDHigh() = itemIDHighOriginals[itemDefinitionIndex];
		}
		*/

		// apply config
		*weaponObject->m_nFallbackPaintKit() = s->paint;
		*weaponObject->m_flFallbackWear() = s->wear;
		*weaponObject->m_nFallbackSeed() = s->seed;
		*weaponObject->m_iEntityQuality() = s->quality;
		// fix stattrack
		*weaponObject->m_iAccountID() = info->xuidlow;
		// force csgo to use callbacks
		*weaponObject->m_iItemIDHigh() = -1;

		VMProtectEnd();
	}

	void applyWeaponSkins() {

		VMProtectBeginMutation("skinchanger::applyWeaponSkins");

		auto localPlayer = game::getLocalPlayer();

		if (!localPlayer)
			return;

		if (!localPlayer->isAlive())
			return;

		int team = localPlayer->m_iTeamNum();

		CBaseHandle m_hActiveWeapon = localPlayer->m_hActiveWeapon();

		if (!m_hActiveWeapon)
			return;

		auto myWeapons = localPlayer->myWeapons();

		if (!myWeapons)
			return;

		player_info_t info;

		if (!interfaces::engineClient->GetPlayerInfo(localPlayer->index(), &info))
			return;

		for (size_t i = 0; myWeapons[i] != INVALID_EHANDLE_INDEX; i++) {

			auto weapon = (C_BaseAttributableItem*)(interfaces::clientEntityList->GetClientEntityFromHandle(myWeapons[i]));

			if (!weapon)
				continue;

			if (!weapon->IsBaseCombatWeapon())
				continue;

			if (info.xuidlow != *weapon->m_OriginalOwnerXuidLow() || info.xuidhigh != *weapon->m_OriginalOwnerXuidHigh())
				continue;

			applyStickerHooks((int*)weapon);

			int itemDefinitionIndex = *weapon->m_iItemDefinitionIndex();

			if (!itemDefinitionIndex)
				continue;

			// changing skin
			
			if (((C_BaseCombatWeapon*)weapon)->IsKnife())
			{
				applyKnifeSkin(itemDefinitionIndex, weapon, &info);

				/*
				if (team == TEAM_COUNTER_TERRORIST) // CT
				{
					int knifeModelId = interfaces::modelInfo->GetModelIndex(knifeModelNames.at(config::visual.skins.ctSkins.knifeId).c_str());
					int knifeDefinitionId = getKnifeDefinitionIndex(config::visual.skins.ctSkins.knifeId);

					if (currentWeapon->itemDefinitionIndex() == WEAPON_KNIFE ||
						currentWeapon->itemDefinitionIndex() == WEAPON_KNIFE_T ||
						currentWeapon->itemDefinitionIndex() == knifeDefinitionId)
					{
						currentWeapon->setItemDefinitionIndex(knifeDefinitionId);

						currentWeapon->setModelIndex(knifeModelId);
						currentWeaponBase->setViewModelIndex(knifeModelId);

						currentWeapon->setFallbackPaintKit(config::visual.skins.ctSkins.knifePaint);

						currentWeapon->setEntityQuality(3);
						currentWeapon->setFallbackWear(0);
						currentWeapon->setFallbackSeed(0);

						currentWeapon->setItemIDHigh(-1);
					}
				}

				else if (team == TEAM_TERRORIST) // T
				{
					//KNIFE_SKIN(tSkins)

					int knifeModelId = interfaces::modelInfo->GetModelIndex(knifeModelNames.at(config::visual.skins.tSkins.knifeId).c_str());
					int knifeDefinitionId = getKnifeDefinitionIndex(config::visual.skins.tSkins.knifeId);

					if (currentWeapon->itemDefinitionIndex() == WEAPON_KNIFE ||
						currentWeapon->itemDefinitionIndex() == WEAPON_KNIFE_T ||
						currentWeapon->itemDefinitionIndex() == knifeDefinitionId)
					{
						currentWeapon->setItemDefinitionIndex(knifeDefinitionId);

						currentWeapon->setModelIndex(knifeModelId);
						currentWeaponBase->setViewModelIndex(knifeModelId);

						currentWeapon->setFallbackPaintKit(config::visual.skins.tSkins.knifePaint);

						currentWeapon->setEntityQuality(3);
						currentWeapon->setFallbackWear(0);
						currentWeapon->setFallbackSeed(0);

						currentWeapon->setItemIDHigh(-1);
					}
				}*/
			}
			else {

				if (team == TEAM_COUNTER_TERRORIST) // CT
				{
					switch (*weapon->m_iItemDefinitionIndex())
					{
						SKIN_GROUPE(ctSkins, weapon)
					}
				}

				else if (team == TEAM_TERRORIST) // T
				{
					switch (*weapon->m_iItemDefinitionIndex())
					{
						SKIN_GROUPE(tSkins, weapon)
					}
				}
			}

			// change the knife model
			changeViewModel(weapon);
		}

		// use this to restore at the ID next call
		if(updateSkin)
			updateSkin = false;

		VMProtectEnd();
	}

	void frameStageNotify(int frameStage) {

		VMProtectBeginMutation("skinchanger::frameStageNotify");

		if (config::visual.skins.enable && frameStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) 
			applyWeaponSkins();

		if (config::visual.playerModel.enable)
			applyPlayerModel(frameStage);
		
		entityLoop(frameStage);

		VMProtectEnd();
	}
}