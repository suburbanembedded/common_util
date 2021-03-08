#include "common_util/Intrusive_list.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace
{
	TEST(Intrusive_list, construct)
	{
		Intrusive_list list;
	}

	TEST(Intrusive_list, empty_list)
	{
		Intrusive_list list;

		ASSERT_TRUE(list.empty());
		ASSERT_EQ(list.front<Intrusive_list_node>(), nullptr);
		ASSERT_EQ(list.back<Intrusive_list_node>(), nullptr);
		ASSERT_EQ(list.size(), 0);
	}

	TEST(Intrusive_list, push_front)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(16);

		Intrusive_list list;

		for(size_t i = 0; i < node_storage.size(); i++)
		{
			ASSERT_EQ(list.size(), i);
			list.push_front(&(node_storage[i]));
			ASSERT_EQ(list.size(), i+1);
		}

		ASSERT_FALSE(list.empty());
		ASSERT_EQ(list.front<Intrusive_list_node>(), &(node_storage.back()));

		auto node = list.front<Intrusive_list_node>();
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			ASSERT_EQ(node, &(node_storage[node_storage.size() - 1 - i]));
			node = node->next();
		}
	}

	TEST(Intrusive_list, push_back)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(16);

		Intrusive_list list;

		for(size_t i = 0; i < node_storage.size(); i++)
		{
			ASSERT_EQ(list.size(), i);
			list.push_back(&(node_storage[i]));
			ASSERT_EQ(list.size(), i+1);
		}

		ASSERT_FALSE(list.empty());
		ASSERT_EQ(list.front<Intrusive_list_node>(), &(node_storage.front()));

		auto node = list.front<Intrusive_list_node>();
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			ASSERT_EQ(node, &(node_storage[i]));
			node = node->next();
		}
	}

	TEST(Intrusive_list, iterator)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(3);

		Intrusive_list list;
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));

		Intrusive_list::iterator_type itr = list.begin();

		size_t i = 0;
		while(itr != list.end())
		{
			ASSERT_EQ(&(*itr), &(node_storage[i]));
			itr++;
			i++;
		}
	}

	TEST(Intrusive_list, iterator_range_for)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(3);

		Intrusive_list list;
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));

		size_t i = 0;
		for(const auto& n : list)
		{
			ASSERT_EQ(&n, &(node_storage[i]));
			i++;
		}
	}

	TEST(Intrusive_list, const_iterator)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(3);

		Intrusive_list list;
		list.push_front(&(node_storage[2]));
		list.push_front(&(node_storage[1]));
		list.push_front(&(node_storage[0]));

		Intrusive_list::const_iterator_type itr = list.cbegin();

		size_t i = 0;
		while(itr != list.cend())
		{
			ASSERT_EQ(&(*itr), &(node_storage[i]));
			itr++;
			i++;
		}
	}

	TEST(Intrusive_list, erase_last)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(3);

		Intrusive_list list;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			list.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(list.size(), 3);

		list.erase(&(node_storage[0]));

		ASSERT_EQ(list.size(), 2);

		auto front = list.front<Intrusive_list_node>();
		ASSERT_EQ(front, &(node_storage[2]));
		ASSERT_EQ(front->next<Intrusive_list_node>(), &(node_storage[1]));
	}

	TEST(Intrusive_list, erase_middle)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(3);

		Intrusive_list list;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			list.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(list.size(), 3);

		list.erase(&(node_storage[1]));

		ASSERT_EQ(list.size(), 2);

		auto front = list.front<Intrusive_list_node>();
		ASSERT_EQ(front, &(node_storage[2]));
		ASSERT_EQ(front->next<Intrusive_list_node>(), &(node_storage[0]));
	}

	TEST(Intrusive_list, erase_first)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(3);

		Intrusive_list list;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			list.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(list.size(), 3);

		list.erase(&(node_storage[2]));

		ASSERT_EQ(list.size(), 2);

		auto front = list.front<Intrusive_list_node>();
		ASSERT_EQ(front, &(node_storage[1]));
		ASSERT_EQ(front->next<Intrusive_list_node>(), &(node_storage[0]));
	}

	TEST(Intrusive_list, pop_front)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(3);

		Intrusive_list list;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			list.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(list.size(), 3);
		ASSERT_EQ(list.front<Intrusive_list_node>(), &(node_storage[2]));

		list.pop_front();
		ASSERT_EQ(list.size(), 2);
		ASSERT_EQ(list.front<Intrusive_list_node>(), &(node_storage[1]));

		list.pop_front();
		ASSERT_EQ(list.size(), 1);
		ASSERT_EQ(list.front<Intrusive_list_node>(), &(node_storage[0]));

		list.pop_front();
		ASSERT_EQ(list.size(), 0);
		ASSERT_EQ(list.front<Intrusive_list_node>(), nullptr);
	}

	TEST(Intrusive_list, pop_back)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(3);

		Intrusive_list list;
		for(size_t i = 0; i < node_storage.size(); i++)
		{
			list.push_front(&(node_storage[i]));
		}

		ASSERT_EQ(list.size(), 3);
		ASSERT_EQ(list.back<Intrusive_list_node>(), &(node_storage[0]));

		list.pop_back();
		ASSERT_EQ(list.size(), 2);
		ASSERT_EQ(list.back<Intrusive_list_node>(), &(node_storage[1]));

		list.pop_back();
		ASSERT_EQ(list.size(), 1);
		ASSERT_EQ(list.back<Intrusive_list_node>(), &(node_storage[2]));

		list.pop_back();
		ASSERT_EQ(list.size(), 0);
		ASSERT_EQ(list.front<Intrusive_list_node>(), nullptr);
	}

	TEST(Intrusive_list, swap_0_1)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(5);

		Intrusive_list list;
		list.push_back(&(node_storage[0]));
		list.push_back(&(node_storage[1]));
		list.push_back(&(node_storage[2]));
		list.push_back(&(node_storage[3]));
		list.push_back(&(node_storage[4]));
		
		{
			auto a = list.front<Intrusive_list_node>();
			auto b = a->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_list_node>();
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
			auto a = list.front<Intrusive_list_node>();
			auto b = a->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_list_node>();
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

	TEST(Intrusive_list, swap_0_2)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(5);

		Intrusive_list list;
		list.push_back(&(node_storage[0]));
		list.push_back(&(node_storage[1]));
		list.push_back(&(node_storage[2]));
		list.push_back(&(node_storage[3]));
		list.push_back(&(node_storage[4]));
		
		{
			auto a = list.front<Intrusive_list_node>();
			auto b = a->next()->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_list_node>();
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
			auto a = list.front<Intrusive_list_node>();
			auto b = a->next()->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_list_node>();
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

	TEST(Intrusive_list, swap_1_2)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(5);

		Intrusive_list list;
		list.push_back(&(node_storage[0]));
		list.push_back(&(node_storage[1]));
		list.push_back(&(node_storage[2]));
		list.push_back(&(node_storage[3]));
		list.push_back(&(node_storage[4]));
		
		{
			auto a = list.front<Intrusive_list_node>()->next();
			auto b = a->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_list_node>();
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
			auto a = list.front<Intrusive_list_node>()->next();
			auto b = a->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_list_node>();
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

	TEST(Intrusive_list, swap_1_3)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(5);

		Intrusive_list list;
		list.push_back(&(node_storage[0]));
		list.push_back(&(node_storage[1]));
		list.push_back(&(node_storage[2]));
		list.push_back(&(node_storage[3]));
		list.push_back(&(node_storage[4]));
		
		{
			auto a = list.front<Intrusive_list_node>()->next();
			auto b = a->next()->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_list_node>();
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
			auto a = list.front<Intrusive_list_node>()->next();
			auto b = a->next()->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_list_node>();
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

	TEST(Intrusive_list, swap_3_5)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(5);

		Intrusive_list list;
		list.push_back(&(node_storage[0]));
		list.push_back(&(node_storage[1]));
		list.push_back(&(node_storage[2]));
		list.push_back(&(node_storage[3]));
		list.push_back(&(node_storage[4]));
		
		{
			auto a = list.front<Intrusive_list_node>()->next()->next();
			auto b = a->next()->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_list_node>();
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
			auto a = list.front<Intrusive_list_node>()->next()->next();
			auto b = a->next()->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_list_node>();
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

	TEST(Intrusive_list, swap_4_5)
	{
		std::vector<Intrusive_list_node> node_storage;
		node_storage.resize(5);

		Intrusive_list list;
		list.push_back(&(node_storage[0]));
		list.push_back(&(node_storage[1]));
		list.push_back(&(node_storage[2]));
		list.push_back(&(node_storage[3]));
		list.push_back(&(node_storage[4]));
		
		{
			auto a = list.front<Intrusive_list_node>()->next()->next()->next();
			auto b = a->next();
			list.swap(a, b);

			auto node = list.front<Intrusive_list_node>();
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
			auto a = list.front<Intrusive_list_node>()->next()->next()->next();
			auto b = a->next();
			list.swap(b, a);

			auto node = list.front<Intrusive_list_node>();
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