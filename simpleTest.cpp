#include "Graph.cpp"
#include <gtest/gtest.h>

TEST(testGraph, constructor)
{
	Graph G(10);
	EXPECT_EQ(G.numberOfVertices, 10);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
