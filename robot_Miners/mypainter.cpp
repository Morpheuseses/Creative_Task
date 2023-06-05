#include "mypainter.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <string>

myPainter::myPainter()
{
    front = QBrush(Qt::gray);
    back = QBrush(Qt::gray);
    textPen = QPen(Qt::darkGray);
    glFont.setPixelSize(20);
}

void myPainter::draw(QPainter *painter, QPaintEvent *event, Map map)
{
    painter->fillRect(event->rect(), back);
    painter->setBrush(front);
    painter->setPen(textPen);
    int w = 30;
    int h = 30;
    int pixeldistance = 30;
    for (int i = 0; i < map.height; i++)
        for (int j = 0; j < map.width; j++)
        {
            if (!(map.prohibited.find(map.map_table[i][j]) > map.prohibited.length()))
                painter->setBrush(Qt::darkGray);
            else
                if (!(map.moveAble.find(map.map_table[i][j]) > map.moveAble.length()))
                    painter->setBrush(Qt::green);
                else
                    painter->setBrush(Qt::gray);

            if (!(map.moveAble.find(map.map_table[i][j]) > map.moveAble.length()))
                painter->drawEllipse(j*pixeldistance, i*pixeldistance, w, h);
            else
                painter->drawRect(j*pixeldistance, i*pixeldistance, w, h);
        }
}
