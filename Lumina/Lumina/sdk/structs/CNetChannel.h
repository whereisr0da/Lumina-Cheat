#pragma once

typedef enum
{
	NA_NULL = 0,
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
} netadrtype_t;

struct netadr_t
{
	netadrtype_t	type;
	unsigned char	ip[ 4 ];
	unsigned short	port;
};

class bf_read
{
public:
	uintptr_t base_address;
	uintptr_t cur_offset;

	bf_read( uintptr_t addr )
	{
		base_address = addr;
		cur_offset = 0;
	}

	void SetOffset( uintptr_t offset )
	{
		cur_offset = offset;
	}

	void Skip( uintptr_t length )
	{
		cur_offset += length;
	}

	int ReadByte()
	{
		auto val = *reinterpret_cast<char*>( base_address + cur_offset );
		++cur_offset;
		return val;
	}

	long ReadLong()
	{
		auto val = *reinterpret_cast<long*>( base_address + cur_offset );
		++cur_offset;
		return val;
	}

	bool ReadBool()
	{
		auto val = *reinterpret_cast<bool*>( base_address + cur_offset );
		++cur_offset;
		return val;
	}

	std::string ReadString()
	{
		char buffer[ 256 ];
		auto str_length = *reinterpret_cast<char*>( base_address + cur_offset );
		++cur_offset;
		memcpy( buffer, reinterpret_cast<void*>( base_address + cur_offset ), str_length > 255 ? 255 : str_length );
		buffer[ str_length > 255 ? 255 : str_length ] = '\0';
		cur_offset += str_length + 1;
		return std::string( buffer );
	}
};

typedef struct netpacket_s netpacket_t;

typedef struct netpacket_s
{
	netadr_t		from;		// sender IP
	int				source;		// received source 
	double			received;	// received time
	unsigned char	*data;		// pointer to raw packet data
	bf_read			message;	// easy bitbuf data access
	int				size;		// size in bytes
	int				wiresize;   // size in bytes before decompression
	bool			stream;		// was send as stream
	struct netpacket_s *pNext;	// for internal use, should be NULL in public
} netpacket_t;

class CNetChannel
{
public:
	char pad_0x0000[ 0x18 ]; //0x0000
	__int32 m_nOutSequenceNr; //0x0018 
	__int32 m_nInSequenceNr; //0x001C 
	__int32 m_nOutSequenceNrAck; //0x0020 
	__int32 m_nOutReliableState; //0x0024 
	__int32 m_nInReliableState; //0x0028 
	__int32 m_nChokedPackets; //0x002C 

	VFUNC( 42, SendNetMsg( void* msg, bool bForceReliable = false, bool bVoice = false ), bool( __thiscall* )( void*, void*, bool, bool ) )( msg, bForceReliable, bVoice )
	VFUNC( 49, Transmit( bool onlyreliable = false ), bool( __thiscall* )( void*, bool ) )( onlyreliable )
};//Size=0x4294