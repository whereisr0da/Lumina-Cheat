#pragma once

inline uint8_t* find_sig_ext(uint32_t offset, const char* signature, uint32_t range = 0u)
{
	static auto pattern_to_bytes = [](const char* pattern) -> std::vector<int>
	{
		auto bytes = std::vector<int32_t>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				current++;

				if (*current == '?')
					current++;

				bytes.push_back(-1);
			}
			else
				bytes.push_back(static_cast<int32_t>(strtoul(current, &current, 0x10)));
		}

		return bytes;
	};

	const auto scan_bytes = reinterpret_cast<std::uint8_t*>(offset);
	auto pattern_bytes = pattern_to_bytes(signature);
	const auto s = pattern_bytes.size();
	const auto d = pattern_bytes.data();

	for (auto i = 0ul; i < range - s; ++i)
	{
		auto found = true;

		for (auto j = 0ul; j < s; ++j)
			if (scan_bytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}

		if (found)
			return &scan_bytes[i];
	}

	return nullptr;
}

__forceinline void erase_function(uint8_t* function)
{
	if (*function == 0xE9)
	{
		auto pdFollow = (PDWORD)(function + 1);
		function = ((PBYTE)(*pdFollow + (DWORD)function + 5));
	}
	else if (*function == 0xEB)
	{
		auto pbFollow = (PDWORD)(function + 1);
		function = ((PBYTE)((DWORD)*pbFollow + (DWORD)function + 2));
	}

	static const auto current_process = reinterpret_cast<HANDLE>(-1);

	const auto end = find_sig_ext(reinterpret_cast<uint32_t>(function), XorStr("90 90 90 90 90"), 0x2000);
	
	size_t bytes = reinterpret_cast<DWORD>(end) - reinterpret_cast<DWORD>(function) + 6;

	void* fn = function;
	size_t size = bytes;
	DWORD old;

	LI_FN(VirtualProtect).get()(fn, size, PAGE_EXECUTE_READWRITE, &old);

	fn = function;
	size = bytes;
	memset(fn, 0, size);

	LI_FN(VirtualProtect).get()(fn, size, old, &old);
}

// NOLINTNEXTLINE
#define erase_fn(a) constexpr auto concat(w, __LINE__) = &a;\
    erase_function(reinterpret_cast<uint8_t*>((void*&)concat(w, __LINE__)))

#define erase_end  __asm _emit 0x90 __asm _emit 0x90 __asm _emit 0x90 __asm _emit 0x90 __asm _emit 0x90 

#define BLOCK_0 __asm __emit 0xB0 __asm __emit 0x0B __asm __emit 0xF0 __asm __emit 0xB0 __asm __emit 0x0B __asm __emit 0xF0 __asm __emit 0xB0 __asm __emit 0xBE __asm __emit 0xEF __asm __emit 0xDE __asm __emit 0xAD __asm __emit 0x01 __asm __emit 0xDE __asm __emit 0xAD
#define JUNK_0(a) __asm jmp a BLOCK_0 \