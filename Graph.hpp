#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

using namespace std;

struct Arc {
	int source;
	int destination;
	double cost;
};

/*
 * Graph Class Implementation
*/
class Graph 
{
	
private:
	const unsigned int numberOfVertices; /**< number of vertices of the graph */
	unsigned int numberOfArcs; /**< number of edges of the graph */

	/*
	 * Matrix that contains the minimum distance between two nodes
	 * minDistMatrix[i][j] = cost of the shortest path from i to j
	*/
	vector<vector<double> > minDistMatrix;

	vector<Arc> arcs; /**< vector of arcs */

public:
	
	/*
	 * Graph constructor
	*/
	Graph(int numberOfVertices);
	
	/*
	 * Graph destructor
	*/
	~Graph();

	/*
	 * Method for adding a new edge to the graph
	*/
	void addArc(Arc x);


	/*
	 * Method for initializing the distanceMatrix with infinity
	 * This step is required for using the Floyd-Warshall Algorithm
	*/
	void fillDistanceMatrixWithInfinity();
	
	/*
	 * Method for generating a pseudorandom permutation of the nodes
	*/
	vector<int> generateVerticesPermutation();
	
	/**
	 *	Floyd-Warshall Algorithm implementation for finding the shortest
	 *	path between every pair of nodes
	 *  Big-O complexity -> O(vertices^3)
	*/ 
	void floydWarshall();



};

#endif
