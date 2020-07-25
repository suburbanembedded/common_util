/**
 * @brief Intrusive doubly linked list 
 * @author Jacob Schloss <jacob@schloss.io>
 * @copyright Copyright (c) 2018 Jacob Schloss. All rights reserved.
 * @license Licensed under the 3-Clause BSD license. See LICENSE for details
*/

#pragma once

#include "common_util/Non_copyable.hpp"

#include <cstddef>
#include <type_traits>
#include <iterator>

//An intrusive doubly linked list for general use
//Nodes can be allocated wherever, for OS use they are generally on a thread's stack

class Intrusive_list;

class Intrusive_list_node
{
public:

	friend class Intrusive_list;

	Intrusive_list_node()
	{
		m_prev = nullptr;
		m_next = nullptr;
	}

	virtual ~Intrusive_list_node()
	{

	}

	//copy & assign are default
	Intrusive_list_node(const Intrusive_list_node& rhs) = default;
	Intrusive_list_node& operator=(const Intrusive_list_node& rhs) = default;

	//permit move
	Intrusive_list_node(Intrusive_list_node&& rhs)
	{
		m_prev = rhs.m_prev;
		m_next = rhs.m_next;
		rhs.m_prev = nullptr;
		rhs.m_next = nullptr;
	}

	Intrusive_list_node* prev()
	{
		return m_prev;
	}

	Intrusive_list_node const * prev() const
	{
		return m_prev;
	}

	Intrusive_list_node* next()
	{
		return m_next;
	}

	Intrusive_list_node const * next() const
	{
		return m_next;
	}

	template<typename T>
	T* prev()
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		return static_cast<T*>(m_prev);
	}

	template<typename T>
	T const * prev() const
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		return static_cast<const T*>(m_prev);
	}

	template<typename T>
	T* next()
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		return static_cast<T*>(m_next);
	}

	template<typename T>
	T const * next() const 
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		return static_cast<const T*>(m_next);
	}

protected:
	Intrusive_list_node* m_prev;
	Intrusive_list_node* m_next;
};

//in this list, nodes are held on the stack externally
//lifetime of nodes must be managed by the creator
class Intrusive_list : private Non_copyable
{
public:

	template<typename T>
	class const_iterator_base
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = const T&;

		const_iterator_base() : m_node_ptr(nullptr)
		{
			
		}

		const_iterator_base(pointer node) : m_node_ptr(node)
		{
			
		}

		//pointer ops
		reference operator*() const
		{
			return *m_node_ptr;
		}
		// const value_type* operator->()  const 
		// {
		// 	return &m_node_ptr;
		// }

		//inc & dec
		const_iterator_base& operator++()
		{
			m_node_ptr = &((*m_node_ptr)->m_next);
			return *this;
		}
		const_iterator_base operator++(int)     
		{
			pointer tmp = m_node_ptr;
			++*this;
			return const_iterator_base(tmp);			
		}
		const_iterator_base& operator--()
		{
			m_node_ptr = &((*m_node_ptr)->m_prev);
			return *this;
		}
		const_iterator_base operator--(int)
		{
			pointer tmp = m_node_ptr;
			--*this;
			return const_iterator_base(tmp);
		}

		//comparison
		bool operator== (const const_iterator_base& rhs) const
		{
			return m_node_ptr == rhs.m_node_ptr;
		}
		bool operator!= (const const_iterator_base& rhs) const
		{
			return m_node_ptr != rhs.m_node_ptr;
		}

	protected:
		pointer m_node_ptr;
	};

	template<typename T>
	class iterator_base : public const_iterator_base< T >
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		iterator_base()
		{
			
		}

		iterator_base(pointer node) : const_iterator_base<T>(node)
		{
			
		}

		//pointer ops
		reference operator*() const
		{
			return *this->m_node_ptr;
		}
		// value_type operator->() 
		// {
		// 	return this->m_node_ptr;
		// }

		//inc & dec
		iterator_base& operator++()
		{
			this->m_node_ptr = &((*this->m_node_ptr)->m_next);
			return *this;
		}
		iterator_base operator++(int)     
		{
			pointer tmp = this->m_node_ptr;
			++*this;
			return iterator_base(tmp);			
		}
		iterator_base& operator--()
		{
			this->m_node_ptr = &((*this->m_node_ptr)->m_prev);
			return *this;
		}
		iterator_base operator--(int)
		{
			pointer tmp = this->m_node_ptr;
			--*this;
			return iterator_base(tmp);
		}

		//comparison
		bool operator== (const iterator_base& rhs) const
		{
			return this->m_node_ptr == rhs.m_node_ptr;
		}
		bool operator!= (const iterator_base& rhs) const
		{
			return this->m_node_ptr != rhs.m_node_ptr;
		}
	};

	typedef iterator_base<Intrusive_list_node*> iterator_type;
	typedef const_iterator_base<Intrusive_list_node*> const_iterator_type;

	Intrusive_list()
	{
		m_sentinel.m_prev = &m_sentinel;
		m_sentinel.m_next = &m_sentinel;
	}

	~Intrusive_list() = default;

	//copy & assign are banned
	//Since the nodes are owned externally, it is probably a bad idea to clone the list.
	Intrusive_list(const Intrusive_list& rhs) = delete;
	Intrusive_list& operator=(const Intrusive_list& rhs) = delete;

	//permit move
	Intrusive_list(Intrusive_list&& rhs)
	{
		m_sentinel.m_prev = rhs.m_sentinel.m_prev;
		m_sentinel.m_next = rhs.m_sentinel.m_next;
		rhs.m_sentinel.m_prev = &rhs.m_sentinel;
		rhs.m_sentinel.m_next = &rhs.m_sentinel;
	}

	iterator_type begin()
	{
		return iterator_type(&(m_sentinel.m_next));
	}
	iterator_type end()
	{
		return iterator_type(&(m_sentinel.m_prev->m_next));
	}

	const_iterator_type cbegin()
	{
		return const_iterator_type(&(m_sentinel.m_next));
	}
	const_iterator_type cend()
	{
		return const_iterator_type(&(m_sentinel.m_prev->m_next));
	}

	Intrusive_list_node const * const get_sentinel() const
	{
		return &m_sentinel;
	}

	template<typename T>
	T* front()
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		if(empty())
		{
			return nullptr;
		}

		return static_cast<T*>(m_sentinel.m_next);
	}

	template<typename T>
	T const * front() const
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		if(empty())
		{
			return nullptr;
		}

		return static_cast<const T*>(m_sentinel.m_next);
	}

	template<typename T>
	T* back()
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		if(empty())
		{
			return nullptr;
		}

		return static_cast<T*>(m_sentinel.m_prev);
	}

	template<typename T>
	T const * back() const 
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		if(empty())
		{
			return nullptr;
		}

		return static_cast<const T*>(m_sentinel.m_prev);
	}

	bool empty() const
	{
		return m_sentinel.m_next == &m_sentinel;
	}

	size_t size() const
	{
		size_t count = 0;
		Intrusive_list_node const * n = m_sentinel.m_next;
		while(n != &m_sentinel)
		{
			count++;
			n = n->m_next;
		}

		return count;
	}

	void push_front(Intrusive_list_node* const node)
	{
		m_sentinel.m_next->m_prev = node;
		node->m_next = m_sentinel.m_next;
		node->m_prev = &m_sentinel;
		m_sentinel.m_next = node;
	}

	void push_back(Intrusive_list_node* const node)
	{
		m_sentinel.m_prev->m_next = node;
		node->m_prev = m_sentinel.m_prev;
		node->m_next = &m_sentinel;
		m_sentinel.m_prev = node;
	}

	void pop_front()
	{
		m_sentinel.m_next = m_sentinel.m_next->m_next;
		m_sentinel.m_next->m_prev = &m_sentinel;
	}

	void pop_back()
	{
		m_sentinel.m_prev = m_sentinel.m_prev->m_prev;
		m_sentinel.m_prev->m_next = &m_sentinel;
	}

	static bool is_node_adj(Intrusive_list_node* const a, Intrusive_list_node* const b)
	{
		const bool ret = (a->m_next == b) || (a->m_prev == b) || (b->m_next == a) || (b->m_prev == a);
		return ret;
	}

	static bool is_a_left_b(Intrusive_list_node* const a, Intrusive_list_node* const b)
	{
		const bool ret = (a->m_next == b);
		return ret;
	}

	static bool is_a_right_b(Intrusive_list_node* const a, Intrusive_list_node* const b)
	{
		const bool ret = (a->m_prev == b);
		return ret;
	}

	void erase(Intrusive_list_node* const node)
	{
		unlink(node);
	}

	static void swap(Intrusive_list_node* const a, Intrusive_list_node* const b)
	{
		if(a == b)
		{
			return;
		}

		if(is_a_left_b(a, b))
		{
			Intrusive_list_node* lhs = a;
			Intrusive_list_node* rhs = b;

			swap_adjacent(lhs, rhs);
		}
		else if(is_a_right_b(a, b))
		{
			Intrusive_list_node* lhs = b;
			Intrusive_list_node* rhs = a;

			swap_adjacent(lhs, rhs);
		}
		else
		{
			Intrusive_list_node* a_prev = unlink(a);
			Intrusive_list_node* b_prev = unlink(b);

			insert(a_prev, b);
			insert(b_prev, a);
		}
	}

protected:

	static void swap_adjacent(Intrusive_list_node* const lhs, Intrusive_list_node* const rhs)
	{
		Intrusive_list_node* const lhs_prev = lhs->m_prev;
		Intrusive_list_node* const rhs_next = rhs->m_next;

		lhs->m_prev = rhs;
		lhs->m_next = rhs_next;

		rhs->m_prev = lhs_prev;
		rhs->m_next = lhs;

		lhs_prev->m_next = rhs;

		rhs_next->m_prev = lhs;
	}

	static void insert(Intrusive_list_node* const prev, Intrusive_list_node* const node)
	{
		node->m_next = prev->m_next;
		prev->m_next = node;
		node->m_prev = prev;
	}

	static Intrusive_list_node* unlink(Intrusive_list_node* const node)
	{
		Intrusive_list_node* const n_prev = node->m_prev;
		Intrusive_list_node* const n_next = node->m_next;

		n_prev->m_next = n_next;
		n_next->m_prev = n_prev;

		node->m_next = nullptr;
		node->m_prev = nullptr;

		return n_prev;
	}

	Intrusive_list_node m_sentinel;
};

void swap(Intrusive_list_node* const a, Intrusive_list_node* const b)
{
	Intrusive_list::swap(a, b);
}
