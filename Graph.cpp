#include "Graph.hpp"
#include <type_traits>
#include <iostream>
#include <random>
#include <numeric>
#include <algorithm>
#include <cassert>

constexpr double infinity = 1e9;

Graph::Graph(unsigned int numOfVertices)
{
	numberOfVertices = numOfVertices;
	assert(numOfVertices > 1);
	numberOfArcs = 0;
	minDistMatrix = vector<vector<double> >(numberOfVertices, vector<double>(numberOfVertices));
	for(int a = 0; a < numberOfVertices; ++a)
	{
		for(int b = a; b < numberOfVertices; ++b)
		{
			minDistMatrix[a][b] = infinity;
			minDistMatrix[b][a] = infinity;
		}
	}
}

Graph::~Graph()
{
	std::cout << "The graph destructor was called" << std::endl;
}

void Graph::addArc(Arc x)
{
	assert(x.source >= 0 && x.source < numberOfVertices);
	assert(x.destination >= 0 && x.destination < numberOfVertices);
	arcs.push_back(x);
	numberOfArcs++;
	printf("min(%lf, %lf) = %lf\n", x.cost, minDistMatrix[x.source][x.destination], std::min(x.cost, minDistMatrix[x.source][x.destination]));
	minDistMatrix[x.source][x.destination] = std::min(x.cost, minDistMatrix[x.source][x.destination]);
	std::cout << "adding edge from " << x.source << " to " << x.destination << std::endl;
	std::cout << " cost = " << x.cost << std::endl;
}

void Graph::floydWarshall()
{
	for(int i = 0; i < numberOfVertices; ++i) minDistMatrix[i][i] = 0;
	for(int z = 0; z < numberOfVertices; ++z)
	{
		for(int x = 0; x < numberOfVertices; ++x)
		{
			for(int y = 0; y < numberOfVertices; ++y)
			{
				minDistMatrix[x][z] = std::min(minDistMatrix[x][z], minDistMatrix[x][y] + minDistMatrix[y][z]);
			}
		}
	}
}

vector<int> Graph::findBestCycle(vector<int>& verticesPermutation)
{
	assert(verticesPermutation.size() == numberOfVertices);

	vector<int> path{verticesPermutation[0], verticesPermutation[1], verticesPermutation[0]};
	double bestInsertionCost, currentInsertionCost;
	int bestInsertionIndex;
	for(int index = 2; index < numberOfVertices; ++index)
	{
		bestInsertionCost = infinity;
		bestInsertionIndex = -1;
		for(int vertex = 0; vertex < path.size()-1; ++vertex)
		{
			currentInsertionCost = minDistMatrix[path[vertex]][verticesPermutation[index]] +
								   minDistMatrix[verticesPermutation[index]][path[vertex+1]];

			if(currentInsertionCost < bestInsertionCost)
			{
				bestInsertionCost = currentInsertionCost;
				bestInsertionIndex = vertex+1;
			}
		}
		std::cout << "For the vtx = " << verticesPermutation[index] << std::endl;
		std::cout << "currentInsertionCost == " << currentInsertionCost << std::endl;
		assert(bestInsertionIndex >= 0 && bestInsertionIndex < path.size());
		path.insert(path.begin() + bestInsertionIndex, verticesPermutation[index]);
		
	}
	puts("Acabei");
	return path;
}

std::set<std::pair<double, vector<int> > > Graph::findKBestPathsUsingNIterations(int desiredNumberOfPaths, int numberOfAttemptsAllowed)
{
	std::set<std::pair<double, vector<int> > > bestKPaths;

	assert(desiredNumberOfPaths < numberOfAttemptsAllowed);
	vector<int> tmp;
	double pathCost;

	vector<int> permutation(numberOfVertices);
	std::iota(permutation.begin(), permutation.end(), 0);
	std::random_shuffle(permutation.begin(), permutation.end());

	for(int i = 0; i < numberOfAttemptsAllowed; ++i)
	{
		tmp = findBestCycle(permutation);
		pathCost = 0;
		for(int vtx = 0; vtx < numberOfVertices+1; ++vtx)
			pathCost += minDistMatrix[tmp[vtx]][tmp[vtx+1]];

		if(bestKPaths.size() < desiredNumberOfPaths)
		{
			bestKPaths.insert(std::make_pair(pathCost, tmp));
			puts("inseri");
		}
		else
		{
			if(pathCost < bestKPaths.rbegin()->first)
			{
				bestKPaths.erase(bestKPaths.end());
				bestKPaths.insert(std::make_pair(pathCost, tmp));
			}
		}
		std::random_shuffle(permutation.begin(), permutation.end());
		puts("embaralhei");
	}
	assert(bestKPaths.size() == desiredNumberOfPaths);
	return bestKPaths;
}





