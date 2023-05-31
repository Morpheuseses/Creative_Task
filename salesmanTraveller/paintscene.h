#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

#include <QDebug>

#include "adjmatrix.h"

class PaintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit PaintScene(QGraphicsScene* parent = 0);

    ~PaintScene();
signals:
    void signalGetPtrMatrix(AdjMatrix*& out_ptrMatrix);

private:
    AdjMatrix* ptrMatrix = nullptr;

    Qt::MouseButtons mouseButtonState;

public:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    void addItem_Vertex(int num)
    {
        addItem(ptrMatrix->Points[num]->circle);
        addItem(ptrMatrix->Points[num]->nameOfTop);

    }
    void addItem_Line(int firstVert, int secondVert)
    {
        ptrMatrix->PathMatrix[firstVert][secondVert].line->setZValue(-1);
        addItem(ptrMatrix->PathMatrix[firstVert][secondVert].line);
        addItem(ptrMatrix->PathMatrix[firstVert][secondVert].text);
    }

public slots:
    void deleteItem_Line(int firstVert, int secondVert)
    {
        removeItem(ptrMatrix->PathMatrix[firstVert][secondVert].line);
        removeItem(ptrMatrix->PathMatrix[firstVert][secondVert].text);
    }
    void deleteItem_Point(int index)
    {
        removeItem(ptrMatrix->Points[index]->nameOfTop);
        removeItem(ptrMatrix->Points[index]->circle);
    }
};

#endif // PAINTSCENE_H
