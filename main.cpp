#include <iostream>
#include <vector>
#include <queue>
#include "prim.h"

/**
@file main.cpp
*/

/**
 * @brief Checks if the graph is connected using BFS.
 * @param graph The adjacency list representation of the graph.
 * @return True if the graph is connected, otherwise false.
 */
bool isConnected(const Graph& graph) {

	int V = graph.getNumVertices();

	std::vector<bool> visited(V, false);
	std::queue<int> q;

	q.push(0);

	visited[0] = true;

	int visitedCount = 1;

	while (!q.empty()) {

		int node = q.front();

		q.pop();

		for (const auto& edge : graph.getEdges(node)) {

			int neighbor = edge.first;

			if (!visited[neighbor]) {

				visited[neighbor] = true;

				q.push(neighbor);

				visitedCount++;
			}

		}

	}

	return visitedCount == V;
}

/**
 * @brief Loads a graph from console input with connectivity check.
 * @return A valid Graph object.
 */
Graph loadGraphFromConsole() {

	while (true) {

		int V, E;

		std::cout << "Enter the number of vertices and edges: ";
		std::cin >> V >> E;

		Graph graph(V);

		std::cout << "Enter " << E << " edges (u v weight):\n";

		for (int i = 0; i < E; ++i) {

			int u, v, weight;

			std::cin >> u >> v >> weight;

			graph.addEdge(u, v, weight);
		}

		if (isConnected(graph)) {

			return graph;
		}

		else {
			std::cout << "Graph is not connected. Please re-enter a connected graph.\n";
		}

	}

}

/**
 * @brief Entry point of the program.
 * @return Program exit code.
 */
int main() {

	try {

		Graph graph = loadGraphFromConsole();

		std::pair<std::vector<Edge>, int> result = graph.primMST();
		std::vector<Edge> mst = result.first;

		int totalWeight = result.second;

		graph.saveMSTToGraphviz(mst, "mst.dot");

		std::cout << "Minimum spanning tree saved to file: mst.dot" << std::endl;
		std::cout << "Total weight of the minimum spanning tree: " << totalWeight << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}
