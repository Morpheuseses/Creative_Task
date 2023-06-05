#include "node.h"


Node::Node()
{
    x = -1;
    y = -1;
    prev = nullptr;
    isVisited = false;
    bool isObstacle = false;
    globalGoal = 0;
    localGoal = 0;
}
Node::Node(int x, int y)
{
    this->x = x;
    this->y = y;
}
bool Node::getObstacle(Map* map)
{
    if (!(map->prohibited.find(map->map_table[y][x]) > map->prohibited.length()))
    {
        isObstacle = true;
        return true;
    }
    isObstacle = false;
    return false;
}
std::vector<Node*> Node::getNbrs(std::vector<std::vector<Node*>>& map_nodes)
{
    std::vector<Node*> res;

    int width = map_nodes[0].size();
    int height = map_nodes.size();


    if (x + 1 < width)
    {
        if (!map_nodes[y][x + 1])
        {
            map_nodes[y][x + 1] = new Node(x+1,y);
        }
        res.push_back(map_nodes[y][x + 1]);

    }
    if (x - 1 >= 0)
    {
        if (!map_nodes[y][x - 1])
        {
            map_nodes[y][x - 1] = new Node(x-1,y);
        }
        res.push_back(map_nodes[y][x - 1]);

    }
    if (y + 1 < height)
    {
        if (!map_nodes[y + 1][x])
        {
            map_nodes[y + 1][x] = new Node(x,y+1);
        }
        res.push_back(map_nodes[y + 1][x]);

    }
    if (y - 1 >= 0)
    {
        if (!map_nodes[y - 1][x])
        {
            map_nodes[y - 1][x] = new Node(x,y-1);
        }
        res.push_back(map_nodes[y - 1][x]);
    }
    return res;
}
