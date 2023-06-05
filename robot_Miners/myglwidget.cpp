#include "myglwidget.h"
#include "mypainter.h"
#include <QPainter>
#include <QRandomGenerator>

myGLWidget::myGLWidget(myPainter *mypainter, QWidget *parent)
    : QOpenGLWidget(parent), mypainter(mypainter)
{
}

void myGLWidget::redraw()
{
    update();
}

void myGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    mypainter->draw(&painter, event, *map);
    painter.end();
}
