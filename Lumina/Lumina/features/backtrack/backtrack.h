#ifndef backtrack_h

#define backtrack_h

#include "../../common/includes.h"

// modded from aristois


struct stored_records {
	Vector head;
	float simulation_time;
	matrix3x4_t matrix[128];
};

struct backtrack_convars {
	ConVar* update_rate;
	ConVar* max_update_rate;
	ConVar* interp;
	ConVar* interp_ratio;
	ConVar* min_interp_ratio;
	ConVar* max_interp_ratio;
	ConVar* max_unlag;
};

namespace backtrack {

	extern std::deque<stored_records> records[65];
	extern backtrack_convars vars;

	void update();
	void run(void*);
	Vector get_hitbox_position(Entity* entity, int hitbox_id);
	float get_lerp_time();
	int time_to_ticks_2(float time);
	bool valid_tick(float simtime);
	void init();
}

#endif // !backtrack_h