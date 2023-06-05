#include "robot.h"
#include <cmath>
#include <string>
#include <QRandomGenerator>


std::ostream& operator<< (std::ostream& out, std::vector<Node*> v)
{
    for (auto i : v)
    {
        std::cout << "(x " << i->x << ":y " << i->y << ") ";
    }
    return out;
}

std::vector<Node*> Robot::findPath(Node* start, Node* end)
{
    std::vector<Node*> tmpPath;
    tmpPath.resize(0);

    std::vector<std::vector<Node*>> map_nodes(map->height, std::vector<Node*>(map->width, nullptr));
    for (auto& vec : map_nodes)
    {
        vec.resize(map->width, nullptr);
    }
    std::vector<Node*> explored;
    std::vector<Node*> reachAble;

    reachAble.push_back(start);

    map_nodes[start->y][start->x] = start; // pushing node to the 2D vector of nodes

    while (!reachAble.empty())
    {
        Node* node = choose_node(reachAble);

        if (*node == *end)
        {

            while (*node != *start && node->prev)
            {
                tmpPath.push_back(node);
                node = node->prev;
            }
            for (int i = 0; i < map->height; i++)
                for (int j = 0; j < map->width; j++)
                {
                    if (find(tmpPath.begin(), tmpPath.end(), map_nodes[i][j]) == tmpPath.end())
                        delete map_nodes[i][j];
                }
            return tmpPath;
        }
        if (!node->isVisited)
        {
            node->globalGoal = sqrt((node->x - end->x) * (node->x - end->x) + (node->y - end->y) * (node->y - end->y));
            if (node->prev)
            {
                node->localGoal = node->prev->localGoal + 10;
            }
            else
                node->localGoal = 0;
            node->isVisited = true;
            reachAble.erase(remove(reachAble.begin(),reachAble.end(), node ), reachAble.end());
            explored.push_back(node);

            std::vector<Node*> new_reachAble = node->getNbrs(map_nodes);

            // check nodes are obstacles
            for (auto& adjacent : new_reachAble)
            {
                if (adjacent->getObstacle(map))
                {
                    auto it = remove_if(new_reachAble.begin(),new_reachAble.end(), [=](Node* n) {return *n == *adjacent; });
                    new_reachAble.erase(it, new_reachAble.end());
                }
                if (adjacent->getObstacle(map))
                {
                    auto it = remove_if(new_reachAble.begin(), new_reachAble.end(), [=](Node* n) {return *n == *adjacent; });
                    new_reachAble.erase(it, new_reachAble.end());
                }
            }
            // removing explored


            for (auto& elem : new_reachAble)
            {
                if (!(find(explored.begin(), explored.end(), elem) == explored.end()))
                {
                    auto it = remove(new_reachAble.begin(), new_reachAble.end(), elem);
                    new_reachAble.erase(it, new_reachAble.end());
                }
                if (!(find(explored.begin(), explored.end(), elem) == explored.end()))
                {
                    auto it = remove(new_reachAble.begin(), new_reachAble.end(), elem);
                    new_reachAble.erase(it, new_reachAble.end());
                }
            }
            // add previous pointer to adjacent nodes
            for (auto& adjacent : new_reachAble)
            {
                if (find(reachAble.begin(), reachAble.end(), adjacent) == reachAble.end())
                {
                    reachAble.push_back(adjacent); // push to list of reachable nodes
                //}
                //if (node->getTotalCost() + 1 < adjacent->getTotalCost()) // new rows
                //{
                    adjacent->prev = node;
                    //adjacent->globalGoal = node->getTotalCost() + 1;
                }
            }
            //std::cout << "reachable:" << reachAble << std::endl;
            //Sleep(500);
        }
    }
    for (int i = 0; i < map->height; i++)
        for (int j = 0; j < map->width; j++)
        {
            if (find(tmpPath.begin(), tmpPath.end(), map_nodes[i][j]) == tmpPath.end())
                delete map_nodes[i][j];
        }
    return tmpPath;
}

Node* Robot::choose_node(std::vector<Node*> reachable)
{
    float min_cost = 100000000;
    Node* best_node = reachable[0];

    for (auto node : reachable)
    {
        if (min_cost > node->getTotalCost())
        {
            min_cost = node->getTotalCost();
            best_node = node;
        }
    }
    return best_node;
}

void Robot::make_step()
{
    if (state == 0 || state == 2)
        return;
    if (state == 3 && start_point->x == base.first && start_point->y == base.second)
    {
        state = 0;
        return;
    }
    if (*start_point == *end_point)
        return;

    if (path.size() == 0)
        path = findPath(start_point, end_point);
    if (path.size() == 0)
        return;

    Node* toMove = path.back();
    path.pop_back();

    // check if the next node became obstacle
    if (map->moveAble.find(map->map_table[toMove->y][toMove->x]) < map->moveAble.length())
        return;
    else if (map->prohibited.find(map->map_table[toMove->y][toMove->x]) < map->prohibited.length()) {
        findPath(start_point, end_point);
        return;
    }

    this->prev_coordinates.first = x;
    this->prev_coordinates.second = y;

    this->x = toMove->x;
    this->y = toMove->y;

    map->update(this);

    start_point = toMove; // -
}


void Robot::setMoveTo(std::pair<int, int> start, std::pair<int, int> end) // -
{
    start_point = new Node;
    start_point->x = start.first;
    start_point->y = start.second;

    x = start_point->x;
    y = start_point->y;

    end_point = new Node;
    end_point->x = end.first;
    end_point->y = end.second;
}

void Robot::makeNewDest()
{
    bool flag = true;
    int dx, dy;
    while (flag)
    {
        dx = QRandomGenerator::global()->bounded(0, map->width-1);
        dy = QRandomGenerator::global()->bounded(0, map->height-1);
        if (map->prohibited.find(map->map_table[dx][dy]) > map->prohibited.length())
            flag = false;
    }

    std::pair<int, int> dest_point = std::make_pair(dx, dy);
    setMoveTo(std::make_pair(start_point->x, start_point->y),
              dest_point);
}

