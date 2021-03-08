/**
 * @brief Byte_util
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2018-2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include <array>
#include <cstdint>

class Byte_util
{
public:

	static constexpr bool hex_to_nibble(const char c, uint8_t* const n)
	{
		if( (c >= '0') && (c <= '9') )
		{
			*n = c - '0';
		}
		else if( (c >= 'A') && (c <= 'F') )
		{
			*n = (c - 'A') + 10;
		}
		else
		{
			return false;
		}

		return true;
	}

	static constexpr bool hex_to_byte(const char c[2], uint8_t* const n)
	{
		uint8_t n1 = 0;
		uint8_t n0 = 0;
		if(!hex_to_nibble(c[0], &n1))
		{
			return false;
		}
		if(!hex_to_nibble(c[1], &n0))
		{
			return false;
		}

		*n = (n1 << 4) | (n0 << 0);

		return true;
	}

	static constexpr bool hex_to_u16(const char c[4], uint16_t* const n)
	{
		uint8_t b1 = 0;
		if(!hex_to_byte(c, &b1))
		{
			return false;
		}

		uint8_t b0 = 0;
		if(!hex_to_byte(c+2, &b0))
		{
			return false;
		}
		
		*n = (uint16_t(b1) << 8) | (uint16_t(b0) << 0);

		return true;
	}

	static constexpr char nibble_to_hex(const uint8_t n)
	{
		return nibble_hex_lut[ get_n0(n) ];
	}

	static void nibble_to_hex(const uint8_t n, char* c)
	{
		*c = nibble_to_hex(n);
	}

	static void u8_to_hex(const uint8_t n, char c[2])
	{
		c[0] = nibble_hex_lut[ get_n1(n) ];
		c[1] = nibble_hex_lut[ get_n0(n) ];
	}

	static void u16_to_hex(const uint32_t n, char c[4])
	{
		u8_to_hex(Byte_util::get_b1(n), c + 0);
		u8_to_hex(Byte_util::get_b0(n), c + 2);
	}

	static void u32_to_hex(const uint32_t n, char c[8])
	{
		u8_to_hex(Byte_util::get_b3(n), c + 0);
		u8_to_hex(Byte_util::get_b2(n), c + 2);
		u8_to_hex(Byte_util::get_b1(n), c + 4);
		u8_to_hex(Byte_util::get_b0(n), c + 6);
	}

	static void u64_to_hex(const uint32_t n, char c[16])
	{
		u8_to_hex(Byte_util::get_b7(n), c + 0);
		u8_to_hex(Byte_util::get_b6(n), c + 2);
		u8_to_hex(Byte_util::get_b5(n), c + 4);
		u8_to_hex(Byte_util::get_b4(n), c + 6);
		u8_to_hex(Byte_util::get_b3(n), c + 8);
		u8_to_hex(Byte_util::get_b2(n), c + 10);
		u8_to_hex(Byte_util::get_b1(n), c + 12);
		u8_to_hex(Byte_util::get_b0(n), c + 14);
	}

	static void u8_to_hex_str(const uint8_t n, std::array<char, 3>* const out_str)
	{
		u8_to_hex(n, out_str->data());
		out_str->back() = '\0';
	}
	static void u16_to_hex_str(const uint16_t n, std::array<char, 5>* const out_str)
	{
		u16_to_hex(n, out_str->data());
		out_str->back() = '\0';
	}
	static void u32_to_hex_str(const uint32_t n, std::array<char, 9>* const out_str)
	{
		u32_to_hex(n, out_str->data());
		out_str->back() = '\0';
	}
	static void u64_to_hex_str(const uint64_t n, std::array<char, 17>* const out_str)
	{
		u64_to_hex(n, out_str->data());
		out_str->back() = '\0';
	}

	static bool hex_str_to_u8(const std::array<char, 3>& str, uint8_t* const out_n)
	{
		return hex_to_byte(str.data(), out_n);
	}

	template <typename T>
	static bool hex_str_to_uT(const std::array<char, sizeof(T)*2+1>& str, T* const out_n)
	{
		T temp = 0;

		char const* str_ptr = str.data();

		for(size_t i = 0; i < sizeof(T); i++)
		{
			uint8_t b = 0;
			if(!hex_to_byte(str_ptr, &b))
			{
				return false;
			}

			str_ptr += 2;

			temp <<= 8;
			temp |= b;
		}

		*out_n = temp;

		return true;
	}

	static bool hex_str_to_u16(const std::array<char, 5>& str, uint16_t* const out_n)
	{
		return hex_str_to_uT<uint16_t>(str, out_n);
	}

	static bool hex_str_to_u32(const std::array<char, 9>& str, uint32_t* const out_n)
	{
		return hex_str_to_uT<uint32_t>(str, out_n);
	}

	static bool hex_str_to_u64(const std::array<char, 17>& str, uint64_t* const out_n)
	{
		return hex_str_to_uT<uint64_t>(str, out_n);
	}

	static constexpr char ascii_to_upper(const char c)
	{
		return c & ~(0x20);
	}

	static constexpr char ascii_to_lower(const char c)
	{
		return c | 0x20;
	}

	static constexpr uint8_t get_n0(const uint8_t x)
	{
		return (x >> 0) & 0x0F;
	}

	static constexpr uint8_t get_n1(const uint8_t x)
	{
		return (x >> 4) & 0x0F;
	}

	static constexpr uint8_t get_b0(const uint16_t x)
	{
		return (x >> 0) & 0x00FF;
	}

	static constexpr uint8_t get_b1(const uint16_t x)
	{
		return (x >> 8) & 0x00FF;
	}

	static constexpr uint8_t get_b0(const uint32_t x)
	{
		return (x >> 0) & 0x000000FF;
	}

	static constexpr uint8_t get_b1(const uint32_t x)
	{
		return (x >> 8) & 0x000000FF;
	}

	static constexpr uint8_t get_b2(const uint32_t x)
	{
		return (x >> 16) & 0x000000FF;
	}

	static constexpr uint8_t get_b3(const uint32_t x)
	{
		return (x >> 24) & 0x000000FF;
	}

	static constexpr uint8_t get_b0(const uint64_t x)
	{
		return uint32_t(x >> 0) & 0x000000FF;
	}

	static constexpr uint8_t get_b1(const uint64_t x)
	{
		return uint32_t(x >> 8) & 0x000000FF;
	}

	static constexpr uint8_t get_b2(const uint64_t x)
	{
		return uint32_t(x >> 16) & 0x000000FF;
	}

	static constexpr uint8_t get_b3(const uint64_t x)
	{
		return uint32_t(x >> 24) & 0x000000FF;
	}

	static constexpr uint8_t get_b4(const uint64_t x)
	{
		return uint32_t(x >> 32) & 0x000000FF;
	}

	static constexpr uint8_t get_b5(const uint64_t x)
	{
		return uint32_t(x >> 40) & 0x000000FF;
	}

	static constexpr uint8_t get_b6(const uint64_t x)
	{
		return uint32_t(x >> 48) & 0x000000FF;
	}

	static constexpr uint8_t get_b7(const uint64_t x)
	{
		return uint32_t(x >> 56) & 0x000000FF;
	}

	static constexpr uint8_t bv_8(const uint8_t x)
	{
		return 1U << x;
	}

	static constexpr uint16_t bv_16(const uint8_t x)
	{
		return 1U << x;
	}

	static constexpr uint32_t bv_32(const uint8_t x)
	{
		return 1U << x;
	}

	static constexpr uint64_t bv_64(const uint8_t x)
	{
		return 1U << x;
	}

	static constexpr uint8_t set_bv_8(uint8_t w, bool set, const uint8_t x)
	{
		return (set) ? (w | (1U << x)) : (w & ~(1U << x));
	}

	static constexpr uint16_t set_bv_16(uint16_t w, bool set, const uint8_t x)
	{
		return (set) ? (w | (1U << x)) : (w & ~(1U << x));
	}

	static constexpr uint32_t set_bv_32(uint32_t w, bool set, const uint8_t x)
	{
		return (set) ? (w | (1U << x)) : (w & ~(1U << x));
	}

	static constexpr uint64_t set_bv_64(uint32_t w, bool set, const uint8_t x)
	{
		return (set) ? (w | (1U << x)) : (w & ~(1U << x));
	}

	static constexpr uint16_t make_u16(const uint8_t b1, const uint8_t b0)
	{
		return (uint16_t(b1) <<  8) |
			   (uint16_t(b0) <<  0);
	}

	static constexpr uint32_t make_u32(const uint16_t h1, const uint16_t h0)
	{
		return (uint32_t(h1) << 16) |
			   (uint32_t(h0) <<  0);
	}

	static constexpr uint32_t make_u32(const uint8_t b3, const uint8_t b2, const uint8_t b1, const uint8_t b0)
	{
		return (uint32_t(b3) << 24) | 
			   (uint32_t(b2) << 16) |
			   (uint32_t(b1) <<  8) |
			   (uint32_t(b0) <<  0);
	}

	static constexpr uint64_t make_u64(const uint32_t h1, const uint32_t h0)
	{
		return (uint64_t(h1) << 32) |
			   (uint64_t(h0) <<  0);
	}

	static constexpr uint64_t make_u64(const uint8_t b7, const uint8_t b6, const uint8_t b5, const uint8_t b4, const uint8_t b3, const uint8_t b2, const uint8_t b1, const uint8_t b0)
	{
		return make_u64(make_u32(b7, b6, b5, b4), make_u32(b3, b2, b1, b0));
	}

	static constexpr uint8_t get_upper_half(const uint16_t x)
	{
		return uint8_t(x >> 8);
	}

	static constexpr uint8_t get_lower_half(const uint16_t x)
	{
		return uint8_t(x & 0x00FF);
	}

	static constexpr uint16_t get_upper_half(const uint32_t x)
	{
		return uint16_t(x >> 16);
	}

	static constexpr uint16_t get_lower_half(const uint32_t x)
	{
		return uint16_t(x & 0x0000FFFF);
	}

	static constexpr uint32_t get_upper_half(const uint64_t x)
	{
		return uint32_t(x >> 32);
	}

	static constexpr uint32_t get_lower_half(const uint64_t x)
	{
		return uint32_t(x & 0x00000000FFFFFFFF);
	}

	///
	/// (val << pos) & mask
	///
	static constexpr uint32_t rmw_mask(const uint32_t initial, const uint32_t val, const uint8_t pos, const uint32_t mask)
	{
		return (initial & (~mask)) | ((val << pos) & mask);
	}

	static constexpr uint8_t mask_rshift(const uint8_t val, const uint8_t mask, const uint8_t rshift)
	{
		return (val & mask) << rshift;
	}

	static constexpr uint16_t mask_rshift(const uint16_t val, const uint16_t mask, const uint8_t rshift)
	{
		return (val & mask) << rshift;
	}

	static constexpr uint32_t mask_rshift(const uint32_t val, const uint32_t mask, const uint8_t rshift)
	{
		return (val & mask) << rshift;
	}

	template <typename T, typename U>
	static constexpr T mask_rshift(const U& val, const T mask, const uint8_t rshift)
	{
		return mask_rshift(T(val), mask, rshift);
	}

	static constexpr uint8_t mask_lshift(const uint8_t val, const uint8_t mask, const uint8_t lshift)
	{
		return (val & mask) >> lshift;
	}

	static constexpr uint16_t mask_lshift(const uint16_t val, const uint16_t mask, const uint8_t lshift)
	{
		return (val & mask) >> lshift;
	}

	static constexpr uint32_t mask_lshift(const uint32_t val, const uint32_t mask, const uint8_t lshift)
	{
		return (val & mask) >> lshift;
	}

	template <typename T, typename U>
	static constexpr T mask_lshift(const U& val, const T mask, const uint8_t lshift)
	{
		return mask_lshift(T(val), mask, lshift);
	}

protected:

	static constexpr char nibble_hex_lut[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

};
