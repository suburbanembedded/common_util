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

	static void u8_to_hex_str(const uint8_t n, std::array<char, 3>* const str)
	{
		(*str)[0] = nibble_hex_lut[ get_n1(n) ];
		(*str)[1] = nibble_hex_lut[ get_n0(n) ];
		(*str)[2] = '\0';
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

	static constexpr uint64_t make_u64(const uint8_t b7, const uint8_t b6, const uint8_t b5, const uint8_t b4, const uint8_t b3, const uint8_t b2, const uint8_t b1, const uint8_t b0)
	{
		return (uint64_t(make_u32(b7, b6, b5, b4)) << 32) | (uint64_t(make_u32(b3, b2, b1, b0)) << 0);
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

protected:

	static constexpr char nibble_hex_lut[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

};
