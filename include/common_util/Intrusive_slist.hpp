/**
 * @brief Intrusive singly linked list 
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2018 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include "common_util/Non_copyable.hpp"

#include <cstddef>
#include <type_traits>
#include <iterator>

//A minimal intrusive singly linked list for OS use
//Not recommended for general use, since this does not manage memory or have many features

class Intrusive_slist;

class Intrusive_slist_node
{
public:

	friend class Intrusive_slist;

	Intrusive_slist_node()
	{
		m_next = nullptr;
	}

	virtual ~Intrusive_slist_node()
	{
		
	}

	//copy & assign are default
	Intrusive_slist_node(const Intrusive_slist_node& rhs) = default;
	Intrusive_slist_node& operator=(const Intrusive_slist_node& rhs) = default;

	//permit move
	Intrusive_slist_node(Intrusive_slist_node&& rhs)
	{
		m_next = rhs.m_next;
		rhs.m_next = nullptr;
	}

	Intrusive_slist_node* next()
	{
		return m_next;
	}

	const Intrusive_slist_node* next() const
	{
		return m_next;
	}

	template<typename T>
	T* next()
	{
		static_assert(std::is_base_of<Intrusive_slist_node, T>::value);

		return static_cast<T*>(m_next);
	}

	template<typename T>
	T const * next() const 
	{
		static_assert(std::is_base_of<Intrusive_slist_node, T>::value);

		return static_cast<const T*>(m_next);
	}

protected:
	Intrusive_slist_node* m_next;
};

//in this list, nodes are held on the stack externally
//lifetime of nodes must be managed by the creator
class Intrusive_slist : private Non_copyable
{
public:

	template<typename T>
	class iterator_base
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator_base() : m_node_ptr(nullptr)
		{
			
		}

		iterator_base(pointer node) : m_node_ptr(node)
		{
			
		}

		//pointer ops
		reference operator*() const
		{
			return *m_node_ptr;
		}
		// const value_type* operator->()  const 
		// {
		// 	return m_node_ptr;
		// }

		//inc & dec
		iterator_base& operator++()
		{
			m_node_ptr = &((*m_node_ptr)->m_next);
			return *this;
		}
		iterator_base operator++(int)     
		{
			pointer tmp = m_node_ptr;
			++*this;
			return iterator_base(tmp);			
		}

		//comparison
		bool operator== (const iterator_base& rhs)  const
		{
			return *m_node_ptr == *rhs.m_node_ptr;
		}
		bool operator!= (const iterator_base& rhs)  const
		{
			return *m_node_ptr != *rhs.m_node_ptr;
		}

		pointer m_node_ptr;
	};

	typedef iterator_base<Intrusive_slist_node*> iterator_type;
	typedef iterator_base<Intrusive_slist_node const * const> const_iterator_type;

	Intrusive_slist()
	{
		m_sentinel.m_next = &m_sentinel;
		m_sentinel_ptr = &m_sentinel;
	}

	~Intrusive_slist() = default;

	//copy & assign are banned
	//Since the nodes are owned externally, it is probably a bad idea to clone the list.
	Intrusive_slist(const Intrusive_slist& rhs) = delete;
	Intrusive_slist& operator=(const Intrusive_slist& rhs) = delete;

	//permit move
	Intrusive_slist(Intrusive_slist&& rhs)
	{
		m_sentinel.m_next = rhs.m_sentinel.m_next;
		rhs.m_sentinel.m_next = &rhs.m_sentinel;
	}

	iterator_type begin()
	{
		return iterator_type(&(m_sentinel.m_next));
	}
	iterator_type end()
	{
		return iterator_type(&m_sentinel_ptr);
	}

	const_iterator_type cbegin() const
	{
		return const_iterator_type(&(m_sentinel.m_next));
	}
	const_iterator_type cend() const
	{
		return const_iterator_type(&m_sentinel_ptr);
	}

	Intrusive_slist_node const * const get_sentinel() const
	{
		return &m_sentinel;
	}

	template<typename T>
	T* front()
	{
		static_assert(std::is_base_of<Intrusive_slist_node, T>::value);

		if(empty())
		{
			return nullptr;
		}

		return static_cast<T*>(m_sentinel.m_next);
	}

	template<typename T>
	const T* front() const
	{
		static_assert(std::is_base_of<Intrusive_slist_node, T>::value);

		if(empty())
		{
			return nullptr;
		}
		
		return static_cast<const T*>(m_sentinel.m_next);
	}

	bool empty() const
	{
		return m_sentinel.m_next == &m_sentinel;
	}

	size_t size() const
	{
		size_t count = 0;
		Intrusive_slist_node const * n = m_sentinel.m_next;
		while(n != &m_sentinel)
		{
			count++;
			n = n->m_next;
		}

		return count;
	}

	void push_front(Intrusive_slist_node* const node)
	{
		node->m_next = m_sentinel.m_next;
		m_sentinel.m_next = node;

		// if(m_tail == &m_sentinel)
		// {
		// 	m_tail = node;
		// }
	}

	// void push_back(Intrusive_slist_node* const node)
	// {
	// 	m_tail->m_next = node;
	// 	node->m_next = &m_sentinel;
	// }

	void pop_front()
	{
		// if(!empty())
		// {
		// 	m_sentinel.m_next = m_sentinel.m_next->m_next;
		// }
		m_sentinel.m_next = m_sentinel.m_next->m_next;
	}

	bool erase(Intrusive_slist_node* const node)
	{
		return unlink(node);
	}

	static bool is_node_adj(Intrusive_slist_node* const a, Intrusive_slist_node* const b)
	{
		return is_a_left_b(a, b) || is_a_right_b(a, b);
	}

	static bool is_a_left_b(Intrusive_slist_node* const a, Intrusive_slist_node* const b)
	{
		const bool ret = (a->m_next == b);
		return ret;
	}

	static bool is_a_right_b(Intrusive_slist_node* const a, Intrusive_slist_node* const b)
	{
		const bool ret = (b->m_next == a);
		return ret;
	}

	void swap(Intrusive_slist_node* const a, Intrusive_slist_node* const b)
	{
		if(a == b)
		{
			return;
		}

		if(is_a_left_b(a, b))
		{
			Intrusive_slist_node* lhs = a;
			Intrusive_slist_node* rhs = b;

			swap_adjacent(lhs, rhs);
		}
		else if(is_a_right_b(a, b))
		{
			Intrusive_slist_node* lhs = b;
			Intrusive_slist_node* rhs = a;

			swap_adjacent(lhs, rhs);
		}
		else
		{
			Intrusive_slist_node* a_prev = unlink(a);
			Intrusive_slist_node* b_prev = unlink(b);

			insert(a_prev, b);
			insert(b_prev, a);
		}
	}

protected:

	bool swap_adjacent(Intrusive_slist_node* const lhs, Intrusive_slist_node* const rhs)
	{
		bool ret = false;

		Intrusive_slist_node* lhs_prev = &m_sentinel;
		while(lhs_prev->m_next != &m_sentinel)
		{
			if(lhs_prev->m_next == lhs)
			{
				lhs_prev->m_next = rhs;
				lhs->m_next = rhs->m_next;
				rhs->m_next = lhs;
				ret = true;
				break;
			}

			lhs_prev = lhs_prev->m_next;
		}

		return ret;
	}

	Intrusive_slist_node* unlink(Intrusive_slist_node* const node)
	{
		Intrusive_slist_node* prev = &m_sentinel;
		while(prev->m_next != &m_sentinel)
		{
			if(prev->m_next == node)
			{
				unlink_next(prev);
				break;
			}

			prev = prev->m_next;
		}

		return prev;
	}

	static Intrusive_slist_node* unlink_next(Intrusive_slist_node* const prev)
	{
		Intrusive_slist_node* node = prev->m_next;
		prev->m_next = node->m_next;
		node->m_next = nullptr;

		return prev;
	}

	static void insert(Intrusive_slist_node* const prev, Intrusive_slist_node* const node)
	{
		node->m_next = prev->m_next;
		prev->m_next = node;
	}

	Intrusive_slist_node* m_sentinel_ptr;
	Intrusive_slist_node m_sentinel;
	// Intrusive_slist_node* m_tail;
};
