#pragma once
#include <string>
#include <vector>
#include <limits>
#include <cmath>

enum class NodeType {
    Empty,
    Wall,
    Start,
    End,
    Path,
    Open,
    Closed
};

inline constexpr float INF_COST = std::numeric_limits<float>::infinity();

class Node {
public:
    int x = 0, y = 0;
    NodeType type = NodeType::Empty; // Type of the node

    float gCost = INF_COST; // Cost from start to current node
    float hCost = INF_COST; // Heuristic cost to end node
    float fCost() const { return gCost + hCost; } // Total cost
   
    std::vector<Node*> neighbors; // Adjacent nodes
    Node* parent = nullptr; // Pointer to parent node for path reconstruction

    Node()
      : type(NodeType::Empty), gCost(INF_COST), hCost(INF_COST), parent(nullptr) {}

    void reset() {
        type = NodeType::Empty;
        gCost = INF_COST;
        hCost = INF_COST;
        parent = nullptr;
    }

};
