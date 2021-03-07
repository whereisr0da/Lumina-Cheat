#pragma once

#ifndef misc_h

#define misc_h

#include <string>

#include "../math/matrix3x4_t.h"
#include "../math/CUtlVector.h"

class NoticeText_t
{
public:
	wchar_t m_nString[ 512 ]; //0x0000 
	char pad_0x0400[ 0xC ]; //0x0400
	float set; //0x040C
	float m_flStartTime; //0x0410 
	float m_flStartTime2; //0x0414 
	float m_flLifeTimeModifier; //0x0418 
	char pad_0x041C[ 0x4 ]; //0x041C
}; //Size=0x420

class SFHudDeathNoticeAndBotStatus
{
public:
	char pad_0x00[ 0x68 ];
	CUtlVector<NoticeText_t>m_nDeathNotices;
};

extern SFHudDeathNoticeAndBotStatus* g_pDeathNotice;

class CUserCmd
{
public:
	virtual ~CUserCmd() {};
	int		command_number;
	int		tick_count;
	Vector	viewangles;
	Vector	aimdirection;
	float	forwardmove;
	float	sidemove;
	float	upmove;
	int		buttons;
	byte    impulse;
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;
	short	mousedx;
	short	mousedy;
	bool	hasbeenpredicted;
	char	pad_0x4C[ 0x18 ];
};

class CViewSetup
{
public:
	int			x, x_old;
	int			y, y_old;
	int			width, width_old;
	int			height, height_old;
	bool		m_bOrtho;
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;
	bool		m_bCustomViewMatrix;
	matrix3x4_t	m_matCustomViewMatrix;
	char		pad_0x68[ 0x48 ];
	float		fov;
	float		fovViewmodel;
	Vector		origin;
	QAngle		angles;
	float		zNear;
	float		zFar;
	float		zNearViewmodel;
	float		zFarViewmodel;
	float		m_flAspectRatio;
	float		m_flNearBlurDepth;
	float		m_flNearFocusDepth;
	float		m_flFarFocusDepth;
	float		m_flFarBlurDepth;
	float		m_flNearBlurRadius;
	float		m_flFarBlurRadius;
	int			m_nDoFQuality;
	int			m_nMotionBlurMode;
	float		m_flShutterTime;
	Vector		m_vShutterOpenPosition;
	QAngle		m_shutterOpenAngles;
	Vector		m_vShutterClosePosition;
	QAngle		m_shutterCloseAngles;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;
	int			m_EdgeBlur;
};

class VarMapEntry_t
{
public:
	unsigned short type;
	unsigned short m_bNeedsToInterpolate;	// Set to false when this var doesn't
											// need Interpolate() called on it anymore.
	void *data;
	void *watcher;
};

class Quaternion				// same data-layout as engine's vec4_t,
{								//		which is a float[4]
public:
	inline Quaternion( void ) {}
	inline Quaternion( float ix, float iy, float iz, float iw ) : x( ix ), y( iy ), z( iz ), w( iw ) {}

	inline void Init( float ix = 0.0f, float iy = 0.0f, float iz = 0.0f, float iw = 0.0f ) { x = ix; y = iy; z = iz; w = iw; }

	float* Base() { return ( float* )this; }
	const float* Base() const { return ( float* )this; }

	float x, y, z, w;
};

class ALIGN16 QuaternionAligned : public Quaternion
{
public:
	inline QuaternionAligned( void ) {};
	inline QuaternionAligned( float X, float Y, float Z, float W )
	{
		Init( X, Y, Z, W );
	}
public:
	explicit QuaternionAligned( const Quaternion &vOther )
	{
		Init( vOther.x, vOther.y, vOther.z, vOther.w );
	}

	QuaternionAligned& operator=( const Quaternion &vOther )
	{
		Init( vOther.x, vOther.y, vOther.z, vOther.w );
		return *this;
	}
};

class C_AnimationLayer
{
public:
	char  pad_0000[ 20 ];
	uint32_t m_nOrder; //0x0014
	uint32_t m_nSequence; //0x0018
	float_t m_flPrevCycle; //0x001C
	float_t m_flWeight; //0x0020
	float_t m_flWeightDeltaRate; //0x0024
	float_t m_flPlaybackRate; //0x0028
	float_t m_flCycle; //0x002C
	void *m_pOwner; //0x0030 // player's thisptr
	char  pad_0038[ 4 ]; //0x0034
};

class ClientClass;
class CEventInfo
{
public:
	uint16_t classID; //0x0000 0 implies not in use
	char pad_0002[ 2 ]; //0x0002 
	float fire_delay; //0x0004 If non-zero, the delay time when the event should be fired ( fixed up on the client )
	char pad_0008[ 4 ]; //0x0008
	ClientClass *pClientClass; //0x000C
	void *pData; //0x0010 Raw event data
	char pad_0014[ 48 ]; //0x0014
}; //Size: 0x0044

class C_TEFireBullets
{
public:
	char pad[ 12 ];
	int		m_iPlayer; //12
	int _m_iItemDefinitionIndex;
	Vector	_m_vecOrigin;
	QAngle	m_vecAngles;
	int		_m_iWeaponID;
	int		m_iMode;
	int		m_iSeed;
	float	m_flSpread;
};

struct Item_t
{
	Item_t( std::string model, std::string icon = "" ) :
		model( model ),
		icon( icon )
	{
	}

	std::string model;
	std::string icon;
};

struct WeaponName_t
{
	WeaponName_t( int definition_index, std::string name ) :
		definition_index( definition_index ),
		name( name )
	{
	}

	int definition_index = 0;
	std::string name = nullptr;
};

struct QualityName_t
{
	QualityName_t( int index, std::string name ) :
		index( index ),
		name( name )
	{
	}

	int index = 0;
	std::string name;
};

#endif