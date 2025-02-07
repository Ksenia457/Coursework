#include "prim.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>

/**
 * @brief Graph constructor.
 * @param vertices Number of vertices in the graph.
 */
Graph::Graph(int vertices) : numVertices(vertices), adjList(vertices) {}

/**
 * @brief Adds an edge to the graph.
 * @param u Source vertex number.
 * @param v Destination vertex number.
 * @param weight Weight of the edge.
 */
void Graph::addEdge(int u, int v, int weight) {

    adjList[u].push_back(std::make_pair(v, weight));
    adjList[v].push_back(std::make_pair(u, weight));
}

/**
 * @brief Executes Prim's algorithm to find the minimum spanning tree.
 * @return Pair containing the vector of edges comprising the MST and the total weight of the MST.
 */
std::pair<std::vector<Edge>, int> Graph::primMST() const {

    std::vector<Edge> mst;

    std::vector<bool> inMST(numVertices, false);

    std::vector<int> key(numVertices, std::numeric_limits<int>::max());

    std::vector<int> parent(numVertices, -1);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    int startVertex = 0;
    key[startVertex] = 0;

    pq.push(std::make_pair(0, startVertex));

    int totalWeight = 0;

    while (!pq.empty()) {

        int u = pq.top().second;

        pq.pop();

        if (inMST[u])

            continue;

        inMST[u] = true;

        if (parent[u] != -1) {

            mst.push_back(Edge{ parent[u], u, key[u] });

            totalWeight += key[u];
        }

        for (size_t i = 0; i < adjList[u].size(); ++i) {

            int v = adjList[u][i].first;

            int weight = adjList[u][i].second;

            if (!inMST[v] && weight < key[v]) {

                key[v] = weight;

                pq.push(std::make_pair(key[v], v));

                parent[v] = u;
            }

        }

    }

    return std::make_pair(mst, totalWeight);
}

/**
 * @brief Saves the minimum spanning tree in Graphviz format.
 * @param mst Vector of edges of the minimum spanning tree.
 * @param filename Name of the file to save.
 */
void Graph::saveMSTToGraphviz(const std::vector<Edge>& mst, const std::string& filename) const {

    std::ofstream file(filename);

    if (!file.is_open()) {

        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    file << "graph MST {\n";

    for (size_t i = 0; i < mst.size(); ++i) {
        file << "    " << mst[i].src << " -- " << mst[i].dest
            << " [label=\"" << mst[i].weight << "\"];\n";
    }

    file << "}\n";

    file.close();
}