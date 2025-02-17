#pragma once

#include <vector>
#include <string>
#include <fstream>

/**
 * @file prim.h
 */

 /**
  * @struct Edge
  * @brief Represents an edge in the graph.
  */
struct Edge {

	int src, dest, weight;
};

/**
 * @class Graph
 * @brief Represents an undirected weighted graph and provides Prim's algorithm implementation.
 */
class Graph {
private:
	int numVertices;                          ///< Number of vertices in the graph.
	std::vector<std::vector<std::pair<int, int>>> adjList; ///< Adjacency list representation.

public:
	/**
	 * @brief Constructor for Graph.
	 * @param vertices Number of vertices in the graph.
	 */
	explicit Graph(int vertices);

	/**
	 * @brief Adds an edge to the graph.
	 * @param u Source vertex.
	 * @param v Destination vertex.
	 * @param weight Weight of the edge.
	 */
	void addEdge(int u, int v, int weight);

	/**
	 * @brief Gets the number of vertices in the graph.
	 * @return The number of vertices.
	 */
	int getNumVertices() const;

	/**
	 * @brief Gets edges connected to a given vertex.
	 * @param vertex The vertex for which edges are retrieved.
	 * @return Vector of edges connected to the vertex.
	 */
	const std::vector<std::pair<int, int>>& getEdges(int vertex) const;

	/**
	 * @brief Runs Prim's algorithm to find the Minimum Spanning Tree.
	 * @return A pair containing the vector of edges in the MST and its total weight.
	 */
	std::pair<std::vector<Edge>, int> primMST() const;

	/**
	 * @brief Saves the Minimum Spanning Tree to a Graphviz file.
	 * @param mst Vector of edges in the MST.
	 * @param filename Name of the file to save.
	 */
	void saveMSTToGraphviz(const std::vector<Edge>& mst, const std::string& filename) const;
};
