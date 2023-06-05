#ifndef ROBOT_H
#define ROBOT_H


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "windows.h"
#include "map.h"
#include "node.h"


class Robot
{

public:
    int x;
    int y;

    std::pair<int, int> prev_coordinates;

    std::pair<int, int> base;

    int state = 0; // 0 - stay, 1 - moving(exploring), 2 - dead, 3 - return to base
    int charge = 100;

    Node* start_point;
    Node* end_point;
    std::vector<Node*> path; // конечный узел можно взять отсюда

    Map* map = nullptr;
    std::string standingOn = "";
    std::string model = "*";
public:
    std::vector<Node*> findPath(Node*, Node*); // -
    void make_step();
    Node* choose_node(std::vector<Node*>);
    void setMoveTo(std::pair<int, int>, std::pair<int, int>); // -
    void makeNewDest();
};
#endif // ROBOT_H
