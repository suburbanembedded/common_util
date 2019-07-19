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

	TEST(Intrusive_list, list_build)
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
}