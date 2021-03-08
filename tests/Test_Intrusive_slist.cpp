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

	TEST(Intrusive_slist, push_front)
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

	TEST(Intrusive_slist, erase_last)
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

	TEST(Intrusive_slist, erase_middle)
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

	TEST(Intrusive_slist, erase_first)
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

	TEST(Intrusive_slist, iterator)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(3);

		Intrusive_slist slist;
		slist.push_front(&(node_storage[2]));
		slist.push_front(&(node_storage[1]));
		slist.push_front(&(node_storage[0]));

		Intrusive_slist::iterator_type itr = slist.begin();

		size_t i = 0;
		while(itr != slist.end())
		{
			ASSERT_EQ(&(*itr), &(node_storage[i]));
			itr++;
			i++;
		}
	}

	TEST(Intrusive_slist, iterator_range_for)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(3);

		Intrusive_slist slist;
		slist.push_front(&(node_storage[2]));
		slist.push_front(&(node_storage[1]));
		slist.push_front(&(node_storage[0]));

		size_t i = 0;
		for(const auto& n : slist)
		{
			ASSERT_EQ(&n, &(node_storage[i]));
			i++;
		}
	}

	TEST(Intrusive_slist, const_iterator)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(3);

		Intrusive_slist slist;
		slist.push_front(&(node_storage[2]));
		slist.push_front(&(node_storage[1]));
		slist.push_front(&(node_storage[0]));

		Intrusive_slist::const_iterator_type itr = slist.cbegin();

		size_t i = 0;
		while(itr != slist.cend())
		{
			ASSERT_EQ(&(*itr), &(node_storage[i]));
			itr++;
			i++;
		}
	}

	TEST(Intrusive_slist, swap_0_1)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(5);

		Intrusive_slist list;
		list.push_front(&(node_storage[4]));
		list.push_front(&(node_storage[3]));
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));
		
		{
			auto a = list.front<Intrusive_slist_node>();
			auto b = a->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}

		{
			auto a = list.front<Intrusive_slist_node>();
			auto b = a->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}
	}

	TEST(Intrusive_slist, swap_0_2)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(5);

		Intrusive_slist list;
		list.push_front(&(node_storage[4]));
		list.push_front(&(node_storage[3]));
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));
		
		{
			auto a = list.front<Intrusive_slist_node>();
			auto b = a->next()->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}

		{
			auto a = list.front<Intrusive_slist_node>();
			auto b = a->next()->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}
	}

	TEST(Intrusive_slist, swap_1_2)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(5);

		Intrusive_slist list;
		list.push_front(&(node_storage[4]));
		list.push_front(&(node_storage[3]));
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));
		
		{
			auto a = list.front<Intrusive_slist_node>()->next();
			auto b = a->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}

		{
			auto a = list.front<Intrusive_slist_node>()->next();
			auto b = a->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}
	}

	TEST(Intrusive_slist, swap_1_3)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(5);

		Intrusive_slist list;
		list.push_front(&(node_storage[4]));
		list.push_front(&(node_storage[3]));
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));
		
		{
			auto a = list.front<Intrusive_slist_node>()->next();
			auto b = a->next()->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}

		{
			auto a = list.front<Intrusive_slist_node>()->next();
			auto b = a->next()->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}
	}

	TEST(Intrusive_slist, swap_3_5)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(5);

		Intrusive_slist list;
		list.push_front(&(node_storage[4]));
		list.push_front(&(node_storage[3]));
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));
		
		{
			auto a = list.front<Intrusive_slist_node>()->next()->next();
			auto b = a->next()->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
		}

		{
			auto a = list.front<Intrusive_slist_node>()->next()->next();
			auto b = a->next()->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}
	}

	TEST(Intrusive_slist, swap_4_5)
	{
		std::vector<Intrusive_slist_node> node_storage;
		node_storage.resize(5);

		Intrusive_slist list;
		list.push_front(&(node_storage[4]));
		list.push_front(&(node_storage[3]));
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));
		
		{
			auto a = list.front<Intrusive_slist_node>()->next()->next()->next();
			auto b = a->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
		}

		{
			auto a = list.front<Intrusive_slist_node>()->next()->next()->next();
			auto b = a->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_slist_node>();
			EXPECT_EQ(node, &(node_storage[0]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[1]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[2]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[3]));
			node = node->next();
			EXPECT_EQ(node, &(node_storage[4]));
			node = node->next();
		}
	}
}
