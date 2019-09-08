/**
 * @brief stack_string
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include <array>

template<size_t LEN>
class Stack_string
{
public:

	Stack_string()
	{
		clear();
	}

	void clear()
	{
		m_str.front() = 0;
		m_len = 0;
	}

	size_t size() const
	{
		return m_len;
	}

	bool empty() const
	{
		return m_len == 0;
	}

	T& operator[](int idx)
	{
		return m_str[idx];
	}

	const T& operator[](int idx) const
	{
		return m_str[idx];
	}

	void push_back(const T& c)
	{

	}
	
	Stack_string& append(Stack_string& str);
	Stack_string& append(const char* str);
	Stack_string& append(const char* str, size_t n);
	Stack_string& append(size_t n, const T& c);

	template<class Iter>
	Stack_string& append(Iter first, Iter last);

	Stack_string& assign(Stack_string& str);
	Stack_string& assign(const char* str);
	Stack_string& assign(const char* str, size_t n);
	Stack_string& assign(size_t n, const T& c);

	const char* c_str();

	const char* data();

protected:

	std::array<char, LEN+1> m_str;
	size_t m_len;
};
