#pragma once

class IAppSystem2
{
public:
	virtual void func0() = 0;
	virtual void func1() = 0;
	virtual void func2() = 0;
	virtual void func3() = 0;
	virtual void func4() = 0;
	virtual void func5() = 0;
	virtual void func6() = 0;
	virtual void func7() = 0;
	virtual void func8() = 0;
	virtual void func9() = 0;
};

struct CVarDLLIdentifier_t;

class ICVar : public IAppSystem2
{
public:
	virtual void			func10() = 0;
	virtual void			RegisterConCommand( ConVar *pCommandBase ) = 0;
	virtual void			UnregisterConCommand( ConVar *pCommandBase ) = 0;
	virtual void			func13() = 0;
	virtual ConVar			*FindVar( const char *var_name ) = 0;

	/*
	template <typename... Values>
	void ConsoleColorPrintf( const Color& MsgColor, const char* szMsgFormat, Values... Parameters )
	{
		typedef void( *oConsoleColorPrintf )( void*, const Color&, const char*, ... );
		return util::get_vfunc<oConsoleColorPrintf>( this, 25 )( this, MsgColor, szMsgFormat, Parameters... );
	}*/
};

extern ICVar* g_pCVar;