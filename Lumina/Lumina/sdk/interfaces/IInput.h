#pragma once

typedef unsigned int CRC32_t;
class IInput
{
public:
	class CVerifiedUserCmd
	{
	public:
		CUserCmd	m_cmd;
		CRC32_t		m_crc;
	};
public:
	void*               pvftable;                     //0x00
	bool                m_fTrackIRAvailable;          //0x04
	bool                m_fMouseInitialized;          //0x05
	bool                m_fMouseActive;               //0x06
	bool                m_fJoystickAdvancedInit;      //0x07
	char                pad_0x08[ 0x2C ];             //0x08
	void*               m_pKeys;                      //0x34
	char                pad_0x38[ 0x64 ];             //0x38
	int					pad_0x41;
	int					pad_0x42;
	int					pad_0x43;
	int					pad_0x44;
	bool                m_fCameraInterceptingMouse;   //0x9C
	bool                m_fCameraInThirdPerson;       //0x9D
	bool                m_fCameraMovingWithMouse;     //0x9E
	Vector				m_vecCameraOffset;            //0xA0
	bool                m_fCameraDistanceMove;        //0xAC
	int                 m_nCameraOldX;                //0xB0
	int                 m_nCameraOldY;                //0xB4
	int                 m_nCameraX;                   //0xB8
	int                 m_nCameraY;                   //0xBC
	bool                m_CameraIsOrthographic;       //0xC0
	Vector              m_angPreviousViewAngles;      //0xC4
	Vector              m_angPreviousViewAnglesTilt;  //0xD0
	float               m_flLastForwardMove;          //0xDC
	int                 m_nClearInputState;           //0xE0
	//char                pad_0xE4[ 0x8 ];              //0xE4
	CUserCmd*           m_pCommands;                  //0xEC
	CVerifiedUserCmd*   m_pVerifiedCommands;		  //0xF0
	VFUNC( 8, GetUserCmd( int slot, int seq ), CUserCmd*( __thiscall* )( void*, int, int ) )( slot, seq )
};

extern IInput* g_pInput;
