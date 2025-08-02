#include "../inc/graph.h"
#include <unordered_set>

using namespace HeaderHunter;

DirectedGraph::DirectedGraph(const std::unordered_map<int, std::vector<int>> graph):m_graph(graph){

}

std::vector<std::vector<int>> DirectedGraph::detectCycles(){

    std::vector<std::vector<int>> cycles;

    return cycles;
}

std::vector<int> DirectedGraph::getNodesWithoutIncomingEdges(){

    std::unordered_set<int> incoming;

    // Step 1: Record all nodes with incoming edges
    for (const auto& [u, neighbors] : m_graph) {
        for (int v : neighbors) {
            incoming.insert(v);
        }
    }

    // Step 2: Find all nodes with no incoming edges
    std::vector<int> no_incoming;
    for (const auto& [node, _] : m_graph) {
        if (incoming.find(node) == incoming.end()) {
            no_incoming.push_back(node);
        }
    }

    return no_incoming;
}

std::vector<int> DirectedGraph::getNodesWithoutOutcomingEdges(){
    std::unordered_set<int> all_nodes;
    std::unordered_set<int> withoutgoing;

    // Step 1: Collect all nodes that exist (from keys and values)
    for (const auto& [u, neighbors] : m_graph) {
        all_nodes.insert(u);
        for (int v : neighbors) {
            all_nodes.insert(v);
        }
    }

    // Step 2: Collect nodes with outgoing edges (i.e., present in map with non-empty vector)
    for (const auto& [u, neighbors] : m_graph) {
        if (!neighbors.empty()) {
            withoutgoing.insert(u);
        }
    }

    // Step 3: Nodes with no outgoing edges = all nodes - nodes with outgoing edges
    std::vector<int> no_outgoing;
    for (int node : all_nodes) {
        if (withoutgoing.find(node) == withoutgoing.end()) {
            no_outgoing.push_back(node);
        }
    }

    return no_outgoing;
}