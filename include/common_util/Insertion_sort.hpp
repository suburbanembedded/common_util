/**
 * @brief insertion_sort
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2018 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include <functional>
#include <iterator>
#include <utility>


template<class Iter, class Comp>
void insertion_sort(Iter begin, Iter end, Comp comp_lt)
{
	if(begin == end)
	{
		return;
	}

	Iter i = begin;
	++i;
	for(; i != end; ++i)
	{
		for(Iter j = i; (j != begin) && comp_lt(*j, *std::prev(j)); --j)
		{
			std::iter_swap(j, std::prev(j));
		}
	}
}

template<class Iter>
void insertion_sort(Iter begin, Iter end)
{
	insertion_sort(begin, end, std::less< typename std::iterator_traits<Iter>::value_type >());
}