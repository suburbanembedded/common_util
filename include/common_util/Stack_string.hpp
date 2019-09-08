/**
 * @brief stack_string
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include <array>

#include "common_util/Stack_string_base.hpp"


template<size_t LEN>
class Stack_string : public Stack_string_base
{
public:

	Stack_string()
	{
		set_buffer(m_buf.data(), m_buf.size());
	}


private:
	std::array<char, LEN+1> m_buf;
};
