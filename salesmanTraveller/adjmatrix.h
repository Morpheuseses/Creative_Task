#ifndef MATRIX_H
#define MATRIX_H

#include "vertex.h"
#include "salesmantraveller.h"
#include "priorityQueue.h"

#include <vector>
#include <QObject>
#include <functional>
#include <ctime>
#include <random>
#include <QString>
#include <QVector>
#include <QQueue>
#include <QPair>

using namespace std;

struct Path
{
    QGraphicsLineItem* line = nullptr;
    QGraphicsTextItem* text = nullptr;
    int size = -1;
};


class AdjMatrix : public QObject
{
    Q_OBJECT

public:
    std::vector<Vertex*> Points;
    Path** PathMatrix;

    explicit AdjMatrix(QObject *parent = Q_NULLPTR);

    ~AdjMatrix();

signals:
    void signalDeleteItem_Line(int index_i, int index_j);
    void signalDeleteItem_Vertex(int index);

    void signalSendMatrixSize(int size);
    void signalSendLabelTextChange(const QString& argl);

public:

    int addPoint(int x, int y);
    void addLine(int firstVert, int secondVert, int size);
    void deleteLine(int index_i, int index_j);
    int deletePoint(int index);
    void deleteAll();

    void setLineColor(int firstVert, int secondVert, int chose);
    void setPointColor(int firstVert, int chose);
    void setAllPointsOneColor(int chose);

    QVector<int> getNbrsVertex(int index);
    QVector<QPair<int, int>> getEdges(int index);
    QVector<int> DFS(int vertexIndex);
    QVector<int> BFS(int vertexIndex);

    QVector<int> dijkstra(int vertexIndex);

    void setPathSize(int firstVert, int secondVert, int size);

    void setAllLinesOneColor(int chose);
    int degreeOfTop(int numbOfTop);

    void ActivateSalesmansMethod();
};

#endif // MATRIX_H
