#include <iostream>
#include <fstream>
#include "prim.h"

/**
@file main.cpp
*/

/**
 * @brief Loads a graph from a file.
 * @param filename Name of the file containing the graph description.
 * @return Graph object created based on the file data.
 */
Graph loadGraphFromFile(const std::string& filename) {

	std::ifstream inFile(filename);

	if (!inFile.is_open()) {

		throw std::runtime_error("Failed to open file: " + filename);
	}

	int V, E;

	if (!(inFile >> V >> E)) {

		throw std::runtime_error("Invalid file format: cannot read number of vertices and edges.");
	}

	int maxVertex = 0;

	std::vector<std::tuple<int, int, int>> edges;

	int u, v, weight;

	while (inFile >> u >> v >> weight) {

		maxVertex = std::max({ maxVertex, u, v });

		edges.emplace_back(u, v, weight);
	}

	if (maxVertex >= V) {

		V = maxVertex + 1;
	}

	Graph graph(V);

	for (const auto& [u, v, weight] : edges) {

		graph.addEdge(u, v, weight);
	}

	inFile.close();

	return graph;
}

/**
 * @brief Entry point of the program.
 * @return Program exit code.
 */
int main() {

	try {

		std::string inputFile = "input.txt";
		std::string outputFile = "mst.dot";

		Graph graph = loadGraphFromFile(inputFile);

		std::pair<std::vector<Edge>, int> result = graph.primMST();

		std::vector<Edge> mst = result.first;

		int totalWeight = result.second;

		graph.saveMSTToGraphviz(mst, outputFile);

		std::cout << "Minimum spanning tree saved to file: " << outputFile << std::endl;
		std::cout << "Total weight of the minimum spanning tree: " << totalWeight << std::endl;
	}
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
		return 1;
	}

	return 0;
}