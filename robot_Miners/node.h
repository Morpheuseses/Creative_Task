#ifndef NODE_H
#define NODE_H


#pragma once
#include "map.h"
#include <vector>

struct Node
{
public:

    int x;
    int y;
    Node* prev = nullptr;
    bool isVisited = false;
    bool isObstacle = false;
    float globalGoal = 0;
    float localGoal = 0;


public:

    Node();
    Node(int x, int y);
    float getTotalCost() { return globalGoal + localGoal; }
    bool getObstacle(Map* map);
    std::vector<Node*> getNbrs(std::vector<std::vector<Node*>>& map_nodes);
    bool operator != (Node node)
    {
        return !(node.x == this->x && node.y == this->y);
    }
    bool operator == (Node node)
    {
        return (node.x == this->x && node.y == this->y);
    }
};
#endif // NODE_H
