#ifndef HEADER_HUNTER_INC_GRAPH__H
#define HEADER_HUNTER_INC_GRAPH__H

#include <unordered_map>
#include <vector>

namespace HeaderHunter{

class DirectedGraph{
public:

    DirectedGraph(const std::unordered_map<int, std::vector<int>> graph);

    ~DirectedGraph() = default;

    std::vector<std::vector<int>> detectCycles();

    std::vector<int> getNodesWithoutIncomingEdges();

    std::vector<int> getNodesWithoutOutcomingEdges();
private:

    std::unordered_map<int, std::vector<int>> m_graph;
    
};

};


#endif // HEADER_HUNTER_INC_GRAPH__H