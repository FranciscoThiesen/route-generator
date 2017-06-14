#include "Graph.hpp"

template<typename T>
Graph::Graph(int numberOfVertices)
{
	this->numberOfVertices = numberOfVertices;	
	this->numberOfArcs = 0;
	this->minimalDistanceMatrix.reserve(numberOfVertices);	
}


void Graph::addArc(T cost, int source, int destination)
{
	this->arcs.emplace_back({cost, source, destination});
	numberOfArcs++;
	minDistMatrix[source][destination] = min(cost, minDistMatrix);
}

void Graph::initializeMinDistMatrix(T infinity)
{
	for(int a = 0; a < this->numberOfVertices; ++a)
	{
		minDistMatrix[a][a] = 0;
		for(int b = a + 1; b < this->numberOfVertices; ++b)
		{
			minDistMatrix[a][b] = infinity;
			minDistMatrix[b][a] = infinity;
		}
	}
}

vector<int> Graph::generateVerticesPermutation()
{
	vector<int> permutation(this->numberOfVertices);
	iota(permutation.begin(), permutation.end(), 0);
	random_shuffle(permutation.begin(), permutation.end());
	return permutation;
}

void Graph::floydWarshall()
{
	for(int z = 0; z < numberOfVertices; ++z)
	{
		for(int x = 0; x < numberOfVertices; ++x)
		{
			for(int y = 0; y < numberOfVertices; ++y)
			{
				minDistMatrix[x][z] = min(minDistMatrix[x][z], minDistMatrix[x][y] + minDistMatrix[y][z]);
			}
		}
	}
}



