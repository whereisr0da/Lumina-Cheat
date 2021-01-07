#pragma once

class CMoveData
{
public:
	bool    m_bFirstRunOfFunctions : 1;
	bool    m_bGameCodeMovedPlayer : 1;
	int     m_nPlayerHandle;        // edict index on server, client entity handle on client=
	int     m_nImpulseCommand;      // Impulse command issued.
	Vector  m_vecViewAngles;        // Command view angles (local space)
	Vector  m_vecAbsViewAngles;     // Command view angles (world space)
	int     m_nButtons;             // Attack buttons.
	int     m_nOldButtons;          // From host_client->oldbuttons;
	float   m_flForwardMove;
	float   m_flSideMove;
	float   m_flUpMove;
	float   m_flMaxSpeed;
	float   m_flClientMaxSpeed;
	Vector  m_vecVelocity;          // edict::velocity        // Current movement direction.
	Vector  m_vecAngles;            // edict::angles
	Vector  m_vecOldAngles;
	float   m_outStepHeight;        // how much you climbed this move
	Vector  m_outWishVel;           // This is where you tried 
	Vector  m_outJumpVel;           // This is your jump velocity
	Vector  m_vecConstraintCenter;
	float   m_flConstraintRadius;
	float   m_flConstraintWidth;
	float   m_flConstraintSpeedFactor;
	float   m_flUnknown[ 5 ];
	Vector  m_vecAbsOrigin;
};

class IGameMovement
{
public:
	virtual			~IGameMovement( void ) {}

	virtual void	          ProcessMovement( C_BasePlayer *pPlayer, CMoveData *pMove ) = 0;
	virtual void	          Reset( void ) = 0;
	virtual void	          StartTrackPredictionErrors( C_BasePlayer *pPlayer ) = 0;
	virtual void	          FinishTrackPredictionErrors( C_BasePlayer *pPlayer ) = 0;
	virtual void	          DiffPrint( char const *fmt, ... ) = 0;
	virtual Vector const&	  GetPlayerMins( bool ducked ) const = 0;
	virtual Vector const&	  GetPlayerMaxs( bool ducked ) const = 0;
	virtual Vector const&   GetPlayerViewOffset( bool ducked ) const = 0;
	virtual bool		        IsMovingPlayerStuck( void ) const = 0;
	virtual C_BasePlayer*   GetMovingPlayer( void ) const = 0;
	virtual void		        UnblockPusher( C_BasePlayer *pPlayer, C_BasePlayer *pPusher ) = 0;
	virtual void            SetupMovementBounds( CMoveData *pMove ) = 0;
};

extern IGameMovement* g_pGameMovement;

class CGameMovement
	: public IGameMovement
{
public:
	virtual ~CGameMovement( void ) {}
};

class IPrediction
{
public:
	VFUNC( 12, GetLocalViewAngles( QAngle& ang ), void( __thiscall* )( void*, QAngle& ) )( ang )
	VFUNC( 371, SetLocalViewAngles( QAngle& ang ), void( __thiscall* )( void*, QAngle& ) )( ang )
		VFUNC( 14, InPrediction(), bool( __thiscall* )( void* ) )( )
		VFUNC( 19, RunCommand( C_BasePlayer *player, CUserCmd *cmd, IMoveHelper *movehelper ), void( __thiscall* )( void*, C_BasePlayer*, CUserCmd *, IMoveHelper * ) )( player, cmd, movehelper )
		VFUNC( 20, SetupMove( C_BasePlayer *player, CUserCmd *cmd, IMoveHelper *movehelper, void* movedata ), void( __thiscall* )( void*, C_BasePlayer *, CUserCmd *, IMoveHelper *, void* ) )( player, cmd, movehelper, movedata )
		VFUNC( 21, FinishMove( C_BasePlayer *player, CUserCmd *cmd, void* movedata ), void( __thiscall* )( void*, C_BasePlayer *, CUserCmd *, void* ) )( player, cmd, movedata )

public:
	float GetIdealPitch( int nSlot ) const
	{
		if ( nSlot == -1 ) { Assert( 0 ); return 0.0f; }
		return m_Split[ nSlot ].m_flIdealPitch;
	}

	CBaseHandle		m_hLastGround;

	bool			m_bInPrediction;
	bool			m_bOldCLPredictValue;
	bool			m_bEnginePaused;

	int				m_nPreviousStartFrame;
	int				m_nIncomingPacketNumber;

	float			m_flLastServerWorldTimeStamp;

	// Last network origin for local player
	struct Split_t
	{
		Split_t()
		{
			m_bFirstTimePredicted = false;
			m_nCommandsPredicted = 0;
			m_nServerCommandsAcknowledged = 0;
			m_bPreviousAckHadErrors = false;
			m_flIdealPitch = 0.0f;

		}

		bool			m_bFirstTimePredicted;
		int				m_nCommandsPredicted;
		int				m_nServerCommandsAcknowledged;
		int				m_bPreviousAckHadErrors;
		float			m_flIdealPitch;
	};

	Split_t				m_Split[ 2 ];
};

extern IPrediction* g_pPrediction;