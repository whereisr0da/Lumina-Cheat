#pragma once


class IGameEvent
{
public:
	virtual ~IGameEvent() {};
	virtual const char *GetName() const = 0;	// get event name

	virtual bool  IsReliable() const = 0; // if event handled reliable
	virtual bool  IsLocal() const = 0; // if event is never networked
	virtual bool  IsEmpty(const char *keyName ) = 0; // check if data field exists

	// Data access
	virtual bool  GetBool(const char *keyName , bool defaultValue = false) = 0;
	virtual int   GetInt(const char *keyName , int defaultValue = 0) = 0;
	virtual unsigned __int64 GetUint64(const char *keyName , unsigned __int64 defaultValue = 0) = 0;
	virtual float GetFloat(const char *keyName , float defaultValue = 0.0f) = 0;
	virtual const char *GetString(const char *keyName , const char *defaultValue = "") = 0;
	virtual const wchar_t * GetWString(char const *keyName , const wchar_t *defaultValue = L"") = 0;

	virtual void SetBool(const char *keyName, bool value) = 0;
	virtual void SetInt(const char *keyName, int value) = 0;
	virtual void SetUint64(const char *keyName, unsigned __int64 value) = 0;
	virtual void SetFloat(const char *keyName, float value) = 0;
	virtual void SetString(const char *keyName, const char *value) = 0;
	virtual void SetWString(const char *keyName, const wchar_t *value) = 0;
};


class IGameEventListener2
{
public:
	virtual    ~IGameEventListener2( void ) {};

	virtual void FireGameEvent( IGameEvent *event ) = 0;
	virtual int  GetEventDebugID( void ) = 0;
};

#undef CreateEvent
class IGameEventManager2
{
public:
	virtual ~IGameEventManager2( void ) {};
	virtual int LoadEventsFromFile( const char* filename ) = 0;
	virtual void Reset() = 0;
	virtual bool AddListener( IGameEventListener2* listener, const char* name, bool bServerSide ) = 0;
	virtual bool FindListener( IGameEventListener2* listener, const char* name ) = 0;
	virtual void RemoveListener( IGameEventListener2* listener ) = 0;
	virtual void AddListenerGlobal( IGameEventListener2* listener, bool bIsServerSide ) = 0;
	virtual IGameEvent* CreateEvent( const char* name, bool bForce = false, int* pCookie = 0 ) = 0;
	virtual bool FireEvent( IGameEvent* event, bool bDontBroadcast = false ) = 0;
	virtual bool FireEventClientSide( IGameEvent* event ) = 0;
	virtual IGameEvent* DuplicateEvent( IGameEvent* event ) = 0;
	virtual void FreeEvent( IGameEvent* event ) = 0;
	virtual bool SerializeEvent( IGameEvent* event, int* buf ) = 0;
	virtual IGameEvent* UnserializeEvent( int* buf ) = 0;
	virtual void *GetEventDataTypes( IGameEvent* event ) = 0;
};