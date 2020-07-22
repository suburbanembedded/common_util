/**
 * @brief stack_string
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include "common_util/Non_copyable.hpp"

#include <algorithm>
#include <iterator>

#include <cstddef>
#include <cstring>

class Stack_string_base : private Non_copyable
{
public:

	template<typename T>
	class iterator_base
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator_base() : m_ptr(nullptr)
		{
			
		}

		iterator_base(pointer ptr) : m_ptr(ptr)
		{
			
		}

		//pointer ops
		reference operator*() const 
		{
			return *m_ptr;
		}
		const value_type* operator->()  const 
		{
			return m_ptr;
		}
		reference operator[](difference_type offset) const
		{
			return m_ptr[offset];
		}

		//inc & dec
		iterator_base& operator++()
		{
			++m_ptr;
			return *this;
		}
		iterator_base operator++(int)     
		{
			pointer tmp = m_ptr;
			++*this;
			return iterator_base(tmp);			
		}
		iterator_base& operator--()
		{
			--m_ptr;
			return *this;
		}
		iterator_base operator--(int)
		{
			pointer tmp = m_ptr;
			--*this;
			return iterator_base(tmp);
		}

		//pointer math
		iterator_base& operator+=(difference_type offset)
		{
			m_ptr += offset;
			return *this;
		}
		iterator_base operator+(difference_type offset) const
		{
			return iterator_base(m_ptr + offset);
		}
		friend iterator_base operator+(difference_type offset, const iterator_base& rhs)
		{
			return iterator_base(offset + rhs.m_ptr);
		}
		iterator_base& operator-= (difference_type offset)
		{
			m_ptr -= offset;
			return *this;
		}
		iterator_base operator- (difference_type offset) const
		{
			return iterator_base(m_ptr - offset);
		}
		difference_type operator-(const iterator_base& rhs) const
		{
			return m_ptr - rhs.m_ptr;
		}

		//comparison
		bool operator== (const iterator_base& rhs)  const
		{
			return m_ptr == rhs.m_ptr;
		}
		bool operator!= (const iterator_base& rhs)  const
		{
			return m_ptr != rhs.m_ptr;
		}
		bool operator<  (const iterator_base& rhs)  const
		{
			return m_ptr < rhs.m_ptr;
		}
		bool operator<= (const iterator_base& rhs)  const
		{
			return m_ptr <= rhs.m_ptr;
		}
		bool operator>  (const iterator_base& rhs)  const
		{
			return m_ptr > rhs.m_ptr;
		}
		bool operator>= (const iterator_base& rhs)  const
		{
			return m_ptr >= rhs.m_ptr;
		}
	
	protected:
		pointer m_ptr;
	};

	typedef iterator_base<char> iterator_type;
	typedef iterator_base<const char> const_iterator_type;

	Stack_string_base()
	{
		m_str = nullptr;
		m_len = 0;
		m_max = 0;
	}

	virtual ~Stack_string_base()
	{

	}

	iterator_type begin()
	{
		return iterator_type(m_str);
	}
	iterator_type end()
	{
		return iterator_type(m_str + size());
	}

	const_iterator_type cbegin() const
	{
		return const_iterator_type(m_str);
	}
	const_iterator_type cend() const
	{
		return const_iterator_type(m_str + size());
	}

	void set_buffer(char* const buf, const size_t max)
	{
		m_str = buf;
		if(m_str && (max > 0))
		{
			m_str[0] = 0;
		}
		m_len = 0;
		m_max = max;
	}

	void clear()
	{
		m_str[0] = 0;
		m_len = 0;
	}

	void resize(size_t count)
	{
		const size_t new_size = std::min(count, max_size()-1);

		if(new_size < size())
		{
			m_len = new_size;
			m_str[m_len] = 0;
		}
		else if(new_size > size())
		{
			const size_t num_to_copy = std::min(new_size, free_space());
			std::fill_n(m_str + m_len, num_to_copy, char());
			m_len = new_size;
			m_str[m_len] = 0;
		}
	}

	size_t size() const
	{
		return m_len;
	}

	//excludes trailing null
	size_t capacity() const
	{
		return m_max - 1;
	}

	//how many chars can be inserted
	size_t free_space() const
	{
		return capacity() - size();
	}

	//includes trailing null
	size_t max_size() const
	{
		return m_max;
	}

	bool empty() const
	{
		return m_len == 0;
	}

	bool full() const
	{
		return m_len == capacity();
	}

	char& operator[](int idx)
	{
		return m_str[idx];
	}

	const char& operator[](int idx) const
	{
		return m_str[idx];
	}

	char& front()
	{
		return m_str[0];
	}

	const char& front() const
	{
		return m_str[0];
	}

	char& back()
	{
		return m_str[size() - 1];
	}

	const char& back() const
	{
		return m_str[size() - 1];
	}

	void push_back(const char c)
	{
		if(m_len < capacity())
		{
			m_str[m_len] = c;
			m_len++;
			m_str[m_len] = 0;
		}
	}
	
	void pop_back()
	{
		if(!empty())
		{
			m_len--;
			m_str[m_len] = 0;
		}
	}

	Stack_string_base& append(const Stack_string_base& str);
	Stack_string_base& append(const char* str);
	Stack_string_base& append(const char* str, size_t n);
	Stack_string_base& append(size_t n, const char c);

	template<class Iter>
	Stack_string_base& append(Iter first, Iter last)
	{
		const size_t num_to_copy = std::min<size_t>(std::distance(first, last), free_space());

		std::copy_n(first, num_to_copy, m_str + m_len);
		m_len += num_to_copy;
		m_str[m_len] = 0;

		return *this;
	}

	Stack_string_base& assign(const Stack_string_base& str);
	Stack_string_base& assign(const char* str);
	Stack_string_base& assign(const char* str, size_t n);
	Stack_string_base& assign(size_t n, const char c);

	template<class Iter>
	Stack_string_base& assign(Iter first, Iter last)
	{
		clear();
		return append(first, last);
	}

	//appends to back
	int sprintf(const char *format, ...);

	const char* c_str() const
	{
		return m_str;
	}

	// char* c_str()
	// {
	// 	return m_str;
	// }

	const char* data() const
	{
		return m_str;
	}

	// char* data()
	// {
	// 	return m_str;
	// }

protected:

	char* m_str;
	size_t m_len;
	size_t m_max;
};
