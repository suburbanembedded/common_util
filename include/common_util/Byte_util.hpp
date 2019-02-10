#pragma once

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

	static constexpr uint32_t make_u32(const uint8_t b3, const uint8_t b2, const uint8_t b1, const uint8_t b0)
	{
		return (uint32_t(b3) << 24) | 
			   (uint32_t(b2) << 16) |
			   (uint32_t(b1) <<  8) |
			   (uint32_t(b0) <<  0);
	}

protected:

	static constexpr char nibble_hex_lut[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

};
