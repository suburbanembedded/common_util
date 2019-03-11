#pragma once

#include <functional>
#include <iterator>
#include <utility>


template<class Iter, class Comp>
void insertion_sort(Iter begin, Iter end, Comp comp_lt)
{
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