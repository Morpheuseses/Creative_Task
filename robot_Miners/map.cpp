#include "map.h"
#include "robot.h"


void Map::update(Robot* r) // робот должен как-то возращать клетку на место, с которой сделал шаг
{
    int posx = r->prev_coordinates.first;
    int posy = r->prev_coordinates.second;

    if (r->standingOn != "")
        map_table[posy][posx] = r->standingOn;

    posx = r->x;
    posy = r->y;
    r->standingOn = map_table[posy][posx];

    map_table[posy][posx] = r->model;
}

void Map::placeRobot(Robot* r)
{
    r->standingOn = map_table[r->start_point->y][r->start_point->x];

    map_table[r->start_point->y][r->start_point->x] = r->model;
}

void Map::printMap()
{

    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_E = 14;
    int color_G = 3;
    system("cls");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
        {
            if (map_table[i][j] == "G")
                SetConsoleTextAttribute(hconsole, color_G);

            else if (map_table[i][j] == "E")
                    SetConsoleTextAttribute(hconsole, color_E);
                else
                    SetConsoleTextAttribute(hconsole, 7);
            std::cout << map_table[i][j] << " ";
        }
        std::cout << std::endl;
    }
    Sleep(200);
}
