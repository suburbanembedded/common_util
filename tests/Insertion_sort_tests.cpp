#include "common_util/Insertion_sort.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"


#include <array>

namespace
{
	TEST(Insertion_sort, null_range)
	{
		int* a = 0;

		insertion_sort(a, a);
	}

	TEST(Insertion_sort, simple_ints)
	{
		std::array<int, 10> array_orig = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
		std::array<int, 10> array = array_orig;

		insertion_sort(array.begin(), array.end());

		EXPECT_THAT(array, ::testing::ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
	}
}
