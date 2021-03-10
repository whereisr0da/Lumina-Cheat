#include "backtrack.h"

#include "../../sdk/interfaces.h"
#include "../../common/config.h"

namespace backtrack {

	std::deque<stored_records> records[65];
	backtrack_convars vars;

	void init() {

		VMProtectBeginMutation("backtrack::init");

		vars.update_rate = (ConVar*)interfaces::console->get_convar(StringHeavy("cl_updaterate"));
		vars.max_update_rate = (ConVar*)interfaces::console->get_convar(StringHeavy("sv_maxupdaterate"));
		vars.min_interp_ratio = (ConVar*)interfaces::console->get_convar(StringHeavy("sv_client_min_interp_ratio"));
		vars.max_interp_ratio = (ConVar*)interfaces::console->get_convar(StringHeavy("sv_client_max_interp_ratio"));
		vars.max_unlag = (ConVar*)interfaces::console->get_convar(StringHeavy("sv_maxunlag"));
		vars.interp = (ConVar*)interfaces::console->get_convar(StringHeavy("cl_interp"));
		vars.interp_ratio = (ConVar*)interfaces::console->get_convar(StringHeavy("cl_interp_ratio"));

		records->clear();

		VMProtectEnd();
	}

	float get_lerp_time() {

		//VMProtectBeginMutation("backtrack::get_lerp_time");

		JUNK_0(tmp0)
			tmp0:

		auto ratio = std::clamp(vars.interp_ratio->get_float(), (vars.min_interp_ratio->get_float() != 1.f) ? vars.min_interp_ratio->get_float() : 1.f, vars.max_interp_ratio->get_float());

		JUNK_0(tmp1)
			tmp1:

		auto result = max(vars.interp->get_float(), (ratio / ((vars.max_update_rate) ? vars.max_update_rate->get_float() : vars.update_rate->get_float())));

		JUNK_0(tmp2) 
			tmp2:

		//VMProtectEnd(); 
		
		return result;
	}

	void update() {

		VMProtectBeginMutation("backtrack::update");

		auto local_player = game::getLocalPlayer();

		if (!config::cheats.backtrack || !local_player || !local_player->isAlive()) {

			if (!records->empty())
				records->clear();

			return;
		}

		for (int i = 1; i <= interfaces::globals->maxClients; i++) {

			auto entity = (Entity*)(interfaces::clientEntityList->GetClientEntity(i));

			if (!entity || entity == local_player || entity->m_bDormant() || !entity->isAlive() || entity->m_iTeamNum() == local_player->m_iTeamNum()) {

				if (records[i].size() > 2)
					records[i].clear();

				continue;
			}

			auto& rec = records[i];

			for (auto r = rec.begin(); r != rec.end();) {
				if (!valid_tick(r->simulation_time))
					r = rec.erase(r);
				else
					r++;
			}

			if (records[i].size() && (records[i].front().simulation_time == entity->simulation_time()))
				continue;

			while (records[i].size() > 3 && records[i].size() > static_cast<size_t>(time_to_ticks_2(static_cast<float>(config::cheats.backtrackTime) / 1000.f)))
				records[i].pop_back();

			auto var_map = reinterpret_cast<uintptr_t>(entity) + 0x24;
			auto vars_count = *reinterpret_cast<int*>(static_cast<uintptr_t>(var_map) + 0x14);

			for (int j = 0; j < vars_count; j++)
				*reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(var_map) + j * 0xC) = 0;

			stored_records record{ };
			record.head = get_hitbox_position(entity, HITBOX_HEAD);
			record.simulation_time = entity->simulation_time();

			entity->setup_bones(record.matrix, 128, 0x7FF00, interfaces::globals->curtime);

			records[i].push_front(record);
		}

		VMProtectEnd();
	}

	void run(void* cmd_) {

		VMProtectBeginMutation("backtrack::run");

		if (!config::cheats.backtrack)
			return;

		CUserCmd* cmd = (CUserCmd*)cmd_;

		if (!(cmd->buttons & IN_ATTACK))
			return;

		auto local_player = game::getLocalPlayer();

		if (!local_player)
			return;

		auto best_fov{ 255.f };
		Entity* best_target{ };
		int besst_target_index{ };
		Vector best_target_head_position{ };
		int best_record{ };

		for (int i = 1; i <= interfaces::globals->maxClients; i++) {

			auto entity = (Entity*)(interfaces::clientEntityList->GetClientEntity(i));

			if (!entity || entity == local_player || entity->m_bDormant() || !entity->isAlive() || entity->m_iTeamNum() == local_player->m_iTeamNum())
				continue;

			auto head_position = entity->get_bone_position(8);

			auto angle = math::calculate_angle(local_player->get_eye_pos(), head_position, cmd->viewangles);

			auto fov = std::hypotf(angle.x, angle.y);

			if (fov < best_fov) {
				best_fov = fov;
				best_target = entity;
				besst_target_index = i;
				best_target_head_position = head_position;
			}
		}

		if (best_target) {

			if (records[besst_target_index].size() <= 3)
				return;

			best_fov = 255.f;

			for (size_t i = 0; i < records[besst_target_index].size(); i++) {

				auto record = &records[besst_target_index][i];

				if (!record || !valid_tick(record->simulation_time))
					continue;

				auto angle = math::calculate_angle(local_player->get_eye_pos(), record->head, cmd->viewangles);

				auto fov = std::hypotf(angle.x, angle.y);

				if (fov < best_fov) {
					best_fov = fov;
					best_record = i;
				}
			}
		}

		if (best_record) {

			auto record = records[besst_target_index][best_record];
			cmd->tick_count = time_to_ticks_2(record.simulation_time);
		}

		VMProtectEnd();
	}

	Vector get_hitbox_position(Entity* entity, int hitbox_id) {

		//VMProtectBeginMutation("backtrack::get_hitbox_position");

		matrix3x4_t bone_matrix[128];

		// NOTE : I can't use mutation on this function due to fps, so, I use random JUNK_0 just for sign (useless)

		JUNK_0(tmp0)
			tmp0:

		if (entity->setup_bones(bone_matrix, 128, BONE_USED_BY_HITBOX, 0.0f)) {

			JUNK_0(tmp1) 
				tmp1:

			auto studio_model = interfaces::modelInfo->GetStudioModel(entity->model());

			JUNK_0(tmp2)
				tmp2:

			if (studio_model) {

				auto hitbox = studio_model->pHitboxSet(0)->pHitbox(hitbox_id);

				JUNK_0(tmp3)
					tmp3:

				if (hitbox) {

					auto min = Vector{}, max = Vector{};

					JUNK_0(tmp4) 
						tmp4:

					math::transform_vector(hitbox->bbmin, bone_matrix[hitbox->bone], min);

					JUNK_0(tmp5)
						tmp5:

					math::transform_vector(hitbox->bbmax, bone_matrix[hitbox->bone], max);

					JUNK_0(tmp6)
						tmp6:

					return Vector((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f, (min.z + max.z) * 0.5f);
				}
			}
		}

		//VMProtectEnd();

		return Vector{};
	}

	bool valid_tick(float simtime) {

		//VMProtectBeginMutation("backtrack::valid_tick");

		auto network = interfaces::engineClient->GetNetChannelInfo();

		JUNK_0(tmp0) 
			tmp0:

		if (!network)
			return false;

		JUNK_0(tmp1) 
			tmp1:

		auto delta = std::clamp(network->GetLatency(0) + get_lerp_time(), 0.f, vars.max_unlag->get_float()) - (interfaces::globals->curtime - simtime);
		
		JUNK_0(tmp2)
			tmp2:

		bool result = std::fabsf(delta) <= 0.2f;

		JUNK_0(tmp3) 
			tmp3:

		//VMProtectEnd();
		
		return result;
	}


	int time_to_ticks_2(float time) {

		//VMProtectBeginMutation("backtrack::time_to_ticks_2");

		int result = static_cast<int>((0.5f + static_cast<float>(time) / interfaces::globals->interval_per_tick));

		JUNK_0(tmp0)
			tmp0:

		//VMProtectEnd();

		return result;
	}
}



