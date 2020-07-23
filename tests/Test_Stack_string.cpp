#include "common_util/Stack_string.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace
{
	TEST(Stack_string, construct_0)
	{
		Stack_string<0> str;

		EXPECT_TRUE(str.empty());
		EXPECT_EQ(str.size(), 0);
		EXPECT_EQ(str.capacity(), 0);
		EXPECT_EQ(str.free_space(), 0);
		EXPECT_EQ(str.max_size(), 1);
	}

	TEST(Stack_string, construct_8)
	{
		Stack_string<8> str;

		EXPECT_TRUE(str.empty());
		EXPECT_EQ(str.size(), 0);
		EXPECT_EQ(str.capacity(), 8);
		EXPECT_EQ(str.free_space(), 8);
		EXPECT_EQ(str.max_size(), 9);
	}

	TEST(Stack_string, clear_empty)
	{
		Stack_string<8> str;
		str.clear();
	}

	TEST(Stack_string, clear)
	{
		Stack_string<8> str;
		str.append("abcd");
		EXPECT_STREQ(str.c_str(), "abcd");
		EXPECT_FALSE(str.empty());
		EXPECT_EQ(str.size(), 4);

		str.clear();
		EXPECT_STREQ(str.c_str(), "");
		EXPECT_TRUE(str.empty());
		EXPECT_EQ(str.size(), 0);
	}

	TEST(Stack_string, resize_shrink)
	{
		Stack_string<8> str;
		str.append("abcdefgh");
		str.resize(4);
		EXPECT_EQ(str.size(), 4);
		EXPECT_STREQ(str.c_str(), "abcd");
	}

	TEST(Stack_string, resize_nop)
	{
		Stack_string<8> str;
		str.append("abcdef");
		str.resize(6);
		EXPECT_EQ(str.size(), 6);
		EXPECT_STREQ(str.c_str(), "abcdef");
	}

	TEST(Stack_string, resize_grow)
	{
		{
			Stack_string<8> str;
			str.resize(4);
			EXPECT_EQ(str.size(), 4);
			EXPECT_EQ(str[0], 0);
			EXPECT_EQ(str[1], 0);
			EXPECT_EQ(str[2], 0);
			EXPECT_EQ(str[3], 0);

			str.resize(12);
			EXPECT_EQ(str.size(), 8);
			EXPECT_EQ(str[0], 0);
			EXPECT_EQ(str[1], 0);
			EXPECT_EQ(str[2], 0);
			EXPECT_EQ(str[3], 0);
			EXPECT_EQ(str[4], 0);
			EXPECT_EQ(str[5], 0);
			EXPECT_EQ(str[6], 0);
			EXPECT_EQ(str[7], 0);
		}

		{

			Stack_string<8> str;
			str.append("abcd");
			
			str.resize(6);
			EXPECT_EQ(str.size(), 6);
			EXPECT_STREQ(str.c_str(), "abcd");
			EXPECT_EQ(str[5], 0);
			EXPECT_EQ(str[6], 0);
		}
	}

	TEST(Stack_string, push_back)
	{
		Stack_string<4> str;

		str.push_back('a');
		str.push_back('b');
		str.push_back('c');
		str.push_back('d');
		str.push_back('e');

		EXPECT_FALSE(str.empty());
		EXPECT_EQ(str.size(), 4);
		EXPECT_EQ(str.capacity(), 4);
		EXPECT_EQ(str.free_space(), 0);
		EXPECT_EQ(str.max_size(), 5);

		EXPECT_STREQ(str.c_str(), "abcd");
		EXPECT_STREQ(str.data(), "abcd");
	}

	TEST(Stack_string, pop_back)
	{
		Stack_string<4> str;

		str.push_back('a');
		str.push_back('b');
		str.push_back('c');
		str.push_back('d');
		str.push_back('e');
		str.pop_back();

		EXPECT_FALSE(str.empty());
		EXPECT_EQ(str.size(), 3);
		EXPECT_EQ(str.capacity(), 4);
		EXPECT_EQ(str.free_space(), 1);
		EXPECT_EQ(str.max_size(), 5);

		EXPECT_STREQ(str.c_str(), "abc");
		EXPECT_STREQ(str.data(), "abc");

		str.pop_back();
		EXPECT_EQ(str.size(), 2);
		EXPECT_EQ(str.free_space(), 2);
		EXPECT_STREQ(str.c_str(), "ab");

		str.pop_back();
		EXPECT_EQ(str.size(), 1);
		EXPECT_EQ(str.free_space(), 3);
		EXPECT_STREQ(str.c_str(), "a");

		str.pop_back();
		EXPECT_EQ(str.size(), 0);
		EXPECT_EQ(str.free_space(), 4);
		EXPECT_STREQ(str.c_str(), "");

		str.pop_back();
		EXPECT_TRUE(str.empty());
		EXPECT_EQ(str.size(), 0);
		EXPECT_EQ(str.free_space(), 4);
		EXPECT_STREQ(str.c_str(), "");
	}

	TEST(Stack_string, operator_idx)
	{
		Stack_string<16> str_a;
		str_a.append("abcdef");

		EXPECT_EQ(str_a[0], 'a');
		EXPECT_EQ(str_a[1], 'b');
		EXPECT_EQ(str_a[2], 'c');
		EXPECT_EQ(str_a[3], 'd');
		EXPECT_EQ(str_a[4], 'e');
		EXPECT_EQ(str_a[5], 'f');

		str_a[3] = 'z';
		EXPECT_EQ(str_a[0], 'a');
		EXPECT_EQ(str_a[1], 'b');
		EXPECT_EQ(str_a[2], 'c');
		EXPECT_EQ(str_a[3], 'z');
		EXPECT_EQ(str_a[4], 'e');
		EXPECT_EQ(str_a[5], 'f');
	}

	TEST(Stack_string, operator_idx_const)
	{
		Stack_string<16> str_a;
		str_a.append("abcdef");

		const Stack_string<16>& str_b = str_a;

		EXPECT_EQ(str_b[0], 'a');
		EXPECT_EQ(str_b[1], 'b');
		EXPECT_EQ(str_b[2], 'c');
		EXPECT_EQ(str_b[3], 'd');
		EXPECT_EQ(str_b[4], 'e');
		EXPECT_EQ(str_b[5], 'f');
	}

	TEST(Stack_string, append_str)
	{
		{	
			Stack_string<4> str_a;
			str_a.push_back('b');

			Stack_string<4> str_b;
			str_b.push_back('a');

			str_b.append(str_a);
			EXPECT_EQ(str_b.size(), 2);
			EXPECT_STREQ(str_b.c_str(), "ab");
		}

		{
			Stack_string<16> str_a;
			str_a.append("bcdef");

			Stack_string<4> str_b;
			str_b.append("a");

			str_b.append(str_a);
			EXPECT_EQ(str_b.size(), 4);
			EXPECT_STREQ(str_b.c_str(), "abcd");
		}
	}

	TEST(Stack_string, append_cstr)
	{
		Stack_string<4> str_a;
		str_a.push_back('a');

		str_a.append("bc");
		EXPECT_EQ(str_a.size(), 3);
		EXPECT_STREQ(str_a.c_str(), "abc");

		str_a.append("def");
		EXPECT_EQ(str_a.size(), 4);
		EXPECT_STREQ(str_a.c_str(), "abcd");
	}

	TEST(Stack_string, append_cstr_n)
	{
		{
			Stack_string<4> str_a;
			str_a.push_back('a');

			str_a.append("bcdef", 2);
			EXPECT_EQ(str_a.size(), 3);
			EXPECT_STREQ(str_a.c_str(), "abc");
		}

		{
			Stack_string<4> str_a;
			str_a.push_back('a');

			str_a.append("bcdef", 5);
			EXPECT_EQ(str_a.size(), 4);
			EXPECT_STREQ(str_a.c_str(), "abcd");
		}
	}

	TEST(Stack_string, append_n_c)
	{
		{	
			Stack_string<4> str_a;
			str_a.append(0, 'a');
			EXPECT_EQ(str_a.size(), 0);
			EXPECT_STREQ(str_a.c_str(), "");
		}

		{	
			Stack_string<4> str_a;
			str_a.append(3, 'a');
			EXPECT_EQ(str_a.size(), 3);
			EXPECT_STREQ(str_a.c_str(), "aaa");
		}

		{	
			Stack_string<4> str_a;
			str_a.append(5, 'a');
			EXPECT_EQ(str_a.size(), 4);
			EXPECT_STREQ(str_a.c_str(), "aaaa");
		}
	}

	TEST(Stack_string, append_iter)
	{
		{	
			Stack_string<4> str_a;

			std::array<char, 4> str_b = {'a', 'b', 'c', 'd'};

			str_a.append(str_b.cbegin(), str_b.cend());

			EXPECT_EQ(str_a.size(), 4);
			EXPECT_STREQ(str_a.c_str(), "abcd");
		}

		{	
			Stack_string<2> str_a;

			std::array<char, 4> str_b = {'a', 'b', 'c', 'd'};

			str_a.append(str_b.cbegin(), str_b.cend());

			EXPECT_EQ(str_a.size(), 2);
			EXPECT_STREQ(str_a.c_str(), "ab");
		}
	}

	TEST(Stack_string, sprintf)
	{
		Stack_string<4> str_a;
		int ret = str_a.sprintf("%s", "abcd");

		EXPECT_EQ(ret, 4);
		EXPECT_EQ(str_a.size(), 4);
		EXPECT_STREQ(str_a.c_str(), "abcd");
	}

	TEST(Stack_string, sprintf_overrun)
	{
		Stack_string<4> str_a;
		int ret = str_a.sprintf("%s", "abcde");

		EXPECT_EQ(ret, 5);
		EXPECT_EQ(str_a.size(), 4);
		EXPECT_STREQ(str_a.c_str(), "abcd");
	}

	TEST(Stack_string, sprintf_append)
	{
		Stack_string<4> str_a;
		str_a.append("a");

		int ret = str_a.sprintf("%s", "b");
		EXPECT_EQ(ret, 1);

		ret = str_a.sprintf("%s", "c");
		EXPECT_EQ(ret, 1);

		ret = str_a.sprintf("%s", "d");
		EXPECT_EQ(ret, 1);

		ret = str_a.sprintf("%s", "e");
		EXPECT_EQ(ret, 1);

		EXPECT_EQ(str_a.size(), 4);
		EXPECT_STREQ(str_a.c_str(), "abcd");	
	}

	TEST(Stack_string, sprintf_format_len)
	{
		Stack_string<4> str_a;
		int ret = str_a.sprintf("%s", "abcde");
		
		EXPECT_EQ(ret, 5);
		EXPECT_EQ(str_a.size(), 4);
		EXPECT_STREQ(str_a.c_str(), "abcd");	
	}

	TEST(Stack_string, sprintf_error)
	{
		Stack_string<4> str_a;
		int ret = str_a.sprintf("%");
		EXPECT_LT(ret, 0);
	}

	TEST(Stack_string, iterator)
	{
		Stack_string<16> str_a;
		str_a.append("abcde");

		Stack_string_base::iterator_type itr = str_a.begin();

		size_t i = 0;
		while(itr != str_a.end())
		{
			ASSERT_EQ(*itr, str_a.data()[i]);
			itr++;
			i++;
		}
	}

	TEST(Stack_string, iterator_range_for)
	{
		Stack_string<16> str_a;
		str_a.append("abcde");

		size_t i = 0;
		for(const auto& c : str_a)
		{
			ASSERT_EQ(c, str_a.data()[i]);
			i++;
		}
	}

	TEST(Stack_string, const_iterator)
	{
		Stack_string<16> str_a;
		str_a.append("abcde");

		Stack_string_base::const_iterator_type itr = str_a.cbegin();

		size_t i = 0;
		while(itr != str_a.cend())
		{
			ASSERT_EQ(*itr, str_a.data()[i]);
			itr++;
			i++;
		}
	}

	TEST(Stack_string, iterator_math)
	{
		Stack_string<16> str_a;
		str_a.append("abcde");

		EXPECT_EQ(5, std::distance(str_a.begin(), str_a.end()));
		EXPECT_EQ(5, std::distance(str_a.cbegin(), str_a.cend()));

		EXPECT_EQ('a', *(str_a.begin()++));
		EXPECT_EQ('b', *(++str_a.begin()));
		EXPECT_EQ('c', *(str_a.begin() + 2));
		EXPECT_EQ('b', *((str_a.begin() + 2) - 1));

		EXPECT_EQ('\0', *(str_a.end()--));
		EXPECT_EQ('e', *(--str_a.end()));
		EXPECT_EQ('d', *((str_a.end() - 3) + 1));

		EXPECT_EQ('b', *(std::next(str_a.begin())));
		EXPECT_EQ('e', *(std::prev(str_a.end())));
	}
}
