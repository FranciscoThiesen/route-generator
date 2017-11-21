#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int main()
{
	constexpr unsigned int nVertices = 10;

	Graph G(nVertices);

	for(uint i = 0; i < nVertices; ++i)
	{
		for(uint j = i; j < nVertices; ++j)
		{
			G.addArc(Arc(i, j, 1.0));
			G.addArc(Arc(j, i, 1.0));
		}
	}

	G.floydWarshall();

	for(uint i = 0; i < nVertices; ++i)
	{
		for(uint j = 0; j < nVertices; ++j)
		{
			printf("%.0lf ", G.minDistMatrix[i][j]);
		}
	}

	auto genPaths = G.findKBestPathsUsingNIterations(10, 20);


	for(const auto &path : genPaths)
	{
		std::cout << "The cost of the following path is of " << path.first << " units " << std::endl;
		for(const int &vtx : path.second)
			std::cout << vtx << " ";
		std::cout << std::endl;
	}

	return 0;
}
