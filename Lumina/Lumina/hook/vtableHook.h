#ifndef vtableHook_h

#define vtableHook_h

#define NOMINMAX

#include "../common/includes.h"

namespace detail {
	class protect_guard {
	public:
		protect_guard(void* base, size_t len, std::uint32_t flags) {
			_base = base;
			_length = len;
			//VirtualProtect(base, len, flags, (PDWORD)&_old);
			LI_FN(VirtualProtect).get()(base, len, flags, (PDWORD)&_old);
		}
		~protect_guard() {
			//VirtualProtect(_base, _length, _old, (PDWORD)&_old);
			LI_FN(VirtualProtect).get()(_base, _length, _old, (PDWORD)&_old);
		}

	private:
		void*         _base;
		size_t        _length;
		std::uint32_t _old;
	};
}

class vmt {
public:
	static inline std::size_t estimate_vftbl_length(std::uintptr_t* vftbl_start);

	void*           class_base;
	std::size_t     vftbl_len;
	std::uintptr_t* new_vftb1;
	std::uintptr_t* old_vftbl;
	LPCVOID         search_base = nullptr;
	bool was_allocated = false;

	uintptr_t * search_free_data_page(const char * module_name, const std::size_t vmt_size);
	vmt();
	vmt(void* base);
	~vmt();

	bool setup(void * base, const char * module_name);

	void hook_index(size_t fn_index, void* fn_pointer);
	void release();

	void* get_original(size_t fn_index);
};

#endif // !vtableHook_h