#pragma once

class Comparison_util
{
public:

	template<typename T, typename U, typename V>
	constexpr static bool is_within(const T& x, const U& low, const V& high)
	{
		return (low < x) && (x < high);
	}

	template<typename T, typename U, typename V>
	constexpr static bool is_within_inclusive(const T& x, const U& low, const V& high)
	{
		return (low <= x) && (x <= high);
	}
};
