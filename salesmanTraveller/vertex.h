#ifndef VERTEX_H
#define VERTEX_H

#include<QGraphicsItem>
#include<QGraphicsEllipseItem>
#include<QGraphicsTextItem>
#include<QGraphicsLineItem>
#include<QBrush>
#include<QPen>
#include<QColor>
#include<QFont>
#include<QString>

#include<QDebug>



class Vertex
{
public:

    unsigned int Number;
    int x = 0;
    int y = 0;

    QGraphicsEllipseItem* circle = nullptr;
    QGraphicsTextItem* nameOfTop = nullptr;

    Vertex(int x, int y, unsigned int number);

    ~Vertex();
};

#endif // VERTEX_H
