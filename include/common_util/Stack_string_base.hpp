/**
 * @brief stack_string
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include <algorithm>

#include <cstddef>
#include <cstring>

class Stack_string_base
{
public:

	Stack_string_base()
	{
		clear();
	}

	virtual ~Stack_string_base()
	{

	}

	void set_buffer(char* const buf, const size_t max)
	{
		m_str = buf;
		m_str[0] = 0;
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
		if(count < size())
		{
			m_len = count;
			m_str[m_len] = 0;
		}
		else if(count > size())
		{
			count = std::min(count, capacity() - size());
			std::fill_n(m_str + m_len, count - size(), char());
			m_len += count;
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

	//includes trailing null
	size_t max_size() const
	{
		return m_max;
	}

	bool empty() const
	{
		return m_len == 0;
	}

	char operator[](int idx)
	{
		return m_str[idx];
	}

	const char operator[](int idx) const
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
		}
	}
	
	void pop_back()
	{
		if(m_len < 1)
		{
			m_len--;
			m_str[m_len] = 0;
		}
	}

	Stack_string_base& append(Stack_string_base& str);
	Stack_string_base& append(const char* str);
	Stack_string_base& append(const char* str, size_t n);
	Stack_string_base& append(size_t n, const char c);

	template<class Iter>
	Stack_string_base& append(Iter first, Iter last)
	{
		const size_t num_to_copy = std::min(std::distance(first, last), capacity() - size());

		std::copy_n(first, num_to_copy, m_str + m_len);
		m_len += num_to_copy;

		return *this;
	}

	Stack_string_base& assign(Stack_string_base& str);
	Stack_string_base& assign(const char* str);
	Stack_string_base& assign(const char* str, size_t n);
	Stack_string_base& assign(size_t n, const char c);

	template<class Iter>
	Stack_string_base& assign(Iter first, Iter last)
	{
		clear();
		return append(first, last);
	}

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
