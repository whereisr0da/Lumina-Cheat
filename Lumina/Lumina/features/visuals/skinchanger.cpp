#include "skinchanger.h"

#include "../../sdk/interfaces.h"
#include "../../common/includes.h"
#include "../../common/config.h"
#include "../../common/common.h"

namespace skinchanger {

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

	void updateAnimations(C_BaseCombatWeapon* ent) {

		VMProtectBeginMutation("skinchanger::updateAnimations");

		// from : legendware

		int seq = *ent->m_nSequence();

		int itemDefinitionIndex = *((C_BaseAttributableItem*)ent)->m_iItemDefinitionIndex();

		// check if this knife needs extra fixing.
		if (itemDefinitionIndex == WEAPON_KNIFE_BUTTERFLY ||
			itemDefinitionIndex == WEAPON_KNIFE_FALCHION ||
			itemDefinitionIndex == WEAPON_KNIFE_SURVIVAL_BOWIE ||
			itemDefinitionIndex == WEAPON_KNIFE_OUTDOOR) {

			// fix the idle sequences.
			if (seq == 1 || seq == 2) {
				// set the animation to be completed.
				*ent->m_flCycle() = 0.999f;

				// cycle change, re-render.
				interfaces::invalidatePhysicsRecursive((void*)ent, ANIMATION_CHANGED);
			}
		}

		VMProtectEnd();
	}

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
			return;

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

	void applyKnifeSkin(int itemDefinitionIndex, C_BaseAttributableItem* weaponObject, player_info_t* info, bool updateSkin) {

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
			
			*weaponObject->m_nModelIndex() = knifeModelId;

			((C_BaseCombatWeapon*)weaponObject)->setViewModelIndex(knifeModelId);

			if (updateSkin) {

				*weaponObject->m_iItemDefinitionIndex() = knifeDefinitionId;
				*weaponObject->m_nFallbackPaintKit() = knifePaint;
				*weaponObject->m_iEntityQuality() = 3;
				*weaponObject->m_flFallbackWear() = 0;
				*weaponObject->m_nFallbackSeed() = 0;

				*weaponObject->m_iItemIDHigh() = -1;
			}
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

			// sticker fix
			if (((Entity*)weapon)->is(HASH("CPredictedViewModel"))) {

				if (!((C_BaseCombatWeapon*)weapon)->IsKnife())
					continue;

				if (info.xuidlow != *weapon->m_OriginalOwnerXuidLow() || info.xuidhigh != *weapon->m_OriginalOwnerXuidHigh())
					continue;

				int itemDefinitionIndex = *weapon->m_iItemDefinitionIndex();

				// change model first lap
				applyKnifeSkin(itemDefinitionIndex, weapon, &info, false);

				// change the knife model
				changeViewModel(weapon);

				// fix animtions
				updateAnimations((C_BaseCombatWeapon*)weapon);
			}

			if (!weapon->IsBaseCombatWeapon())
				continue;

			if (info.xuidlow != *weapon->m_OriginalOwnerXuidLow() || info.xuidhigh != *weapon->m_OriginalOwnerXuidHigh())
				continue;

			int itemDefinitionIndex = *weapon->m_iItemDefinitionIndex();

			if (!itemDefinitionIndex)
				continue;

			// changing skin
			if (((C_BaseCombatWeapon*)weapon)->IsKnife())
			{
				applyKnifeSkin(itemDefinitionIndex, weapon, &info, true);
			}
			else {

				bool weaponSkinChanged = false;

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

				// apply sticker ONLY on changed weapons AFTER changing skin and knife model
				if(weaponSkinChanged)
					applyStickerHooks((int*)weapon);
			}
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