/**
 * @brief Register_util
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2019 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include <cstdint>

class Register_util
{
public:

	template<typename T>
	static inline void mask_set_bits(volatile T* const reg, const T mask, const T x)
	{
		*reg = ((*reg) & (~mask)) | x;
	}

	template<typename T>
	static inline void set_bits(volatile T* const reg, const T x)
	{
		*reg = (*reg) | x;
	}

	template<typename T>
	static inline void clear_bits(volatile T* const reg, const T x)
	{
		*reg = (*reg) & (~x);
	}

	template<typename T>
	static inline void wait_until_set(volatile T* const reg, const T x)
	{
		while(((*reg) & x) == 0)
		{

		}
	}

	template<typename T>
	static inline void wait_until_clear(volatile T* const reg, const T x)
	{
		while(((*reg) & x) != 0)
		{
			
		}
	}

	template<typename T>
	static inline void wait_until_value(volatile T* const reg, const T mask, const T val)
	{
		while(((*reg) & mask) != val)
		{
			
		}
	}

protected:

};
