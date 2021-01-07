#ifndef vfunc_h

#define vfunc_h

namespace vfunc {

	template <typename T> T get_vfunc(void *v_table, const int i_index) { return (*static_cast<T**>(v_table))[i_index]; }
}

#define MEMEBR_FUNC_ARGS(...) ( this, __VA_ARGS__ ); }
#define FUNCARGS(...) ( __VA_ARGS__ ); }
#define VFUNC( index, func, sig ) auto func { return vfunc::get_vfunc< sig >( this, index ) MEMEBR_FUNC_ARGS
#define MFUNC(func, sig, offset) auto func { return reinterpret_cast< sig >( offset ) MEMEBR_FUNC_ARGS
#define FUNC(func, sig, offset) auto func { return reinterpret_cast< sig >( offset ) FUNCARGS

#endif