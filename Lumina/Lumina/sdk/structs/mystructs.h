#ifndef mystruct_h

#define mystruct_h

#include "Entity.h"

struct box {

	int x, y, w, h;

	box() = default;

	box(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

struct boxPoint {

	int x1, y1, x2, y2;

	boxPoint() = default;

	boxPoint(int x1, int y1, int x2, int y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
};

struct player_t {

	Entity* handle;
	bool dormant;
	bool enemie;
	bool alive;
	player_info_t* info;
	CCSWeaponData* weaponData;

	player_t() = default;

};

#endif // !mystruct_h