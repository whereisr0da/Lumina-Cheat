#pragma once

class CCSGOPlayerAnimState
{
public:
	MFUNC( update( QAngle ang ), void( __vectorcall* )( void*, void*, float, float, float, void* ), offsets::update_anim_state )( nullptr, 0, ang.y, ang.x, nullptr );
	char            pad[3];
	char            bUnknown; //0x4
	char            pad2[91];
	void*           pBaseEntity; //0x60
	void*           pActiveWeapon; //0x64
	void*           pLastActiveWeapon; //0x68
	float           m_flLastClientSideAnimationUpdateTime; //0x6C
	int             m_iLastClientSideAnimationUpdateFramecount; //0x70
	float           m_flEyePitch; //0x74
	float           m_flEyeYaw; //0x78
	float           m_flPitch; //0x7C
	float           m_flGoalFeetYaw; //0x80
	float           m_flCurrentFeetYaw; //0x84
	float           m_flCurrentTorsoYaw; //0x88
	float           m_flUnknownVelocityLean; //0x8C //changes when moving/jumping/hitting ground
	float           m_flLeanAmount; //0x90
	char            pad4[4];
	float           m_flFeetCycle; //0x98 0 to 1
	float           m_flFeetYawRate; //0x9C 0 to 1
	float           m_fUnknown2;
	float           m_fDuckAmount; //0xA4
	float           m_fLandingDuckAdditiveSomething;
	float           m_fUnknown3;
	Vector          m_vOrigin;
	Vector          m_vLastOrigin;
	float           m_vVelocityX;
	float           m_vVelocityY;
	char            pad5[4];
	float           m_flUnknownFloat1;
	char            pad6[8];
	float           m_flUnknownFloat2;
	float           m_flUnknownFloat3;
	float           m_unknown;
	float           m_velocity;
	float           flUpVelocity; //0xF0
	float           m_flSpeedNormalized; //0xF4 //from 0 to 1
	float           m_flFeetSpeedForwardsOrSideWays; //0xF8 //from 0 to 2. something  is 1 when walking, 2.something when running, 0.653 when crouch walking
	float           m_flFeetSpeedUnknownForwardOrSideways; //0xFC //from 0 to 3. something
	float           m_flTimeSinceStartedMoving;
	float           m_flTimeSinceStoppedMoving;
	unsigned char   m_bOnGround; //0x108
	unsigned char   m_bInHitGroundAnimation; //0x109
	char            pad7[10];
	float           m_flLastOriginZ; //0x114
	float           m_flHeadHeightOrOffsetFromHittingGroundAnimation; //0x118 from 0 to 1, is 1 when standing
	float           m_flStopToFullRunningFraction; //0x11C from 0 to 1, doesnt change when walking or crouching, only running
	char            pad8[4];
	float            m_flUnknownFraction; //0x124 affected while jumping and running, or when just jumping, 0 to 1
	char            pad9[4];
	float           m_flUnknown3;
	char            pad10[528];
	template< class T >
	inline T& get_offset(const int off)
	{
		return *reinterpret_cast<T*>(DWORD(this) + off);
	}
};