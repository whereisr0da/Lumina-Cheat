#ifndef defines_h

#define defines_h

typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;

#define M_PI		(float)3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI / 180.f) )

#define RandomInt( min, max ) ( rand() % ( max - min + 1 ) + min)
#define RandomFlt( min, max ) ( min + 1 ) + ( ( ( float ) rand() ) / ( float ) RAND_MAX ) * ( max - ( min + 1 ) );

#define FLOAT32_NAN_BITS     (uint32)0x7FC00000	// not a number!
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )
#define VEC_T_NAN FLOAT32_NAN

#define DECL_ALIGN(x)			__declspec( align( x ) )

#define ALIGN4 DECL_ALIGN(4)
#define ALIGN8 DECL_ALIGN(8)
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN32 DECL_ALIGN(32)
#define ALIGN128 DECL_ALIGN(128)


#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)

#define INRANGE( x, a, b )    ( x >= a && x <= b ) 
#define getBits( x )    ( INRANGE( ( x&( ~0x20 ) ),'A','F') ? ( ( x&( ~0x20 ) ) - 'A' + 0xa ) : ( INRANGE( x, '0', '9') ? x - '0' : 0 ) )
#define getByte( x )    ( getBits( x[ 0 ] ) << 4 | getBits( x[ 1 ] ) )

#define tick_interval			( g_pGlobals->interval_per_tick )

#define time_to_ticks( dt )		( (int)( 0.5f + (float)(dt) / tick_interval ) )
#define ticks_to_time( t )		( tick_interval *( t ) )
#define round_to_ticks( t )		( tick_interval * time_to_ticks( t ) )

#define IN_ATTACK				(1 << 0)
#define IN_JUMP					(1 << 1)
#define IN_DUCK					(1 << 2)
#define IN_FORWARD				(1 << 3)
#define IN_BACK					(1 << 4)
#define IN_USE					(1 << 5)
#define IN_CANCEL				(1 << 6)
#define IN_LEFT					(1 << 7)
#define IN_RIGHT				(1 << 8)
#define IN_MOVELEFT				(1 << 9)
#define IN_MOVERIGHT			(1 << 10)
#define IN_ATTACK2				(1 << 11)
#define IN_RUN					(1 << 12)
#define IN_RELOAD				(1 << 13)
#define IN_ALT1					(1 << 14)
#define IN_ALT2					(1 << 15)
#define IN_SCORE				(1 << 16)
#define IN_SPEED				(1 << 17)
#define IN_WALK					(1 << 18)
#define IN_ZOOM					(1 << 19)
#define IN_WEAPON1				(1 << 20)
#define IN_WEAPON2				(1 << 21)
#define IN_BULLRUSH				(1 << 22)

#define	FL_ONGROUND				(1 << 0)	
#define FL_DUCKING				(1 << 1)	
#define	FL_WATERJUMP			(1 << 3)	
#define FL_ONTRAIN				(1 << 4) 
#define FL_INRAIN				(1 << 5)	
#define FL_FROZEN				(1 << 6) 
#define FL_ATCONTROLS			(1 << 7) 
#define	FL_CLIENT				(1 << 8)	
#define FL_FAKECLIENT			(1 << 9)	
#define	FL_INWATER				(1 << 10)

#define TEXTURE_GROUP_LIGHTMAP						_w( "Lightmaps" )
#define TEXTURE_GROUP_WORLD							_w( "World textures" )
#define TEXTURE_GROUP_MODEL							_w( "Model textures" )
#define TEXTURE_GROUP_VGUI							_w( "VGUI textures" )
#define TEXTURE_GROUP_PARTICLE						_w( "Particle textures" )
#define TEXTURE_GROUP_DECAL							_w( "Decal textures" )
#define TEXTURE_GROUP_SKYBOX						_w( "SkyBox textures" )
#define TEXTURE_GROUP_CLIENT_EFFECTS				_w( "ClientEffect textures" )
#define TEXTURE_GROUP_OTHER							_w( "Other textures" )
#define TEXTURE_GROUP_PRECACHED						_w( "Precached" )				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						_w( "CubeMap textures" )
#define TEXTURE_GROUP_RENDER_TARGET					_w( "RenderTargets" )
#define TEXTURE_GROUP_UNACCOUNTED					_w( "Unaccounted textures" )	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			_w( "Static Indices" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		_w( "Displacement Verts" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	_w( "Lighting Verts" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	_w( "World Verts" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	_w( "Model Verts" )
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	_w( "Other Verts" )
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			_w( "Dynamic Indices" )
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			_w( "Dynamic Verts" )
#define TEXTURE_GROUP_DEPTH_BUFFER					_w( "DepthBuffer" )
#define TEXTURE_GROUP_VIEW_MODEL					_w( "ViewModel" )
#define TEXTURE_GROUP_PIXEL_SHADERS					_w( "Pixel Shaders" )
#define TEXTURE_GROUP_VERTEX_SHADERS				_w( "Vertex Shaders" )
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			_w( "RenderTarget Surfaces" )
#define TEXTURE_GROUP_MORPH_TARGETS					_w( "Morph Targets" )

#define MAX_AREA_STATE_BYTES		32
#define MAX_AREA_PORTAL_STATE_BYTES 24

#define CHAR_TEX_CONCRETE	'C'			// texture types
#define CHAR_TEX_METAL		'M'
#define CHAR_TEX_DIRT		'D'
#define CHAR_TEX_VENT		'V'
#define CHAR_TEX_GRATE		'G'
#define CHAR_TEX_TILE		'T'
#define CHAR_TEX_SLOSH		'S'
#define CHAR_TEX_WOOD		'W'
#define CHAR_TEX_COMPUTER	'P'
#define CHAR_TEX_GLASS		'Y'
#define CHAR_TEX_FLESH		'F'
#define CHAR_TEX_SNOW		'N'
#define CHAR_TEX_PLASTIC	'L'
#define CHAR_TEX_CARDBOARD	'U'

#define	DAMAGE_NO				0
#define DAMAGE_EVENTS_ONLY		1		// Call damage functions, but don't modify health
#define	DAMAGE_YES				2
#define	DAMAGE_AIM				3

#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10	

#define	HITGROUP_HEAD_FLAG      (1<<0)
#define	HITGROUP_CHEST_FLAG		(1<<1)
#define	HITGROUP_STOMACH_FLAG	(1<<2)
#define HITGROUP_LEFTARM_FLAG	(1<<3)
#define HITGROUP_RIGHTARM_FLAG	(1<<4)
#define HITGROUP_LEFTLEG_FLAG	(1<<5)
#define HITGROUP_RIGHTLEG_FLAG	(1<<6)
#define HITGROUP_ALL_FLAG (1<<7)

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define	SURF_LIGHT		0x0001		// value will hold the light strength
#define	SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define	SURF_SKY		0x0004		// don't draw, but add to skybox
#define	SURF_WARP		0x0008		// turbulent water warp
#define	SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define	SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define	SURF_NODRAW		0x0080	// don't bother referencing the texture

#define	SURF_HINT		0x0100	// make a primary bsp splitter

#define	SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOPAINT	SURF_NODECALS	// the surface can not have paint placed on it
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface 
#define SURF_HITBOX		0x8000	// surface is part of a hitbox

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define	MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define	MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define	MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)


#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT		0x00000200	// bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK	0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0	0x00000400	// bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1	0x00000800	
#define BONE_USED_BY_VERTEX_LOD2	0x00001000  
#define BONE_USED_BY_VERTEX_LOD3	0x00002000
#define BONE_USED_BY_VERTEX_LOD4	0x00004000
#define BONE_USED_BY_VERTEX_LOD5	0x00008000
#define BONE_USED_BY_VERTEX_LOD6	0x00010000
#define BONE_USED_BY_VERTEX_LOD7	0x00020000
#define BONE_USED_BY_BONE_MERGE		0x00040000	// bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define ATTACHMENT_FLAG_WORLD_ALIGN 0x10000

#define INVALID_EHANDLE_INDEX 0xFFFFFFFF


#define NET_FRAMES_BACKUP 64 // must be power of 2. 
#define NET_FRAMES_MASK ( NET_FRAMES_BACKUP - 1 )

template<class T> const T&
clamp( const T& x, const T& lower, const T& upper ) { return min( upper, max( x, lower ) ); }

inline float BitsToFloat( uint32 i )
{
	union Convertor_t
	{
		float f;
		unsigned long ul;
	}tmp;
	tmp.ul = i;
	return tmp.f;
}

inline float sqrt2( float sqr )
{
	float root = 0;

	__asm
	{
		sqrtss xmm0, sqr
		movss root, xmm0
	}

	return root;
}

#endif // !defines_h