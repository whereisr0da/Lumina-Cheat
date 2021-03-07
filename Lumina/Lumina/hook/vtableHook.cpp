#include "../common/includes.h"
#include "../common/common.h"

// thx to oneshot for the trick
// Modified code from exphck https://www.unknowncheats.me/forum/2128832-post43.html

uintptr_t* vmt::search_free_data_page(const char* module_name, const std::size_t vmt_size) 
{
	HMODULE module_addr = NULL;

	VMProtectBeginMutation("vmt::search_free_data_page");

	auto check_data_section = [&](LPCVOID address, const std::size_t vmt_size) {

		const DWORD DataProtection = (PAGE_EXECUTE_READWRITE | PAGE_READWRITE);
		MEMORY_BASIC_INFORMATION mbi = { 0 };

		//if (LI_FN(VirtualQuery).get()(address, &mbi, sizeof(mbi)) == sizeof(mbi) && mbi.AllocationBase && mbi.BaseAddress &&
		if (VirtualQuery(address, &mbi, sizeof(mbi)) == sizeof(mbi) && mbi.AllocationBase && mbi.BaseAddress &&
			mbi.State == MEM_COMMIT && !(mbi.Protect & PAGE_GUARD) && mbi.Protect != PAGE_NOACCESS) {
			if ((mbi.Protect & (DataProtection)) && mbi.RegionSize >= vmt_size) {
				return ((mbi.Protect & (DataProtection)) && mbi.RegionSize >= vmt_size) ? true : false;
			}
		}

		return false;
	};

	// this is very ghetto trick, but it's the only with to keep it at compile time
	// TODO : use hash
	if (!strcmp(module_name, StringHeavy("materialsystem.dll")))
	{
		module_addr = (HMODULE)LI_MODULE("materialsystem.dll").cached();
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : materialsystem.dll cached"));
#endif
	}
	else if (!strcmp(module_name, StringHeavy("client.dll")))
	{
		module_addr = (HMODULE)LI_MODULE("client.dll").cached();
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : client.dll cached"));
#endif
	}
	else if (!strcmp(module_name, StringHeavy("vgui2.dll")))
	{
		module_addr = (HMODULE)LI_MODULE("vgui2.dll").cached();
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : vgui2.dll cached"));
#endif
	}
	else if (!strcmp(module_name, StringHeavy("engine.dll")))
	{
		module_addr = (HMODULE)LI_MODULE("engine.dll").cached();
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : engine.dll cached"));
#endif
	}
	else if (!strcmp(module_name, StringHeavy("shaderapidx9.dll")))
	{
		module_addr = (HMODULE)LI_MODULE("shaderapidx9.dll").cached();
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : shaderapidx9.dll cached"));
#endif
	}
	else if (!strcmp(module_name, StringHeavy("vguimatsurface.dll")))
	{
		module_addr = (HMODULE)LI_MODULE("vguimatsurface.dll").cached();
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : vguimatsurface.dll cached"));
#endif
	}
	else if (!strcmp(module_name, StringHeavy("direct3d.dll")))
	{
		module_addr = (HMODULE)LI_MODULE("direct3d.dll").cached();
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : direct3d.dll cached"));
#endif
	}
	else if (!strcmp(module_name, StringHeavy("datacache.dll")))
	{
		module_addr = (HMODULE)LI_MODULE("datacache.dll").cached();
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : datacache.dll cached"));
#endif
	}

	else
	{
		module_addr = LI_FN(GetModuleHandleA).get()(module_name);
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::search_free_data_page() : module not cached"));
#endif
	}



	if (module_addr == nullptr) {
#ifdef _DEBUG
		common::ps(StringHeavy("vmt::setup() : module_addr == nullptr"));
		common::ps(StringHeavy("vmt::setup() : trying a last thing"));
#endif
		module_addr = GetModuleHandleA(module_name);

		if (module_addr == nullptr) {

#ifdef _DEBUG
			common::ps(StringHeavy("vmt::setup() : fail module_addr == nullptr"));
#endif

			return nullptr;
		}
	}

	/*
module_addr = GetModuleHandleA(module_name);

if (module_addr == nullptr) {

	common::ps(StringHeavy("vmt::setup() : fail module_addr == nullptr"));

	return nullptr;
}*/

	const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER> (module_addr);

	const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS> (reinterpret_cast<std::uint8_t*>(module_addr) + dos_header->e_lfanew);

	const auto module_end = reinterpret_cast<std::uintptr_t>(module_addr) + nt_headers->OptionalHeader.SizeOfImage - sizeof(std::uintptr_t);

	for (auto current_address = module_end; current_address > (DWORD)module_addr; current_address -= sizeof(std::uintptr_t)) {

		if (*reinterpret_cast<std::uintptr_t*>(current_address) == 0 && check_data_section(reinterpret_cast<LPCVOID>(current_address), vmt_size)) {

			//OBF_BEGIN

			bool is_good_vmt = true;
			auto page_count = (0u);

			int i = 0;
			/*
				FOR(V(i) = N(0), page_count < vmt_size && V(is_good_vmt), page_count += sizeof(std::uintptr_t))

					IF(*reinterpret_cast<std::uintptr_t*>(current_address + page_count) != 0)
						V(is_good_vmt) = false;
					ENDIF

				ENDFOR

						if (is_good_vmt && page_count >= vmt_size)
							RETURN((uintptr_t*)current_address);

			OBF_END

					*/

			for (; page_count < vmt_size && is_good_vmt; page_count += sizeof(std::uintptr_t)) {

				if (*reinterpret_cast<std::uintptr_t*>(current_address + page_count) != 0)
					is_good_vmt = false;
			}

			if (is_good_vmt && page_count >= vmt_size)
				return ((uintptr_t*)current_address);
		}
	}

	//common::ps(StringHeavy("vmt::search_free_data_page() : end"));

	VMProtectEnd();

	return nullptr;
}

vmt::vmt()
	: class_base(nullptr), vftbl_len(0), new_vftb1(nullptr), old_vftbl(nullptr) {
}
vmt::vmt(void* base)
	: class_base(base), vftbl_len(0), new_vftb1(nullptr), old_vftbl(nullptr) {
}
vmt::~vmt() {

	VMProtectBeginMutation("vmt::~vmt");

	release();
	if (was_allocated)
		delete[] new_vftb1;

	VMProtectEnd();
}

bool vmt::setup(void* base, const char * module_name) {

	VMProtectBeginMutation("vmt::setup");

	// using a little bit of meta prog for obfu reasons

	OBF_BEGIN

	IF(base == 0)
		RETURN(false)
		ENDIF

		IF(base != nullptr)
		class_base = base;
	ENDIF

		IF(class_base == nullptr)
		RETURN(false)
		ENDIF

		size_t pointerSize = sizeof(std::uintptr_t);


	old_vftbl = *(std::uintptr_t**)class_base;



	vftbl_len = estimate_vftbl_length(old_vftbl) * (pointerSize);

	IF(vftbl_len == N((size_t)0))

	RETURN(false)
		ENDIF


	new_vftb1 = search_free_data_page(module_name, vftbl_len + (pointerSize));


	if (new_vftb1 == nullptr) {

		RETURN(false)
	}


	/*
	memset(new_vftb1, NULL, vftbl_len + sizeof(std::uintptr_t));
	*/

	unsigned char *ptr = (unsigned char *)new_vftb1;

	int len = vftbl_len + V(pointerSize);

	WHILE(len-- > 0)
		V(*ptr)++ = N(0);
	ENDWHILE


		/*
		memcpy(&new_vftb1[N(1)], old_vftbl, vftbl_len);
		*/

	char *d = (char *)&new_vftb1[N(1)];
	const char *s = (const char *)old_vftbl;

	len = vftbl_len;

	WHILE(len--)
		*d++ = *s++;
	ENDWHILE


		/*
	memset(new_vftb1, NULL, vftbl_len + sizeof(std::uintptr_t));



	memcpy(&new_vftb1[1], old_vftbl, vftbl_len);

	*/
		new_vftb1[N(0)] = old_vftbl[-1];


	try {
		auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };

		*(std::uintptr_t**)class_base = &new_vftb1[(1)];


		was_allocated = false;
	}
	catch (...) {
		delete[] new_vftb1;
		return false;
	}

	OBF_END

	VMProtectEnd();

	return true;
}

std::size_t vmt::estimate_vftbl_length(std::uintptr_t* vftbl_start) {

	VMProtectBeginMutation("vmt::estimate_vftbl_length");

	MEMORY_BASIC_INFORMATION memInfo = { NULL };
	int m_nSize = -1;
	do {
		m_nSize++;
		LI_FN(VirtualQuery).get()(reinterpret_cast<LPCVOID>(vftbl_start[m_nSize]), &memInfo, sizeof(memInfo));
		//VirtualQuery(reinterpret_cast<LPCVOID>(vftbl_start[m_nSize]), &memInfo, sizeof(memInfo));
	} while (memInfo.Protect == PAGE_EXECUTE_READ || memInfo.Protect == PAGE_EXECUTE_READWRITE);

	VMProtectEnd();

	return m_nSize;
}

void vmt::hook_index(size_t fn_index, void* fn_pointer) {

	VMProtectBeginMutation("vmt::hook_index");

	if (fn_index >= 0 && fn_index <= (int)vftbl_len)
		new_vftb1[fn_index + 1] = reinterpret_cast<std::uintptr_t>(fn_pointer);

	VMProtectEnd();
}

void vmt::release() {

	VMProtectBeginMutation("vmt::release");

	try {
		if (old_vftbl != nullptr) {
			auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
			*(std::uintptr_t**)class_base = old_vftbl;
			old_vftbl = nullptr;
		}
	}
	catch (...) {
	}

	VMProtectEnd();
}

void* vmt::get_original(size_t fn_index) {

	VMProtectBeginMutation("vmt::get_original");

	void* result = reinterpret_cast<void*>(old_vftbl[fn_index]);

	VMProtectEnd();

	return result;
}
