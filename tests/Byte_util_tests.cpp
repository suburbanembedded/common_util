#include "common_util/Byte_util.hpp"

#include "gtest/gtest.h"

#include <array>
#include <vector>

namespace
{
	constexpr std::array<char, 16> hex_digit_map = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	TEST(Byte_util, hex_to_nibble_pass_domain)
	{
		const std::array<uint8_t, 16> expected_output = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
		std::array<uint8_t, 16> output;

		for(size_t i = 0; i < 16; i++)
		{
			EXPECT_TRUE(Byte_util::hex_to_nibble(hex_digit_map[i], output.data()+i));
			EXPECT_EQ(output[i], expected_output[i]);
		}
	}

	TEST(Byte_util, hex_to_nibble_test_pass_fail)
	{
		char in = 0;
		uint8_t out = 0;
		for(size_t i = '\0'; i < '0'; i++)
		{
			in = i;
			EXPECT_FALSE(Byte_util::hex_to_nibble(in, &out));
		}
		for(size_t i = '0'; i < ':'; i++)
		{
			in = i;
			EXPECT_TRUE(Byte_util::hex_to_nibble(in, &out));
		}
		for(size_t i = ':'; i < 'A'; i++)
		{
			in = i;
			EXPECT_FALSE(Byte_util::hex_to_nibble(in, &out));
		}
		for(size_t i = 'A'; i < 'G'; i++)
		{
			in = i;
			EXPECT_TRUE(Byte_util::hex_to_nibble(in, &out));
		}
		for(size_t i = 'G'; i < 128; i++)
		{
			in = i;
			EXPECT_FALSE(Byte_util::hex_to_nibble(in, &out));
		}
	}

	TEST(Byte_util, hex_to_byte_domain)
	{
		for(size_t i = 0; i < 16; i++)
		{
			for(size_t j = 0; j < 16; j++)
			{
				const char input[2] = {hex_digit_map[i], hex_digit_map[j]};
				const uint8_t expected_output = i*16U+j;
				uint8_t output = 0;

				EXPECT_TRUE(Byte_util::hex_to_byte(input, &output));
				EXPECT_EQ(output, expected_output);
			}
		}
	}

	TEST(Byte_util, make_u16)
	{
		EXPECT_EQ(Byte_util::make_u16(0x00, 0x00), 0x0000);

		EXPECT_EQ(Byte_util::make_u16(0x5A, 0x5A), 0x5A5A);

		EXPECT_EQ(Byte_util::make_u16(0x7F, 0x00), 0x7F00);

		EXPECT_EQ(Byte_util::make_u16(0x00, 0xF7), 0x00F7);

		EXPECT_EQ(Byte_util::make_u16(0xA5, 0xA5), 0xA5A5);

		EXPECT_EQ(Byte_util::make_u16(0xFF, 0xFF), 0xFFFF);
	}
}
