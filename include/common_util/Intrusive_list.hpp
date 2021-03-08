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

	~Intrusive_list_node() = default;

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
	class iterator_base
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
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

		//inc & dec
		iterator_base& operator++()
		{
			if(m_ptr)
			{
				m_ptr = m_ptr->next();
			}
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
			if(m_ptr)
			{
				m_ptr = m_ptr->prev();
			}
			return *this;
		}
		iterator_base operator--(int)
		{
			pointer tmp = m_ptr;
			--*this;
			return iterator_base(tmp);
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

	protected:
		pointer m_ptr;
	};

	typedef iterator_base<Intrusive_list_node> iterator_type;
	typedef iterator_base<const Intrusive_list_node> const_iterator_type;

	Intrusive_list()
	{
		m_head = nullptr;
		m_tail = nullptr;
	}

	~Intrusive_list() = default;

	//copy & assign are banned
	//Since the nodes are owned externally, it is probably a bad idea to clone the list.
	Intrusive_list(const Intrusive_list& rhs) = delete;
	Intrusive_list& operator=(const Intrusive_list& rhs) = delete;

	//permit move
	Intrusive_list(Intrusive_list&& rhs)
	{
		m_head = rhs.m_head;
		m_tail = rhs.m_tail;
		rhs.m_head = nullptr;
		rhs.m_tail = nullptr;
	}

	iterator_type begin()
	{
		return iterator_type(m_head);
	}
	iterator_type end()
	{
		return iterator_type(nullptr);
	}

	const_iterator_type cbegin() const
	{
		return const_iterator_type(m_head);
	}
	const_iterator_type cend() const
	{
		return const_iterator_type(nullptr);
	}

	template<typename T>
	T* front()
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		return static_cast<T*>(m_head);
	}

	template<typename T>
	T const * front() const
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		return static_cast<const T*>(m_head);
	}

	template<typename T>
	T* back()
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		return static_cast<T*>(m_tail);
	}

	template<typename T>
	T const * back() const 
	{
		static_assert(std::is_base_of<Intrusive_list_node, T>::value);

		return static_cast<const T*>(m_tail);
	}

	bool empty() const
	{
		return m_head == nullptr;
	}

	size_t size() const
	{
		size_t count = 0;
		Intrusive_list_node const * n = m_head;
		while(n)
		{
			count++;
			n = n->m_next;
		}

		return count;
	}

	void push_front(Intrusive_list_node* const node)
	{
		if(m_head)
		{
			node->m_next = m_head;
			node->m_prev = nullptr;

			m_head->m_prev = node;
			m_head = node;
		}
		else
		{
			node->m_next = nullptr;
			node->m_prev = nullptr;

			m_head = node;
			m_tail = node;
		}	
	}

	void push_back(Intrusive_list_node* const node)
	{
		if(m_tail)
		{
			node->m_next = nullptr;
			node->m_prev = m_tail;

			m_tail->m_next = node;
			m_tail = node;
		}
		else
		{
			node->m_next = nullptr;
			node->m_prev = nullptr;

			m_head = node;
			m_tail = node;
		}	
	}

	void pop_front()
	{
		if(m_head)
		{
			if(m_head == m_tail)
			{
				m_head = nullptr;
				m_tail = nullptr;
			}
			else
			{
				m_head = m_head->m_next;
				m_head->m_prev = nullptr;
			}
		}
	}

	void pop_back()
	{
		if(m_tail)
		{
			if(m_head == m_tail)
			{
				m_head = nullptr;
				m_tail = nullptr;
			}
			else
			{
				m_tail = m_tail->m_prev;
				m_tail->m_next = nullptr;
			}
		}
	}

protected:
	Intrusive_list_node* m_head;
	Intrusive_list_node* m_tail;
};
