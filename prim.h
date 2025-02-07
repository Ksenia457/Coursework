#pragma once

#include <vector>
#include <string>

/**
 * @brief Structure to represent an edge of the graph.
 */
struct Edge {

    int src;     ///< Source vertex number
    int dest;    ///< Destination vertex number
    int weight;  ///< Weight of the edge
};

/**
 * @brief Class to represent a graph and perform Prim's algorithm.
 */
class Graph {
public:
    /**
     * @brief Graph constructor.
     * @param vertices Number of vertices in the graph.
     */
    explicit Graph(int vertices);

    /**
     * @brief Adds an edge to the graph.
     * @param u Source vertex number.
     * @param v Destination vertex number.
     * @param weight Weight of the edge.
     */
    void addEdge(int u, int v, int weight);

    /**
     * @brief Executes Prim's algorithm to find the minimum spanning tree.
     * @return Pair containing the vector of edges comprising the MST and the total weight.
     */
    std::pair<std::vector<Edge>, int> primMST() const;

    /**
     * @brief Saves the minimum spanning tree in Graphviz format.
     * @param mst Vector of edges of the minimum spanning tree.
     * @param filename Name of the file to save.
     */
    void saveMSTToGraphviz(const std::vector<Edge>& mst, const std::string& filename) const;

private:

    int numVertices;  ///< Number of vertices in the graph
    std::vector<std::vector<std::pair<int, int>>> adjList;  ///< Adjacency list
};