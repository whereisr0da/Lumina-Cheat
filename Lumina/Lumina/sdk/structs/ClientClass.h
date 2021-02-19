#ifndef ClientClass_h

#define ClientClass_h

class IClientNetworkable;
class ClientClass;


class d_variant_ {
public:
	union {
		float m_float;
		long m_int;
		char* m_string;
		void* m_data;
		float m_vector[3];
		__int64 m_int64;
	};
	int type;
};



class recv_prop_ {
public:
	char* prop_name;
	int prop_type;
	int prop_flags;
	int buffer_size;
	int is_inside_of_array;
	const void* extra_data_ptr;
	recv_prop_* array_prop;
	void* array_length_proxy;
	void* proxy_fn;
	void* data_table_proxy_fn;
	void* data_table;
	int offset;
	int element_stride;
	int elements_count;
	const char* parent_array_prop_name;
};

class recv_table_ {

public:
	recv_prop_ * props;
	int props_count;
	void* decoder_ptr;
	char* table_name;
	bool is_initialized;
	bool is_in_main_list;
};

class c_recv_proxy_data_ {
public:
	const recv_prop_* recv_prop;
	d_variant_ value;
	int element_index;
	int object_id;
};

using recv_var_proxy_fn_ = void(*)(const c_recv_proxy_data_* data, void* struct_ptr, void* out_ptr);


using CreateClientClassFn = IClientNetworkable * ( *)( int, int );
using CreateEventFn = IClientNetworkable * ( *)( );

class ClientClass
{
public:
	CreateClientClassFn m_pCreateFn;
	CreateEventFn m_pCreateEventFn;
	const char* m_pNetworkName;
	recv_table_* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

#endif // !ClientClass_h