/**
 * @brief stack_string_base
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#include "common_util/Stack_string_base.hpp"

#include <cstdarg>
#include <cstdio>

Stack_string_base& Stack_string_base::append(const Stack_string_base& str)
{
	append(str.data(), str.size());

	return *this;
}
Stack_string_base& Stack_string_base::append(const char* str)
{
	if(!str)
	{
		return *this;
	}

	const size_t str_len = strlen(str);
	const size_t num_to_copy = std::min(str_len, free_space());
		
	std::copy_n(str, num_to_copy, m_str + m_len);
	m_len += num_to_copy;
	m_str[m_len] = 0;

	return *this;
}

Stack_string_base& Stack_string_base::append(const char* str, size_t n)
{
	if(!str)
	{
		return *this;
	}

	const size_t str_len = strlen(str);
	const size_t num_to_copy = std::min(str_len, std::min(n, free_space()));

	std::copy_n(str, num_to_copy, m_str + m_len);
	m_len += num_to_copy;
	m_str[m_len] = 0;

	return *this;
}

Stack_string_base& Stack_string_base::append(size_t n, const char c)
{
	const size_t num_to_copy = std::min(n, free_space());

	for(size_t i = 0; i < num_to_copy; i++)
	{
		m_str[m_len] = c;
		m_len++;
	}

	m_str[m_len] = 0;

	return *this;
}

Stack_string_base& Stack_string_base::assign(const Stack_string_base& str)
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

int Stack_string_base::sprintf(const char *format, ...)
{

	//next open spot
	char* const buf_start = (&back()) + 1;

	//we already account for the null in capacity()
	const size_t char_len = free_space();
	const size_t buf_len = char_len + 1;

	va_list args;
	va_start(args, format);
	int ret = vsnprintf(buf_start, buf_len, format, args);
	va_end(args);

	if(ret < 0)
	{
		return ret;
	}

	if(size_t(ret) <= char_len)
	{
		m_len += ret;
	}
	else
	{
		m_len += char_len;
	}

	return ret;
}
