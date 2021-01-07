#pragma once

struct virtualmeshlist_t;


class ITraceListData
{
public:
	virtual ~ITraceListData() {}

	virtual void Reset() = 0;
	virtual bool IsEmpty() = 0;
	// CanTraceRay will return true if the current volume encloses the ray
	// NOTE: The leaflist trace will NOT check this.  Traces are intersected
	// against the culled volume exclusively.
	virtual bool CanTraceRay( const Ray_t &ray ) = 0;
};

class IEntityEnumerator
{
public:
	// This gets called with each handle
	virtual bool EnumEntity( IHandleEntity *pHandleEntity ) = 0;
};


struct BrushSideInfo_t
{
	Vector plane;			// The plane of the brush side
	float planec;
	unsigned short bevel;	// Bevel plane?
	unsigned short thin;	// Thin?
};

enum DebugTraceCounterBehavior_t
{
	kTRACE_COUNTER_SET = 0,
	kTRACE_COUNTER_INC,
};

class IEngineTrace
{
public:
	// Returns the contents mask + entity at a particular world-space position
	virtual int		GetPointContents( const Vector &vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = NULL ) = 0;

	// Returns the contents mask of the world only @ the world-space position (static props are ignored)
	virtual int		GetPointContents_WorldOnly( const Vector &vecAbsPosition, int contentsMask = MASK_ALL ) = 0;

	// Get the point contents, but only test the specific entity. This works
	// on static props and brush models.
	//
	// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
	// bFailed to true if bFailed is non-null.
	virtual int		GetPointContents_Collideable( ICollideable *pCollide, const Vector &vecAbsPosition ) = 0;

	// Traces a ray against a particular entity
	virtual void	ClipRayToEntity( const Ray_t &ray, unsigned int fMask, IHandleEntity *pEnt, trace_t *pTrace ) = 0;

	// Traces a ray against a particular entity
	virtual void	ClipRayToCollideable( const Ray_t &ray, unsigned int fMask, ICollideable *pCollide, trace_t *pTrace ) = 0;

	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void	TraceRay( const Ray_t &ray, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace ) = 0;

	// A version that sets up the leaf and entity lists and allows you to pass those in for collision.
	virtual void	SetupLeafAndEntityListRay( const Ray_t &ray, ITraceListData *pTraceData ) = 0;
	virtual void    SetupLeafAndEntityListBox( const Vector &vecBoxMin, const Vector &vecBoxMax, ITraceListData *pTraceData ) = 0;
	virtual void	TraceRayAgainstLeafAndEntityList( const Ray_t &ray, ITraceListData *pTraceData, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace ) = 0;

	// A version that sweeps a collideable through the world
	// abs start + abs end represents the collision origins you want to sweep the collideable through
	// vecAngles represents the collision angles of the collideable during the sweep
	virtual void	SweepCollideable( ICollideable *pCollide, const Vector &vecAbsStart, const Vector &vecAbsEnd,
									  const QAngle &vecAngles, unsigned int fMask, ITraceFilter *pTraceFilter, trace_t *pTrace ) = 0;

	// Enumerates over all entities along a ray
	// If triggers == true, it enumerates all triggers along a ray
	virtual void	EnumerateEntities( const Ray_t &ray, bool triggers, IEntityEnumerator *pEnumerator ) = 0;

	// Same thing, but enumerate entitys within a box
	virtual void	EnumerateEntities( const Vector &vecAbsMins, const Vector &vecAbsMaxs, IEntityEnumerator *pEnumerator ) = 0;

	// Convert a handle entity to a collideable.  Useful inside enumer
	virtual ICollideable *GetCollideable( IHandleEntity *pEntity ) = 0;

	// HACKHACK: Temp for performance measurments
	virtual int GetStatByIndex( int index, bool bClear ) = 0;

	//finds brushes in an AABB, prone to some false positives
	virtual void lolignorethisaswellrifk() = 0;

	//Creates a CPhysCollide out of all displacements wholly or partially contained in the specified AABB
	virtual void GetCollidableFromDisplacementsInAABB() = 0;

	// gets the number of displacements in the world
	virtual int GetNumDisplacements() = 0;

	// gets a specific diplacement mesh
	virtual void GetDisplacementMesh( int nIndex, virtualmeshlist_t *pMeshTriList ) = 0;

	//retrieve brush planes and contents, returns true if data is being returned in the output pointers, false if the brush doesn't exist
	virtual bool lolignorethis() = 0;

	virtual bool PointOutsideWorld( const Vector &ptTest ) = 0; //Tests a point to see if it's outside any playable area

																// Walks bsp to find the leaf containing the specified point
	virtual int GetLeafContainingPoint( const Vector &ptTest ) = 0;

	virtual ITraceListData *AllocTraceListData() = 0;
	virtual void FreeTraceListData( ITraceListData * ) = 0;

	/// Used only in debugging: get/set/clear/increment the trace debug counter. See comment below for details.
	virtual int GetSetDebugTraceCounter( int value, DebugTraceCounterBehavior_t behavior ) = 0;

	void clip_ray_to_player( const Vector& src, const Vector& end, const uint32_t mask, C_BaseEntity* player, ITraceFilter* filter, trace_t* t )
	{
		if (!player || player->IsDormant())
			return;

		if ( filter && !filter->ShouldHitEntity( player, mask ) )
			return;

		trace_t t_new{};
		Ray_t r{};
		r.Init( src, end );

		ClipRayToEntity( r, mask, player, &t_new );
		if ( t_new.fraction < t->fraction )
			*t = t_new;
	}
};

extern IEngineTrace* g_pTrace;