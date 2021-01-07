#pragma once

#ifndef csplayerresource_h

#define csplayerresource_h

#include "../netvars.h"

class Color;

class C_CSPlayerResource
{
public:
	OFFSET(int, get_c4_player, 0x161C)

	OFFSETRS( get_ping, int, 0x0AE4 )

};

//extern C_CSPlayerResource** g_ppPlayerResource;

#endif