#pragma once

#include <cstdint>

class Byte_util
{
public:

	static bool nibble_to_hex(uint8_t n, char* const c)
	{
		if(n > 15)
		{
			return false;
		}

		*c = nibble_hex_lut[n];

		return true;
	}

	static void u8_to_hex(uint8_t n, char c[2])
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

protected:

	constexpr static char nibble_hex_lut[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

};
