#include "common_util/Intrusive_slist.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace
{
	TEST(Intrusive_slist, construct)
	{
		Intrusive_slist list;
	}

	TEST(Intrusive_slist, empty_list)
	{
		Intrusive_slist slist;

		ASSERT_TRUE(slist.empty());
		ASSERT_EQ(slist.front<Intrusive_slist_node>(), nullptr);
		ASSERT_EQ(slist.size(), 0);
	}

	TEST(Intrusive_slist, pop_empty)
	{
		Intrusive_slist slist;

		ASSERT_TRUE(slist.empty());
		ASSERT_EQ(slist.front<Intrusive_slist_node>(), nullptr);
		ASSERT_EQ(slist.size(), 0);
		
		slist.pop_front();
		
		ASSERT_TRUE(slist.empty());
		ASSERT_EQ(slist.front<Intrusive_slist_node>(), nullptr);
		ASSERT_EQ(slist.size(), 0);
	}

	TEST(Intrusive_slist, slist_build)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(16);

		Intrusive_slist slist;

		for(size_t i = 0; i < node_storage.size(); i++)
		{
			ASSERT_EQ(slist.size(), i);
			slist.push_front(&(node_storage[i]));
			ASSERT_EQ(slist.size(), i+1);
		}

		ASSERT_FALSE(slist.empty());
		ASSERT_EQ(slist.front<Intrusive_slist_node>(), &(node_storage.back()));

		auto node = slist.front<Intrusive_slist_node>();
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			ASSERT_EQ(node, &(node_storage[node_storage.size() - 1 - i]));
			node = node->next();
		}
	}

	TEST(Intrusive_slist, slist_erase_last)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(3);

		Intrusive_slist slist;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			slist.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(slist.size(), 3);

		slist.erase(&(node_storage[0]));

		ASSERT_EQ(slist.size(), 2);

		auto front = slist.front<Intrusive_slist_node>();
		ASSERT_EQ(front, &(node_storage[2]));
		ASSERT_EQ(front->next<Intrusive_slist_node>(), &(node_storage[1]));
	}

	TEST(Intrusive_slist, slist_erase_middle)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(3);

		Intrusive_slist slist;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			slist.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(slist.size(), 3);

		slist.erase(&(node_storage[1]));

		ASSERT_EQ(slist.size(), 2);

		auto front = slist.front<Intrusive_slist_node>();
		ASSERT_EQ(front, &(node_storage[2]));
		ASSERT_EQ(front->next<Intrusive_slist_node>(), &(node_storage[0]));
	}

	TEST(Intrusive_slist, slist_erase_first)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(3);

		Intrusive_slist slist;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			slist.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(slist.size(), 3);

		slist.erase(&(node_storage[2]));

		ASSERT_EQ(slist.size(), 2);

		auto front = slist.front<Intrusive_slist_node>();
		ASSERT_EQ(front, &(node_storage[1]));
		ASSERT_EQ(front->next<Intrusive_slist_node>(), &(node_storage[0]));
	}

	TEST(Intrusive_slist, pop_front)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(3);

		Intrusive_slist slist;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			slist.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(slist.size(), 3);
		ASSERT_EQ(slist.front<Intrusive_slist_node>(), &(node_storage[2]));

		slist.pop_front();
		ASSERT_EQ(slist.size(), 2);
		ASSERT_EQ(slist.front<Intrusive_slist_node>(), &(node_storage[1]));

		slist.pop_front();
		ASSERT_EQ(slist.size(), 1);
		ASSERT_EQ(slist.front<Intrusive_slist_node>(), &(node_storage[0]));

		slist.pop_front();
		ASSERT_EQ(slist.size(), 0);
		ASSERT_EQ(slist.front<Intrusive_slist_node>(), nullptr);
	}
}
