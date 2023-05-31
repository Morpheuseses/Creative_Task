#include "paintscene.h"

PaintScene::PaintScene(QGraphicsScene* parent) : QGraphicsScene(parent)
{

}
PaintScene::~PaintScene()
{

}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {

        if(items(QPointF(event->scenePos().x(), event->scenePos().y())).size()==0)
        {

            if(ptrMatrix==nullptr) {emit signalGetPtrMatrix(ptrMatrix);}



            int buffNumbOfCreatedPoint = ptrMatrix->addPoint(event->scenePos().x(), event->scenePos().y());


            addItem_Vertex(buffNumbOfCreatedPoint);

            for(int i = 0; i < buffNumbOfCreatedPoint; i++)
            {

            addItem_Line(i, buffNumbOfCreatedPoint);
            }
        }
    }
    if(event->button() == Qt::RightButton)
    {
        ptrMatrix->deletePoint(0);
    }

    if(event->button() == Qt::MiddleButton)
    {
        ptrMatrix->deleteAll();
    }
}
