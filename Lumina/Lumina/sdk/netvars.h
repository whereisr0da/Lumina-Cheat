#ifndef netvart_h

#define netvart_h

#include <cstdint>
#include <map>
#include "../security/xorstr.hpp"
#include "../sdk/math/Vector.h"

/*

using fnv_t = unsigned;
class FnvHash
{
	static const fnv_t FNV_PRIME = 16777619u;
	static const fnv_t OFFSET_BASIS = 2166136261u;

	template <unsigned int N>
	static constexpr fnv_t fnvHashConst(const char(&str)[N], unsigned int I = N)
	{
		return static_cast<fnv_t>(1ULL * (I == 1 ? (OFFSET_BASIS ^ str[0]) : (fnvHashConst(str, I - 1) ^ str[I - 1])) * FNV_PRIME);
	}

	static fnv_t fnvHash(const char* str)
	{
		const auto length = strlen(str) + 1;
		auto hash = OFFSET_BASIS;
		for (size_t i = 0; i < length; ++i)
		{
			hash ^= *str++;
			hash *= FNV_PRIME;
		}
		return hash;
	}

	struct Wrapper
	{
		Wrapper(const char* str) : str(str) {}
		const char* str;
	};

	fnv_t hash_value;
public:
	FnvHash(Wrapper wrapper) : hash_value(fnvHash(wrapper.str)) {}

	template <unsigned int N>
	constexpr FnvHash(const char(&str)[N]) : hash_value(fnvHashConst(str)) {}

	constexpr operator fnv_t() const { return this->hash_value; }
};

struct CRecvProxyData;

class RecvProp;
class RecvTable;

using RecvVarProxyFn = void(__cdecl *)(CRecvProxyData*, void*, void*);

struct DVariant
{
	union
	{
		float m_Float;
		long m_Int;
		char* m_pString;
		void* m_pData;
		Vector m_Vector;
		int64_t m_Int64;
	};

	int m_Type;
};

struct CRecvProxyData
{
	const RecvProp* m_pRecvProp;
	DVariant m_Value;
	int m_iElement;
	int m_ObjectID;
};

enum SendPropType : int
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,
	DPT_DataTable,
	DPT_Int64,
	DPT_NUMSendPropTypes
};

class RecvProp
{
public:
	char* m_pVarName;
	SendPropType m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	RecvVarProxyFn m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};

class RecvTable
{
public:
	RecvProp * m_pProps;
	int m_nProps;
	void* m_pDecoder;
	char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

class CNetVars
{
private:
	struct StoredPropData
	{
		RecvProp* prop_ptr;
		uint16_t class_relative_offset;
	};

public:
	static CNetVars& Get()
	{
		static CNetVars instance;
		return instance;
	}

	unsigned short GetOffset(unsigned int hash) { return m_props[hash].class_relative_offset; }
	RecvProp* GetPropPtr(unsigned int hash) { return m_props[hash].prop_ptr; }

	// Prevent instruction cache pollution caused by automatic
	// inlining of Get and GetOffset every netvar usage when there
	// are a lot of netvars
	__declspec(noinline) static uint16_t GetOffsetByHash(fnv_t hash)
	{
		return Get().GetOffset(hash);
	}

private:
	CNetVars();
	void dump_recursive(const char* base_class, RecvTable* table, uint16_t offset);

private:
	std::map<fnv_t, StoredPropData> m_props;
};
//===============================================
#define PNETVAR(funcname, type, netvarname) type* funcname() \
{ \
    static fnv_t hash; \
	static uint16_t offset; \
    if( !offset ) { char* str = XorStr(netvarname); \
	hash = FnvHash( str ); \
	offset = CNetVars::GetOffsetByHash(hash); \
	Assert(offset); } \
	return reinterpret_cast<type*>(uintptr_t(this) + offset); \
}
//===============================================
#define ANETVAR(funcname, type, num, netvarname) std::array<type, num>& funcname() \
{ \
	static fnv_t hash; \
	static uint16_t offset; \
    if( !offset ) { char* str = XorStr(netvarname); \
	hash = FnvHash( str ) \
	offset = CNetVars::GetOffsetByHash(hash); \
	Assert(offset); } \
	return *reinterpret_cast<std::array<type, num>*>(uintptr_t(this) + offset); \
}
//===============================================
#define NETVAR(funcname, type, netvarname) type& funcname() \
{ \
	static fnv_t hash; \
	static uint16_t offset; \
    if( !offset ) { char* str = XorStr(netvarname); \
	hash = FnvHash( str ); \
	offset = CNetVars::GetOffsetByHash(hash); \
	Assert(offset); } \
	return *reinterpret_cast<type*>(uintptr_t(this) + offset); \
}
//===============================================
#define NETVARA(funcname, type, netvarname, add) type& funcname() \
{ \
	static fnv_t hash; \
	static uint16_t offset; \
    if( !offset ) {char* str = XorStr(netvarname); \
	hash = FnvHash( str ); \
	offset = CNetVars::GetOffsetByHash(hash); \
	Assert(offset); } \
	return *reinterpret_cast<type*>(uintptr_t(this) + offset + add); \
}
//===============================================
#define NETPROP(funcname, netvarname) static RecvProp* funcname() \
{ \
	static fnv_t hash; \
	static RecvProp* prop_ptr = nullptr; \
    if( !prop_ptr ) { char* str = XorStr(netvarname); \
	hash = FnvHash( str ); \
	prop_ptr = CNetVars::Get().GetPropPtr(hash); } \
	return prop_ptr; \
}
//===============================================
#define OFFSET(funcname, type, offset) type& funcname() \
{ \
	static uint16_t _offset = offset; \
	Assert(_offset); \
	return *reinterpret_cast<type*>(uintptr_t(this) + _offset); \
}
//===============================================
#define POFFSET(funcname, type, offset) type* funcname() \
{ \
	static uint16_t _offset = offset; \
	Assert(_offset); \
	return reinterpret_cast<type*>(uintptr_t(this) + _offset); \
}
//===============================================
#define AOFFSET(funcname, type, num, offset) std::array<type, num>& funcname() \
{ \
	static uint16_t _offset = offset; \
	Assert(_offset); \
	return *reinterpret_cast<std::array<type, num>*>(uintptr_t(this) + _offset); \
}
//===============================================
#define APOFFSET(funcname, type, num, offset) std::array<type, num>& funcname() \
{ \
	static uint16_t _offset = offset; \
	Assert(_offset); \
	return **reinterpret_cast<std::array<type, num>**>(uintptr_t(this) + _offset); \
}
//===============================================
#define OFFSETRS(funcname, type, offset) type& funcname( int index ) \
{ \
	static uint16_t _offset = offset; \
	Assert(_offset); \
	return *reinterpret_cast<type*>(uintptr_t(this) + _offset + index * 4); \
}*/


namespace netvar_manager {

#pragma warning( push )
#pragma warning( disable: 4307 )

	namespace fnv_1a {
		template< typename S >
		struct fnv_internal;
		template< typename S >
		struct fnv1a;

		template< >
		struct fnv_internal< uint32_t > {
			constexpr static uint32_t default_offset_basis = 0x811C9DC5;
			constexpr static uint32_t prime = 0x01000193;
		};

		template< >
		struct fnv1a< uint32_t > : public fnv_internal< uint32_t > {
			constexpr static uint32_t hash(char const* const aString, const uint32_t val = default_offset_basis) {
				return (aString[0] == '\0')
					? val
					: hash(&aString[1], (val ^ uint32_t(aString[0])) * prime);
			}

			constexpr static uint32_t hash(wchar_t const* const aString, const uint32_t val = default_offset_basis) {
				return (aString[0] == L'\0')
					? val
					: hash(&aString[1], (val ^ uint32_t(aString[0])) * prime);
			}
		};
	}

	using fnv = fnv_1a::fnv1a< uint32_t >;

#pragma warning( pop )
}

#define NETVAR(table, prop, func_name, type) \
	type& func_name( ) { \
      static uintptr_t offset = 0; \
      if(!offset) \
      { offset = netvar_manager::get_net_var(netvar_manager::fnv::hash( table ), netvar_manager::fnv::hash( prop ) ); } \
	  \
      return *reinterpret_cast< type* >( uintptr_t( this ) + offset ); \
    }

#define NETVAR_PTR(table, prop, func_name, type) \
	type* func_name( ) { \
      static uintptr_t offset = 0; \
      if(!offset) \
      { offset = netvar_manager::get_net_var(netvar_manager::fnv::hash( table ), netvar_manager::fnv::hash( prop ) ); } \
	  \
      return reinterpret_cast< type* >( uintptr_t( this ) + offset ); \
    }

#define POFFSET(type, var, offset) \
	type* var() { \
		return (type*)(uintptr_t(this) + offset); \
	} \

#define GOFFSET(type, var, offset) \
	type var() { \
		return *(type*)(uintptr_t(this) + offset); \
	} \

#define OFFSET(type, var, offset) \
	type& var() { \
		return *(type*)(uintptr_t(this) + offset); \
	} \

#define OFFSETRS(funcname, type, offset) type& funcname( int index ) \
{ \
	static uint16_t _offset = offset; \
	Assert(_offset); \
	return *reinterpret_cast<type*>(uintptr_t(this) + _offset + index * 4); \
}

namespace netvar_manager {
	uintptr_t get_net_var(uint32_t table, uint32_t prop);
}

#endif 