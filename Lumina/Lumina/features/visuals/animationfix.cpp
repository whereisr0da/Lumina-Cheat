#include "animationfix.h"
#include "../../common/includes.h"
#include "../../sdk/interfaces.h"
#include "skinchanger.h"

namespace animationfix {

	// from aristois

	recv_var_proxy_fn_ sequence_proxy_fn = nullptr;
	recv_var_proxy_fn_ recv_model_index;

	void hooked_recvproxy_viewmodel(c_recv_proxy_data_* p_data, void* p_struct, void* p_out) {

		VMProtectBeginMutation("aniamtionfix::hooked_recvproxy_viewmodel");

		auto localPlayer = game::getLocalPlayer();

		if(!localPlayer || !localPlayer->isAlive())
			return recv_model_index(p_data, p_struct, p_out);

		std::vector<int> knifeModelIndexs = {};

		// grab all knife model ids
		for (std::string knifeModel : skinchanger::knifeModelNames){
			knifeModelIndexs.push_back(interfaces::modelInfo->GetModelIndex(knifeModel.c_str()));
		}

		// if current viewmodel is knife
		if (std::find(knifeModelIndexs.begin(), knifeModelIndexs.end(), p_data->value.m_int) != knifeModelIndexs.end()) {

			int knifeId = localPlayer->m_iTeamNum() == TEAM_COUNTER_TERRORIST ? config::visual.skins.ctSkins.knifeId : config::visual.skins.tSkins.knifeId;

			// set the according model id
			p_data->value.m_int = knifeModelIndexs.at(knifeId);
		}

		// reset
		recv_model_index(p_data, p_struct, p_out);

		VMProtectEnd();
	}

	void set_view_model_sequence(const c_recv_proxy_data_* pDataConst, void* p_struct, void* p_out) noexcept {

		VMProtectBeginMutation("aniamtionfix::set_view_model_sequence");

		c_recv_proxy_data_* p_data = const_cast<c_recv_proxy_data_*>(pDataConst);

		C_BaseAttributableItem* player_view_model = (C_BaseAttributableItem*)(p_struct);

		if (!player_view_model)
			return sequence_proxy_fn(p_data, p_struct, p_out);

		auto localPlayer = game::getLocalPlayer();

		if (!localPlayer || !localPlayer->isAlive())
			return sequence_proxy_fn(p_data, p_struct, p_out);

		Entity* p_owner = (Entity*)(interfaces::clientEntityList->GetClientEntity(*player_view_model->m_hOwner() & 0xFFF));

		if (p_owner != localPlayer)
			return sequence_proxy_fn(p_data, p_struct, p_out);

		std::string sz_model = interfaces::modelInfo->GetModelName(interfaces::modelInfo->GetModel(*player_view_model->m_nModelIndex()));

		hash32_t modelHash = FNV1a::get(sz_model);

		int m_nSequence = p_data->value.m_int;

		if (modelHash == HASH("models/weapons/v_knife_butterfly.mdl")) {
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
		else if (modelHash == HASH("models/weapons/v_knife_falchion_advanced.mdl")) {
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
		else if (modelHash == HASH("models/weapons/v_knife_push.mdl")) {
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
		else if (modelHash == HASH("models/weapons/v_knife_survival_bowie.mdl")) {
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
		else if (modelHash == HASH("models/weapons/v_knife_ursus.mdl")) {
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
		else if (modelHash == HASH("models/weapons/v_knife_stiletto.mdl")) {
			switch (m_nSequence) {
			case SEQUENCE_DEFAULT_LOOKAT01:
				m_nSequence = RandomInt(12, 13);
				break;
			}
		}
		else if (modelHash == HASH("models/weapons/v_knife_widowmaker.mdl")) {
			switch (m_nSequence) {
			case SEQUENCE_DEFAULT_LOOKAT01:
				m_nSequence = RandomInt(14, 15);
				break;
			}
		}
		else if (modelHash == HASH("models/weapons/v_knife_cord.mdl")
			|| modelHash == HASH("models/weapons/v_knife_canis.mdl")
			|| modelHash == HASH("models/weapons/v_knife_outdoor.mdl")
			|| modelHash == HASH("models/weapons/v_knife_skeleton.mdl"))
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

		sequence_proxy_fn(p_data, p_struct, p_out);

		VMProtectEnd();
	}

	void knifeAnimationHook() {

		VMProtectBeginMutation("aniamtionfix::knifeAnimationHook");

		for (auto client_class = interfaces::baseClientDll->GetAllClasses(); client_class; client_class = client_class->m_pNext) {

			if (FNV1a::get(client_class->m_pNetworkName) == HASH("CBaseViewModel")) {
				const auto table = reinterpret_cast<recv_table_*>(client_class->m_pRecvTable);
				for (int nIndex = 0; nIndex < table->props_count; nIndex++) {
					recv_prop_* pProp = &table->props[nIndex];
					if (!pProp || FNV1a::get(pProp->prop_name) != HASH("m_nSequence"))
						continue;
					sequence_proxy_fn = static_cast<recv_var_proxy_fn_>(pProp->proxy_fn);
					pProp->proxy_fn = static_cast<recv_var_proxy_fn_>(set_view_model_sequence);
					break;
				}
				break;
			}
		}

		VMProtectEnd();
	}

	void init() {

		VMProtectBeginMutation("aniamtionfix::knifeAnimation");

		knifeAnimationHook();

		auto client_class = interfaces::baseClientDll->GetAllClasses();

		while (client_class) {

			const char* pszName = client_class->m_pRecvTable->table_name;

			if (FNV1a::get(pszName) == HASH("DT_BaseViewModel")) {
				for (int i = 0; i < client_class->m_pRecvTable->props_count; i++) {
					recv_prop_* pProp = &(client_class->m_pRecvTable->props[i]);
					const char* name = pProp->prop_name;
					if (FNV1a::get(name) == HASH("m_nModelIndex")) {
						recv_model_index = (recv_var_proxy_fn_)pProp->proxy_fn;
						pProp->proxy_fn = (recv_var_proxy_fn_)hooked_recvproxy_viewmodel;
					}
				}
			}

			client_class = client_class->m_pNext;
		}

		VMProtectEnd();
	}

}