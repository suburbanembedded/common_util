/**
 * @brief stack_string_base
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#include "common_util/Stack_string_base.hpp"

Stack_string_base& Stack_string_base::append(Stack_string_base& str)
{
	append(str.data(), str.size());

	return *this;
}
Stack_string_base& Stack_string_base::append(const char* str)
{
	if(str)
	{
		const size_t num_to_copy = strlen(str);
		append(str, num_to_copy);
	}

	return *this;
}

Stack_string_base& Stack_string_base::append(const char* str, size_t n)
{
	const size_t num_to_copy = std::min(n, capacity() - size());

	std::copy_n(str, num_to_copy, m_str + m_len);
	m_len += num_to_copy;

	m_str[m_len] = 0;

	return *this;
}

Stack_string_base& Stack_string_base::append(size_t n, const char c)
{
	const size_t num_to_copy = std::min(n, capacity() - size());

	for(size_t i = 0; i < num_to_copy; i++)
	{
		m_str[m_len] = c;
		m_len++;
	}

	m_str[m_len] = 0;

	return *this;
}

Stack_string_base& Stack_string_base::assign(Stack_string_base& str)
{
	clear();
	return append(str);
}
Stack_string_base& Stack_string_base::assign(const char* str)
{
	clear();
	return append(str);
}
Stack_string_base& Stack_string_base::assign(const char* str, size_t n)
{
	clear();
	return append(str, n);
}
Stack_string_base& Stack_string_base::assign(size_t n, const char c)
{
	clear();
	return append(n, c);
}
