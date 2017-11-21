#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <set>
#include <utility>

using std::vector;

/*
 * Struct for Arc (directed)
*/
struct Arc {
	
	int source;
	int destination;
	double cost;
	explicit Arc(int src, int dest, double c) : source(src), destination(dest), cost(c) {};

};

/*
 * Graph Class Implementation
 * It assumes that the graph consists of a single Strongly Connected Component
*/
struct Graph 
{
	unsigned int numberOfVertices; /**< number of vertices of the graph */

	
	vector<Arc> arcs; /**< vector of arcs (directed) */

	/*
	 * Matrix that contains the minimum distance between two nodes
	 * minDistMatrix[i][j] = cost of the shortest path from i to j
	*/
	vector<vector<double> > minDistMatrix;

	 /**< vector of arcs */

	/*
	 * Graph constructor
	*/
	Graph(const unsigned int numOfVertices);
	
	/*
	 * Graph destructor
	*/
	~Graph();

	/*
	 * Method for adding a new edge to the graph
	*/
	void addArc(Arc x);

	/*
	 *	Floyd-Warshall Algorithm implementation for finding the shortest
	 *	path between every pair of nodes
	 *  Big-O complexity -> O(vertices^3)
	*/ 
	void floydWarshall();

	/*
	 * Method for finding the best cycle for a given permutation in O(vertices ^ 2)
	 * We start the cycle with the two first vertices of the cycle, and then we insert the 
	 * next vertex of the permutation on the cheapeast position available
	 * For example, if we have such a cycle v1 -> v2 -> v1, and we want to insert v3
	 * We will try to insert v3 between v1 and v2, (v1 -> v3 -> v2 -> v1), and also
	 * between v2 and v1(v1 -> v2 -> v3 -> v1). We shall choose the cycle with the smallest
	 * total cost among these two.
	 * Big-O complexity -> O(vertices)
	*/
	vector<int> findBestCycle(vector<int>& verticesPermutation);


	/*
	 * Method for selecting the best K cycles, using exactly N attempts.
	 * Big-O complexity -> O(N * vertices^2)
	*/
	std::set<std::pair<double, vector<int> > > findKBestPathsUsingNIterations(int desiredNumberOfPaths,
	 int numberOfAttemptsAllowed);


};

#endif
