#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include "map.h"

class myPainter
{
public:
    myPainter();

public:
    void draw(QPainter *painter, QPaintEvent *event, Map map);
    QBrush front;
private:

    QBrush back;
    QFont glFont;
    QPen textPen;
};

#endif // MYPAINTER_H
