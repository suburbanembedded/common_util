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

	~Intrusive_slist_node() = default;

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

	typedef iterator_base<Intrusive_slist_node> iterator_type;
	typedef iterator_base<const Intrusive_slist_node> const_iterator_type;

	Intrusive_slist()
	{
		m_head = nullptr;
	}

	~Intrusive_slist() = default;

	//copy & assign are banned
	//Since the nodes are owned externally, it is probably a bad idea to clone the list.
	Intrusive_slist(const Intrusive_slist& rhs) = delete;
	Intrusive_slist& operator=(const Intrusive_slist& rhs) = delete;

	//permit move
	Intrusive_slist(Intrusive_slist&& rhs)
	{
		m_head = rhs.m_head;
		rhs.m_head = nullptr;
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
		static_assert(std::is_base_of<Intrusive_slist_node, T>::value);

		return static_cast<T*>(m_head);
	}

	template<typename T>
	const T* front() const
	{
		static_assert(std::is_base_of<Intrusive_slist_node, T>::value);
		
		return static_cast<const T*>(m_head);
	}

	bool empty() const
	{
		return m_head == nullptr;
	}

	size_t size() const
	{
		size_t count = 0;
		Intrusive_slist_node const * n = m_head;
		while(n)
		{
			count++;
			n = n->m_next;
		}

		return count;
	}

	void push_front(Intrusive_slist_node* const node)
	{
		if(m_head)
		{
			node->m_next = m_head;
		}
		else
		{
			node->m_next = nullptr;
		}
		
		m_head = node;
	}

	void pop_front()
	{
		if(m_head)
		{
			m_head = m_head->m_next;
		}
	}

	bool erase(Intrusive_slist_node* const node)
	{
		if(empty())
		{
			return false;
		}

		Intrusive_slist_node* prev = nullptr;
		Intrusive_slist_node* curr = m_head;
		Intrusive_slist_node* next = curr->m_next;

		if(node == m_head)
		{
			curr->m_next = nullptr;	
			m_head = next;
			return true;
		}

		while(curr)
		{
			if(curr == node)
			{
				if(prev)
				{
					prev->m_next = next;
				}

				node->m_next = nullptr;
				return true;
			}

			prev = curr;
			curr = curr->m_next;
			next = curr->m_next;
		}

		return false;
	}

protected:
	Intrusive_slist_node* m_head;
};
