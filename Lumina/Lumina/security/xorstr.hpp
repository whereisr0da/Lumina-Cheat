
/*
 * Copyright 2017 - 2020 Justas Masiulis
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef JM_XORSTR_HPP
#define JM_XORSTR_HPP

#include <immintrin.h>
#include <cstdint>
#include <cstddef>
#include <utility>
#include <type_traits>

#define xorstr(str) ::jm::xor_string([]() { return str; }, std::integral_constant<std::size_t, sizeof(str) / sizeof(*str)>{}, std::make_index_sequence<::jm::detail::_buffer_size<sizeof(str)>()>{})
#define xorstr_(str) xorstr(str).crypt_get()

#ifdef _MSC_VER
#define XORSTR_FORCEINLINE __forceinline
#else
#define XORSTR_FORCEINLINE __attribute__((always_inline)) inline
#endif

#if defined(__clang__) || defined(__GNUC__)
#define JM_XORSTR_LOAD_FROM_REG(x) ::jm::detail::load_from_reg(x)
#else
#define JM_XORSTR_LOAD_FROM_REG(x) (x)
#endif

namespace jm {

	namespace detail {

		template<std::size_t Size>
		XORSTR_FORCEINLINE constexpr std::size_t _buffer_size()
		{
			return ((Size / 16) + (Size % 16 != 0)) * 2;
		}

		template<std::uint32_t Seed>
		XORSTR_FORCEINLINE constexpr std::uint32_t key4() noexcept
		{
			std::uint32_t value = Seed;
			for (char c : __TIME__)
				value = static_cast<std::uint32_t>((value ^ c) * 16777619ull);
			return value;
		}

		template<std::size_t S>
		XORSTR_FORCEINLINE constexpr std::uint64_t key8()
		{
			constexpr auto first_part = key4<2166136261 + S>();
			constexpr auto second_part = key4<first_part>();
			return (static_cast<std::uint64_t>(first_part) << 32) | second_part;
		}

		// loads up to 8 characters of string into uint64 and xors it with the key
		template<std::size_t N, class CharT>
		XORSTR_FORCEINLINE constexpr std::uint64_t
			load_xored_str8(std::uint64_t key, std::size_t idx, const CharT* str) noexcept
		{
			using cast_type = typename std::make_unsigned<CharT>::type;
			constexpr auto value_size = sizeof(CharT);
			constexpr auto idx_offset = 8 / value_size;

			std::uint64_t value = key;
			for (std::size_t i = 0; i < idx_offset && i + idx * idx_offset < N; ++i)
				value ^=
				(std::uint64_t{ static_cast<cast_type>(str[i + idx * idx_offset]) }
			<< ((i % idx_offset) * 8 * value_size));

			return value;
		}

		// forces compiler to use registers instead of stuffing constants in rdata
		XORSTR_FORCEINLINE std::uint64_t load_from_reg(std::uint64_t value) noexcept
		{
#if defined(__clang__) || defined(__GNUC__)
			asm("" : "=r"(value) : "0"(value) : );
#endif
			return value;
		}

		template<std::uint64_t V>
		struct uint64_v {
			constexpr static std::uint64_t value = V;
		};

	} // namespace detail

	template<class CharT, std::size_t Size, class Keys, class Indices>
	class xor_string;

	template<class CharT, std::size_t Size, std::uint64_t... Keys, std::size_t... Indices>
	class xor_string<CharT, Size, std::integer_sequence<std::uint64_t, Keys...>, std::index_sequence<Indices...>> {
#ifndef JM_XORSTR_DISABLE_AVX_INTRINSICS
		constexpr static inline std::uint64_t alignment = ((Size > 16) ? 32 : 16);
#else
		constexpr static inline std::uint64_t alignment = 16;
#endif

		alignas(alignment) std::uint64_t _storage[sizeof...(Keys)];

	public:
		using value_type = CharT;
		using size_type = std::size_t;
		using pointer = CharT * ;
		using const_pointer = const CharT*;

		template<class L>
		XORSTR_FORCEINLINE xor_string(L l, std::integral_constant<std::size_t, Size>, std::index_sequence<Indices...>) noexcept
			: _storage{ JM_XORSTR_LOAD_FROM_REG(detail::uint64_v<detail::load_xored_str8<Size>(Keys, Indices, l())>::value)... }
		{}

		XORSTR_FORCEINLINE constexpr size_type size() const noexcept
		{
			return Size - 1;
		}

		XORSTR_FORCEINLINE void crypt() noexcept
		{
#if defined(__clang__)
			alignas(alignment)
				std::uint64_t arr[]{ JM_XORSTR_LOAD_FROM_REG(Keys)... };
			std::uint64_t*    keys =
				(std::uint64_t*)JM_XORSTR_LOAD_FROM_REG((std::uint64_t)arr);
#else
			alignas(alignment) std::uint64_t keys[]{ JM_XORSTR_LOAD_FROM_REG(Keys)... };
#endif

#ifndef JM_XORSTR_DISABLE_AVX_INTRINSICS
			((Indices >= sizeof(_storage) / 32 ? static_cast<void>(0) : _mm256_store_si256(
				reinterpret_cast<__m256i*>(_storage) + Indices,
				_mm256_xor_si256(
					_mm256_load_si256(reinterpret_cast<const __m256i*>(_storage) + Indices),
					_mm256_load_si256(reinterpret_cast<const __m256i*>(keys) + Indices)))), ...);

			if constexpr (sizeof(_storage) % 32 != 0)
				_mm_store_si128(
					reinterpret_cast<__m128i*>(_storage + sizeof...(Keys) - 2),
					_mm_xor_si128(_mm_load_si128(reinterpret_cast<const __m128i*>(_storage + sizeof...(Keys) - 2)),
						_mm_load_si128(reinterpret_cast<const __m128i*>(keys + sizeof...(Keys) - 2))));
#else
			((Indices >= sizeof(_storage) / 16 ? static_cast<void>(0) : _mm_store_si128(
				reinterpret_cast<__m128i*>(_storage) + Indices,
				_mm_xor_si128(_mm_load_si128(reinterpret_cast<const __m128i*>(_storage) + Indices),
					_mm_load_si128(reinterpret_cast<const __m128i*>(keys) + Indices)))), ...);
#endif
		}

		XORSTR_FORCEINLINE const_pointer get() const noexcept
		{
			return reinterpret_cast<const_pointer>(_storage);
		}

		XORSTR_FORCEINLINE pointer get() noexcept
		{
			return reinterpret_cast<pointer>(_storage);
		}

		XORSTR_FORCEINLINE pointer crypt_get() noexcept
		{
			// crypt() function inlined by hand, because MSVC linker chokes when you have a lot of strings
			// on 32 bit builds, so don't blame me for shit code :pepekms:
#if defined(__clang__)
			alignas(alignment)
				std::uint64_t arr[]{ JM_XORSTR_LOAD_FROM_REG(Keys)... };
			std::uint64_t*    keys =
				(std::uint64_t*)JM_XORSTR_LOAD_FROM_REG((std::uint64_t)arr);
#else
			alignas(alignment) std::uint64_t keys[]{ JM_XORSTR_LOAD_FROM_REG(Keys)... };
#endif

#ifndef JM_XORSTR_DISABLE_AVX_INTRINSICS
			((Indices >= sizeof(_storage) / 32 ? static_cast<void>(0) : _mm256_store_si256(
				reinterpret_cast<__m256i*>(_storage) + Indices,
				_mm256_xor_si256(
					_mm256_load_si256(reinterpret_cast<const __m256i*>(_storage) + Indices),
					_mm256_load_si256(reinterpret_cast<const __m256i*>(keys) + Indices)))), ...);

			if constexpr (sizeof(_storage) % 32 != 0)
				_mm_store_si128(
					reinterpret_cast<__m128i*>(_storage + sizeof...(Keys) - 2),
					_mm_xor_si128(_mm_load_si128(reinterpret_cast<const __m128i*>(_storage + sizeof...(Keys) - 2)),
						_mm_load_si128(reinterpret_cast<const __m128i*>(keys + sizeof...(Keys) - 2))));
#else
			((Indices >= sizeof(_storage) / 16 ? static_cast<void>(0) : _mm_store_si128(
				reinterpret_cast<__m128i*>(_storage) + Indices,
				_mm_xor_si128(_mm_load_si128(reinterpret_cast<const __m128i*>(_storage) + Indices),
					_mm_load_si128(reinterpret_cast<const __m128i*>(keys) + Indices)))), ...);
#endif
			return (pointer)(_storage);
		}
	};

	template<class L, std::size_t Size, std::size_t... Indices>
	xor_string(L l, std::integral_constant<std::size_t, Size>, std::index_sequence<Indices...>)->xor_string<
		std::remove_const_t<std::remove_reference_t<decltype(l()[0])>>,
		Size,
		std::integer_sequence<std::uint64_t, detail::key8<Indices>()...>,
		std::index_sequence<Indices...>>;

} // namespace jm

#define XorStr( s ) (xorstr(s).crypt_get())

#endif // include guard


/*

#pragma once

#include <string>
#include <array>
#include <cstdarg>

#define BEGIN_NAMESPACE( x ) namespace x {
#define END_NAMESPACE }

BEGIN_NAMESPACE(XorCompileTime)

constexpr auto time = __TIME__;
constexpr auto seed = static_cast<int>(time[7]) + static_cast<int>(time[6]) * 10 + static_cast<int>(time[4]) * 60 + static_cast<int>(time[3]) * 600 + static_cast<int>(time[1]) * 3600 + static_cast<int>(time[0]) * 36000;

template < int N >
struct RandomGenerator {
private:
	static constexpr unsigned a = 16807; // 7^5
	static constexpr unsigned m = 2147483647; // 2^31 - 1

	static constexpr unsigned s = RandomGenerator< N - 1 >::value;
	static constexpr unsigned lo = a * (s & 0xFFFF); // Multiply lower 16 bits by 16807
	static constexpr unsigned hi = a * (s >> 16); // Multiply higher 16 bits by 16807
	static constexpr unsigned lo2 = lo + ((hi & 0x7FFF) << 16); // Combine lower 15 bits of hi with lo's upper bits
	static constexpr unsigned hi2 = hi >> 15; // Discard lower 15 bits of hi
	static constexpr unsigned lo3 = lo2 + hi;

public:
	static constexpr unsigned max = m;
	static constexpr unsigned value = lo3 > m ? lo3 - m : lo3;
};

template <>
struct RandomGenerator< 0 > {
	static constexpr unsigned value = seed;
};

template < int N, int M >
struct RandomInt {
	static constexpr auto value = RandomGenerator< N + 1 >::value % M;
};

template < int N >
struct RandomChar {
	static const char value = static_cast<char>(1 + RandomInt< N, 0x7F - 1 >::value);
};

template < size_t N, int K >
struct XorString {
private:
	const char _key;
	std::array< char, N + 1 > _encrypted;

	constexpr char enc(char c) const {

		//VMProtectBeginMutation("XorString::enc");

		char result = c ^ _key;

		//VMProtectEnd();

		return result;
	}

	char dec(char c) const {

		//VMProtectBeginMutation("XorString::dec");

		char result = c ^ _key;

		//VMProtectEnd();

		return result;
	}

public:
	template < size_t... Is >
	constexpr __forceinline XorString(const char* str, std::index_sequence< Is... >) : _key(RandomChar< K >::value), _encrypted{ enc(str[Is])... } {
	}

	__forceinline decltype(auto) decrypt(void)
	{
		//VMProtectBeginMutation("XorString::decrypt");

		for (size_t i = 0; i < N; ++i)
		{

			_encrypted[i] = dec(_encrypted[i]);

		}
		_encrypted[N] = '\0';

		auto encrypted = _encrypted.data();

		//VMProtectEnd();

		return encrypted;
	}
};

#define XorStr( s ) ( XorCompileTime::XorString< sizeof( s ) - 1, __COUNTER__ >( s, std::make_index_sequence< sizeof( s ) - 1>() ).decrypt() )

END_NAMESPACE
*/