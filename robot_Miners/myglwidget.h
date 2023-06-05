#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "mypainter.h"
#include "mainwindow.h"
#include <QOpenGLWidget>
#include "map.h"

class myGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    myGLWidget(myPainter *myPainter, QWidget *parent);
public:
    Map* map;
public slots:
    void redraw();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    myPainter *mypainter;

};
#endif // MYGLWIDGET_H
