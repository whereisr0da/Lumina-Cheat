#ifndef console_h

#define console_h

class i_app_system {
public:
	virtual bool connect(void* factory) = 0;
	virtual void disconnect() = 0;
	virtual void* query_interface(const char *pInterfaceName) = 0;
	virtual int init() = 0;
	virtual void shutdown() = 0;
	virtual const void* get_dependencies() = 0;
	virtual int  get_tier() = 0;
	virtual void reconnect(void* factory, const char *pInterfaceName) = 0;
	virtual void unknown() = 0;
};

class con_command;
class con_command_base;

typedef int cvar_dll_indentifier_t;

class IConsole : public i_app_system {
public:
	virtual cvar_dll_indentifier_t allocate_dll_indentifier() = 0;
	virtual void register_con_command(con_command_base *pCommandBase) = 0;
	virtual void unregister_con_command(con_command_base *pCommandBase) = 0;
	virtual void unregister_con_commands(cvar_dll_indentifier_t id) = 0;
	virtual const char* get_command_line_value(const char *pVariableName) = 0;
	virtual con_command_base* find_command_base(const char *name) = 0;
	virtual const con_command_base* find_command_base(const char *name) const = 0;
	virtual void* get_convar(const char *var_name) = 0;
	virtual const void* get_convar(const char *var_name) const = 0;
};

#endif // !console