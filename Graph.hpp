#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <random>
#include <tuple>

using namespace std;

template<typename T>
class Graph{
	
private:
	const unsigned int numberOfVertices;
	unsigned int numberOfArcs;
	vector<vector<T> > minDistMatrix;
	vector<tuple<T, int, int> > arcs;

public:
	Graph(int numberOfVertices);
	void addArc(T cost, int source, int destination);
	void initializeMinimalDistanceMatrix(T infinity);
	vector<int> generateVerticesPermutation();
	void floydWarshall();
	//vector<vector<int> > findXPathsAmongYPermutations(int totalPermutations, int totalPaths);
};

#endif
