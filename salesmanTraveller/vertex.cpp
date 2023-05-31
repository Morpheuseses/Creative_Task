#include "vertex.h"

Vertex::Vertex(int px, int py, unsigned int number)
{
    Number = number;
    x = px;
    y = py;

    circle = new QGraphicsEllipseItem(x-13,y-13,26,26);
    circle->setBrush(QColor(255,127,39));
    circle->setPen(QPen(QColor(255,127,39)));

    nameOfTop = new QGraphicsTextItem(QString::number(Number));

    if (Number>=10)
        nameOfTop->setPos(x-9,y-10);
    else
        nameOfTop->setPos(x-6,y-10);

}
Vertex::~Vertex()
{
    delete circle;
    delete nameOfTop;
}
